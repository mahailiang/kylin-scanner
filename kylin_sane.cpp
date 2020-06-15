#include "kylin_sane.h"
//KylinSane* KylinSane::instance=nullptr; //静态成员需要先初始化

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
  uint8_t *data;
  int width;
  int height;
  int x;
  int y;
}
Image;

#define STRIP_HEIGHT	256
static SANE_Handle device = nullptr;
static int verbose;
static SANE_Byte *buffer;
static size_t buffer_size;

#define SET_1_BIT(n,i) ((1<<(i))|(n))
#define SET_0_BIT(n,i) ((~(1<<(i)))&(n))
#define SET_R_BIT(n,i) ((n)^(1<<(i)))
#define GET_i_BIT(n,i) (((n)>>(i))&1)

static void
auth_callback (SANE_String_Const resource,
	       SANE_Char * username, SANE_Char * password)
{
}

static void write_pnm_header (SANE_Frame format, int width, int height, int depth, FILE *ofp)
{
    switch (format)
    {
        case SANE_FRAME_RED:
        case SANE_FRAME_GREEN:
        case SANE_FRAME_BLUE:
        case SANE_FRAME_RGB:
            fprintf (ofp, "P6\n# SANE data follows\n%d %d\n%d\n", width, height, (depth <= 8) ? 255 : 65535);
            break;
        default:
            if (depth == 1)
                fprintf (ofp, "P4\n# SANE data follows\n%d %d\n", width, height);
            else
                fprintf (ofp, "P5\n# SANE data follows\n%d %d\n%d\n", width, height,(depth <= 8) ? 255 : 65535);
            break;
    }
}

static void *
advance (Image * image)
{
  if (++image->x >= image->width)
    {
      image->x = 0;
      if (++image->y >= image->height || !image->data)
	{
	  size_t old_size = 0, new_size;

	  if (image->data)
        old_size = static_cast<size_t>(image->height * image->width);

	  image->height += STRIP_HEIGHT;
      new_size = static_cast<size_t>(image->height * image->width);

	  if (image->data)
        image->data = (uint8_t *) realloc (image->data, new_size);
	  else
        image->data = (uint8_t *) malloc (new_size);
	  if (image->data)
	    memset (image->data + old_size, 0, new_size - old_size);
	}
    }
  if (!image->data)
    fprintf (stderr, "can't allocate image buffer (%dx%d)\n",
         image->width, image->height);
  return image->data;
}

static SANE_Status scan_it (FILE *ofp)
{
    int i, len, first_frame = 1, offset = 0, must_buffer = 0, hundred_percent;
    SANE_Byte min = 0xff, max = 0;
    SANE_Parameters parm;
    SANE_Status status;
    Image image = { nullptr, 0, 0, 0, 0 };
    SANE_Word total_bytes = 0;
    SANE_Int hang_over = -1;

    do
    {
        if (!first_frame)
        {
            status = sane_start (device);
            if (status != SANE_STATUS_GOOD)
            {
                goto cleanup;
            }
        }

        status = sane_get_parameters (device, &parm);
        qDebug("Parm : stat=%s form=%d,lf=%d,bpl=%d,pixpl=%d,lin=%d,dep=%d\n",
			sane_strstatus (status),
			parm.format, parm.last_frame,
			parm.bytes_per_line, parm.pixels_per_line,
			parm.lines, parm.depth);

        if (status != SANE_STATUS_GOOD)
        {
          goto cleanup;
        }

        if (first_frame)
        {
            if (parm.lines >= 0)
            {
                 qDebug("scanning image of size %dx%d pixels at %d bits/pixel\n",
                      parm.pixels_per_line, parm.lines,
                      parm.depth * (SANE_FRAME_RGB == parm.format ? 3 : 1));
            }
           else
           {
                 qDebug("scanning image %d pixels wide and "
                      "variable height at %d bits/pixel\n",
                      parm.pixels_per_line,
                      parm.depth * (SANE_FRAME_RGB == parm.format ? 3 : 1));
           }
            switch (parm.format)
            {
                case SANE_FRAME_RED:
                case SANE_FRAME_GREEN:
                case SANE_FRAME_BLUE:
                  assert (parm.depth == 8);
                  must_buffer = 1;
                  offset = parm.format - SANE_FRAME_RED;
                  break;
                case SANE_FRAME_RGB:
                  qDebug("SANE_FRAME_RGB\n");
                  assert ((parm.depth == 8) || (parm.depth == 16));

                case SANE_FRAME_GRAY:
                    assert ((parm.depth == 1) || (parm.depth == 8) || (parm.depth == 16));
                    if (parm.lines < 0)
                    {
                        qDebug("parm.format = SANE_FRAME_GRAY, parm.lines < 0\n");
                        must_buffer = 1;
                        offset = 0;
                    }
                    else
                    {
                        qDebug("SANE_FRAME_GRAY\n");
                        write_pnm_header (parm.format, parm.pixels_per_line, parm.lines, parm.depth, ofp);
                    }
                  break;
                default:
                  break;
            }

            if (must_buffer)
            {
                /**
                 * We're either scanning a multi-frame image or the
                 * scanner doesn't know what the eventual image height
                 * will be (common for hand-held scanners).  In either
                 * case, we need to buffer all data before we can write
                 * the image.
                 */
                image.width = parm.bytes_per_line;
                if (parm.lines >= 0)
                    image.height = parm.lines - STRIP_HEIGHT + 1;
                else
                    image.height = 0;

                image.x = image.width - 1;
                image.y = -1;
                if (!advance (&image))
                {
                    status = SANE_STATUS_NO_MEM;
                    goto cleanup;
                }
            }
        }
        else
        {
            assert (parm.format >= SANE_FRAME_RED && parm.format <= SANE_FRAME_BLUE);
            offset = parm.format - SANE_FRAME_RED;
            image.x = image.y = 0;
        }

        hundred_percent = parm.bytes_per_line * parm.lines * ((parm.format == SANE_FRAME_RGB || parm.format == SANE_FRAME_GRAY) ? 1:3);

        while (1)
        {
            double progr;
            status = sane_read (device, buffer, buffer_size, &len);
            total_bytes += (SANE_Word) len;
            progr = ((total_bytes * 100.) / (double) hundred_percent);
            if (progr > 100.)
                progr = 100.;

            if (status != SANE_STATUS_GOOD)
            {
                if (status != SANE_STATUS_EOF)
                {
                    return status;
                }
                break;
            }

            if (must_buffer)
            {
                qDebug("must_buffer = %d\n", must_buffer);
                switch (parm.format)
                {
                    case SANE_FRAME_RED:
                    case SANE_FRAME_GREEN:
                    case SANE_FRAME_BLUE:
                        for (i = 0; i < len; ++i)
                        {
                            image.data[offset + 3 * i] = buffer[i];
                            if (!advance (&image))
                            {
                                status = SANE_STATUS_NO_MEM;
                                goto cleanup;
                            }
                        }
                        offset += 3 * len;
                        break;
                    case SANE_FRAME_RGB:
                        for (i = 0; i < len; ++i)
                        {
                            image.data[offset + i] = buffer[i];
                            if (!advance (&image))
                            {
                                status = SANE_STATUS_NO_MEM;
                                goto cleanup;
                            }
                        }
                        offset += len;
                        break;
                    case SANE_FRAME_GRAY:
                        for (i = 0; i < len; ++i)
                        {
                            image.data[offset + i] = buffer[i];
                            if (!advance (&image))
                            {
                                status = SANE_STATUS_NO_MEM;
                                goto cleanup;
                            }
                        }
                        offset += len;
                        break;
                    default:
                        break;
                }
            }
            else			/* ! must_buffer */
            {
                if ((parm.depth != 16)) 
                    fwrite (buffer, 1, len, ofp);
                else
                {
#if !defined(WORDS_BIGENDIAN)
                    int i, start = 0;
                    /* check if we have saved one byte from the last sane_read */
                    if (hang_over > -1)
                    {
                        if (len > 0)
                        {
                            fwrite (buffer, 1, 1, ofp);
                            buffer[0] = (SANE_Byte) hang_over;
                            hang_over = -1;
                            start = 1;
                        }
                    }
                    /* now do the byte-swapping */
                    for (i = start; i < (len - 1); i += 2)
                    {
                        unsigned char LSB;
                        LSB = buffer[i];
                        buffer[i] = buffer[i + 1];
                        buffer[i + 1] = LSB;
                    }
                    /* check if we have an odd number of bytes */
                    if (((len - start) % 2) != 0)
                    {
                        hang_over = buffer[len - 1];
                        len--;
                    }
#endif
                    fwrite (buffer, 1, len, ofp);
                }
            }

            if (verbose && parm.depth == 8)
            {
              for (i = 0; i < len; ++i)
                if (buffer[i] >= max)
                    max = buffer[i];
                else if (buffer[i] < min)
                    min = buffer[i];
            }
        }
        first_frame = 0;
    }while (!parm.last_frame);

    if (must_buffer)
    {
        image.height = image.y;
        write_pnm_header (parm.format, parm.pixels_per_line,image.height, parm.depth, ofp);

#if !defined(WORDS_BIGENDIAN)
        if (parm.depth == 16)
        {
            int i;
            for (i = 0; i < image.height * image.width; i += 2)
            {
                unsigned char LSB;
                LSB = image.data[i];
                image.data[i] = image.data[i + 1];
                image.data[i + 1] = LSB;
            }
        }
#endif
        fwrite (image.data, 1, image.height * image.width, ofp);
    }

    fflush( ofp );

cleanup:
    if (image.data)
        free (image.data);

    return status;
}


SANE_Status kylin_sane_get_parameters(SANE_Handle device)
{
    SANE_Status status;
    SANE_Parameters parm;

    status = sane_get_parameters (device, &parm);
    qDebug("Parm : stat=%s form=%d,lf=%d,bpl=%d,pixpl=%d,lin=%d,dep=%d\n",
        sane_strstatus (status),
        parm.format, parm.last_frame,
        parm.bytes_per_line, parm.pixels_per_line,
        parm.lines, parm.depth);

    return status;
}

SANE_Status do_scan(const char *fileName)
{
    SANE_Status status = SANE_STATUS_GOOD;
    FILE *ofp = nullptr;
	char path[PATH_MAX];
	char part_path[PATH_MAX];
	buffer_size = (32 * 1024);
    buffer = static_cast<SANE_Byte *>(malloc(buffer_size));

    string dir = "/tmp/scanner/";
    if(access(dir.c_str(), 0) == -1)
    {
        cout << dir << "is not existing, now create it." << endl;
        int flag=mkdir(dir.c_str(), 0777);
        if(flag == 0)
            cout << "create successfully!" << endl;
        else {
            cout << "create failed!" << endl;
        }
    }

	do
	{
        //int dwProcessID = getpid();
        //sprintf (path, "%s%d.pnm", fileName, dwProcessID);
        sprintf (path, "%s/%s.pnm", dir.c_str(), fileName);
        strcpy (part_path, path);
        strcat (part_path, ".part");

        qDebug("picture name: %s\n", path);

		status = sane_start (device);
		if (status != SANE_STATUS_GOOD)
		{
			break;
		}

        if (nullptr == (ofp = fopen (part_path, "w")))
        {
            status = SANE_STATUS_ACCESS_DENIED;
            break;
        }

		status = scan_it (ofp);

		switch (status)
		{
			case SANE_STATUS_GOOD:
			case SANE_STATUS_EOF:
                 {
                      status = SANE_STATUS_GOOD;
                      if (!ofp || 0 != fclose(ofp))
                      {
                          status = SANE_STATUS_ACCESS_DENIED;
                          break;
                      }
                      else
                      {
                          ofp = nullptr;
                          if (rename (part_path, path))
                          {
                              status = SANE_STATUS_ACCESS_DENIED;
                              break;
                          }
                      }
                  }
				  break;
			default:
                  break;
		}
	}while (0);

    if (SANE_STATUS_GOOD != status)
    {
        sane_cancel (device);
    }
    if (ofp)
    {
        fclose (ofp);
        ofp = nullptr;
    }
    if (buffer)
    {
        free (buffer);
        buffer = nullptr;
    }

    return status;
}

// Initialize SANE
//SANE初始化
void init()
{
    SANE_Int version_code = 0;

	sane_init (&version_code, auth_callback);

    qDebug("SANE version code: %d\n", version_code);
}

// Get all devices
//查询所有连接设备。这里会比较耗时
SANE_Status get_devices(const SANE_Device ***device_list)
{
    SANE_Status sane_status = SANE_STATUS_GOOD;

    qDebug("Get all devices...\n");

    sane_status = sane_get_devices (device_list, SANE_FALSE);

    if (sane_status)
	{
        qDebug("sane_get_devices status: %s\n", sane_strstatus(sane_status));
	}	
    return sane_status;
}

// Open a device
//使用设备名字打开设备
SANE_Status open_sane_device(SANE_Device *device, SANE_Handle *sane_handle)
{
    SANE_Status sane_status = SANE_STATUS_GOOD;

    qDebug("Name: %s, vendor: %s, model: %s, type: %s\n",
		 device->name, device->model, device->vendor, device->type);

    sane_status = sane_open(device->name, sane_handle);
    if (sane_status)
    {
        qDebug("sane_open status: %s\n", sane_strstatus(sane_status));
    }

    return sane_status;
}

/**
 * Option 2
 * get all colors
 * print all colors: Color Gray Lineart (etc.)
 */
int get_option_colors(SANE_Handle sane_handle, int optnum)
{
    KylinSane& instance = KylinSane::getInstance();
    QStringList colors;

    const SANE_Option_Descriptor *opt;
    const char *tmp = nullptr;
    int ret = 0;
    int i = 0;

    qDebug("begin get option[%d] colors\n", optnum);

    opt = sane_get_option_descriptor(sane_handle, optnum);

    qDebug("begin print all colors:\n");
    for(i=0; opt->constraint.string_list[i] != nullptr; i++)
	{
        tmp = *(opt->constraint.string_list+i);
        qDebug("optnum[%d] colors string: %s \n", optnum, *(opt->constraint.string_list+i));
        if(!strcmp("Color", tmp))
        {
            colors << QObject::tr("Color");
        }
        if(!strcmp("Gray", tmp))
        {
            colors << QObject::tr("Gray");
        }
        if(!strcmp("Lineart", tmp))
        {
            colors << QObject::tr("Lineart");
        }
    }

    /*
    // Handle StringList colors default display, just place it to 0 position.
    QString tmpColor;

    qDebug() << colors[0];

    // 0 position of colors isn't Gray
    if(QString::compare("Gray", colors[0], Qt::CaseSensitive)
            || !QString::compare("灰度", colors[0], Qt::CaseSensitive))
    {
        for(int k=0; k<colors.size(); k++)
        {
            qDebug() << colors[k];

            if(! QString::compare("Gray", colors[k], Qt::CaseSensitive)
                    || !QString::compare("灰度", colors[k], Qt::CaseSensitive)) // "灰度"
            {

                tmpColor = colors[0];
                colors[0] = colors[k];
                colors[k] = tmpColor;
                break;
            }
        }
    }
    */

    instance.setKylinSaneColors(colors);
    return ret;
}

/**
 * Option 2
 * set selected color
 */
SANE_Status set_option_colors(SANE_Handle sane_handle, SANE_String val_color)
{
    SANE_Status status;

    qDebug("\nbegin set option[2] color: %s \n", val_color);

    status = sane_control_option(sane_handle, 2, SANE_ACTION_SET_VALUE, val_color, nullptr);
    if (status != SANE_STATUS_GOOD)
	{
        qDebug("Option did not set\n");
        return status;
    }

    qDebug("set color option success!\n\n");
    return status;
}


/**
 * Option 3
 * get all sources
 * print all sources: source Gray Lineart (etc.)
 */
int get_option_sources(SANE_Handle sane_handle, int optnum)
{ 
    KylinSane& instance = KylinSane::getInstance();
    QString type;

    const SANE_Option_Descriptor *opt;
    const char *tmp = nullptr;
    int flag = 0;
    int ret = 0;
    int i = 0;

    qDebug("begin get option[%d] sources\n", optnum);

    opt = sane_get_option_descriptor(sane_handle, optnum);

    qDebug("begin print all sources:\n");
    for(i=0; opt->constraint.string_list[i] != nullptr; i++)
	{
        tmp = *(opt->constraint.string_list+i);
        qDebug("optnum[%d] sources string: %s \n", optnum, tmp);
        if(!strcmp("Flatbed", tmp))
        {
            type = QObject::tr("Flatbed"); //平板式
            flag = 1;
        }
    }
    if(flag == 0)
        type = QObject::tr("Transparency Adapter"); //馈纸式

    instance.setKylinSaneType(type);
    return ret;
}

/**
 * Option 2
 * set selected source
 */
SANE_Status set_option_sources(SANE_Handle sane_handle, int optnum, SANE_String val_source)
{
    SANE_Status status = SANE_STATUS_GOOD;

    qDebug("begin set option[%d] source: %s \n", optnum, val_source);

    status = sane_control_option(sane_handle, optnum, SANE_ACTION_SET_VALUE, val_source, nullptr);
    if (status != SANE_STATUS_GOOD)
	{
        qDebug("Option did not set\n");
        return status;
    }

    qDebug("set source option success!\n\n");
    return status;
}


/**
 * Option 6
 * get all resolutions[6] option
 * print all resolution: 4800 2400 1200 600 300 150 100 75 (etc.)
 */
 int get_option_resolutions(SANE_Handle sane_handle, int optnum)
{
    KylinSane& instance = KylinSane::getInstance();
    QStringList resolutions;

    const SANE_Option_Descriptor *opt;
    int res = 0;
    int i = 0;

    qDebug("begin get option[%d] resolution \n", optnum);

    opt = sane_get_option_descriptor(sane_handle, optnum);

    qDebug("begin print all resolutions:\n");
    for(i=0; opt->constraint.word_list[i]; i++)
    {
        res = *(opt->constraint.word_list+i);
        qDebug("optnum[%d] resolutions int: %d \n", optnum, res);
        switch (res) {
        case 4800:
            resolutions << "4800";
            break;
        case 2400:
            resolutions << "2400";
            break;
        case 1200:
            resolutions << "1200";
            break;
        case 600:
            resolutions << "600";
            break;
        case 300:
            resolutions << "300";
            break;
        case 150:
            resolutions << "150";
            break;
        case 100:
            resolutions << "100";
            break;
        case 75:
            resolutions << "75";
            break;
        default:
            break;
        }
    }
    resolutions << QObject::tr("auto");

    /*
    // 0 position of resolutions isn't 300
    QString tmpResolution;

    if(QString::compare("300", resolutions[0], Qt::CaseSensitive))
    {
        for(int k=0; k<resolutions.size(); k++)
        {
            qDebug() << resolutions[k];

            if(! QString::compare("300", resolutions[k], Qt::CaseSensitive))
            {
                tmpResolution = resolutions[0];
                resolutions[0] = resolutions[k];
                resolutions[k] = tmpResolution;
                break;
            }
        }
    }
    */

    instance.setKylinSaneResolutions(resolutions);

    return 0;
}

/**
 * Option 6
 * set selected resolutions
 */
SANE_Status set_option_resolutions(SANE_Handle sane_handle, SANE_Int val_resolution)
{
    SANE_Status status = SANE_STATUS_GOOD;

    qDebug("\nbegin set option 6 resolution: %d \n", val_resolution);

    status = sane_control_option(sane_handle, 6, SANE_ACTION_SET_VALUE, &val_resolution, nullptr);
    if (status != SANE_STATUS_GOOD)
	{
        qDebug("Option did not set\n");
        return status;
    }

    qDebug("set resolution option success!\n\n");
    return status;
}


/**
 * Option 8(Top-left x),9(Top-left y),10(Bottom-right x),11(Bottom-right y)
 * get all sizes[8,9,10,11] option
 * print all size: tl-x tl-y br-x br-y (etc.)
 * A3: 0 0 297 420
 * A4: 0 0 210 297 (canon 210=> 0 0 216 297)
 * Because sizes just can read normal, so we could directly to set general sizes
 */
void get_option_sizes(SANE_Handle sane_handle, int optnum)
{
    KylinSane& instance = KylinSane::getInstance();
    QStringList sizes;

    const SANE_Option_Descriptor *opt;
    int res = 0;
    int i = 0;

    qDebug("begin get option[%d] size \n", optnum);

    opt = sane_get_option_descriptor(sane_handle, optnum);

    qDebug("begin print all sizes:\n");
	for(i=0; opt->constraint.word_list[i]; i++)
	{
        res = *(opt->constraint.word_list+i);
        qDebug("optnum[%d] sizes int: %d \n", optnum, res);

        // Via br_x to decide scan sizes
        if(optnum == 10)
        {
            if(res >= 420)
                sizes << "A2";
            if(res >= 297)
                sizes << "A3";
            if(res >= 210)
                sizes << "A4";
            if(res >= 148)
                sizes << "A5";
            if(res >= 105)
                sizes << "A6";
        }
    }
    instance.setKylinSaneSizes(sizes);
}

/**
 * Option 6
 * set selected sizes
 */
SANE_Status set_option_sizes(SANE_Handle sane_handle, int optnum, SANE_Int val_size)
{
    SANE_Status status = SANE_STATUS_GOOD;

    qDebug("\nbegin set option[%d] size: %d \n", optnum, val_size);

    status = sane_control_option(sane_handle, optnum, SANE_ACTION_SET_VALUE, &val_size, nullptr);
    if (status != SANE_STATUS_GOOD)
	{
        qDebug("Option did not set\n");
        return status;
    }

    qDebug("set size option success!\n\n");
    return status;
}

/**
 * @brief set_option_sizes_real
 * @param sane_handle sane_handle
 * @param val_size_br_x bottom_right x coordition
 * @param val_size_br_y botton_right y coordition
 * @return SANE_STATUS
 */
SANE_Status set_option_sizes_real(SANE_Handle sane_handle, SANE_Int val_size_br_x, SANE_Int val_size_br_y)
{
    SANE_Status status = SANE_STATUS_GOOD;
    qDebug("size Bottom-right xy=[%d, %d]\n", val_size_br_x, val_size_br_y);


    status = set_option_sizes(sane_handle, 10, SANE_FIX(val_size_br_x));
    status = set_option_sizes(sane_handle, 11, SANE_FIX(val_size_br_y));

    return status;
}

SANE_Status set_option_sizes_all(SANE_Handle sane_handle, int type)
{
    SANE_Status status = SANE_STATUS_GOOD;

    switch (type) {
    case A2:
        status = set_option_sizes_real(sane_handle, 420, 594);
        break;
    case A3:
        status = set_option_sizes_real(sane_handle, 297, 420);
        break;
    case A4:
        status = set_option_sizes_real(sane_handle, 210, 297);
        break;
    case A5:
        status = set_option_sizes_real(sane_handle, 148, 210);
        break;
    case A6:
        status = set_option_sizes_real(sane_handle, 105, 144);
        break;
    default:
        status = SANE_STATUS_UNSUPPORTED;
    }

    return status;
}

/*--------------------------------------------------------------------------*/

#define GUARDS_SIZE 4			/* 4 bytes */
#define GUARD1 ((SANE_Word)0x5abf8ea5)
#define GUARD2 ((SANE_Word)0xa58ebf5a)

/* Allocate the requested memory plus enough room to store some guard bytes. */
static void *guards_malloc(size_t size)
{
	unsigned char *ptr;

	size += 2*GUARDS_SIZE;
    ptr = static_cast<unsigned char *>(malloc(size));

	assert(ptr);

	ptr += GUARDS_SIZE;

	return(ptr);
}

/* Free some memory allocated by guards_malloc. */
static void guards_free(void *ptr)
{
    unsigned char *p = static_cast<unsigned char *>(ptr);

	p -= GUARDS_SIZE;
	free(p);
}

/* Get an option descriptor by the name of the option. */
static const SANE_Option_Descriptor *get_optdesc_by_name(SANE_Handle device, const char *name, int *option_num)
{
	const SANE_Option_Descriptor *opt;
	SANE_Int num_dev_options;
	SANE_Status status;	
	
	/* Get the number of options. */
    status = sane_control_option (device, 0, SANE_ACTION_GET_VALUE, &num_dev_options, nullptr);
    qDebug("get option 0 value (%s)\n", sane_strstatus(status));

	for (*option_num = 0; *option_num < num_dev_options; (*option_num)++) {

		/* Get the option descriptor */
		opt = sane_get_option_descriptor (device, *option_num);
	
		if (opt->name && strcmp(opt->name, name) == 0) {
            qDebug("get option descriptor for option %d, opt->name=%s name=%s\n", *option_num, opt->name, name);
			return(opt);
		}
	}
    return(nullptr);
}

void display_option_value(SANE_Handle device, int optnum)
{
    const SANE_Option_Descriptor *opt;

    opt = sane_get_option_descriptor(device, optnum);

    qDebug("\n\nGet options %d:\n", optnum);
    qDebug("opt name: %s\n",opt->name);
    qDebug("opt title: %s\n",opt->title);
    qDebug("opt type: %d \n",opt->type);
    qDebug("opt description: %s\n",opt->desc);
    qDebug("opt cap: %d \n", opt->cap);
    qDebug("opt size: %d \n", opt->size);
    qDebug("opt unit: %d \n", opt->unit);
    qDebug("\n");
}


/* Returns a string with the value of an option. */
static char *get_option_value(SANE_Handle device, const char *option_name)
{
    const SANE_Option_Descriptor *opt;
    void *optval;				/* value for the option */
    int optnum;
    static char str[100];
    int status = 0;

    SANE_String val_string_source; //来源
    SANE_String val_string_color; //颜色
    SANE_Word val_size; //尺寸
    SANE_Word val_resolution; //分辨率

    opt = get_optdesc_by_name(device, option_name, &optnum);
    qDebug("optnum = %d\n", optnum);

    if (opt) {
        optval = guards_malloc(opt->size);
        /* Get default optval(different format) */
        status = sane_control_option (device, optnum, SANE_ACTION_GET_VALUE, optval, nullptr);

        qDebug("opt->type = %d\n", opt->type);
        switch(optnum)
        {
            case 2:
                if(opt->type == SANE_TYPE_STRING)
                {
                    val_string_color = static_cast<SANE_String>(optval);
                    qDebug("Default color= %s constraint_type=%d\n", val_string_color, opt->constraint_type);
                }

                status = get_option_colors(device, optnum);
                break;

            case 3:
                if(opt->type == SANE_TYPE_STRING)
                {
                    val_string_source = static_cast<SANE_String>(optval);
                    qDebug("Default source= %s constraint_type=%d\n", val_string_source, opt->constraint_type);
                }
                status = get_option_sources(device, optnum);
                break;

            case 6:
                if(opt->type == SANE_TYPE_INT)
                {
                    val_resolution = *(SANE_Word*)optval;
                    qDebug("resolution = %d constraint_type=%d\n", val_resolution, opt->constraint_type);

                }

                if(opt->constraint_type == SANE_CONSTRAINT_WORD_LIST)
                {
                    status = get_option_resolutions(device, optnum);
                }
                break;

            case 8:
                if(opt->type == SANE_TYPE_FIXED)
                {
                    val_size = SANE_UNFIX(*(SANE_Word*) optval);
                    qDebug("size Top-left x= %d constraint_type=%d\n", val_size, opt->constraint_type);
                }

                if(opt->constraint_type == SANE_CONSTRAINT_RANGE)
                {
                    get_option_sizes(device, optnum);
                }
                break;
            case 9:
                if(opt->type == SANE_TYPE_FIXED)
                {
                    val_size = SANE_UNFIX(*(SANE_Word*) optval);
                    qDebug("size Top-left y= %d constraint_type=%d\n", val_size, opt->constraint_type);
                }

                if(opt->constraint_type == SANE_CONSTRAINT_RANGE)
                {
                    get_option_sizes(device, optnum);
                }
                break;
            case 10:
                if(opt->type == SANE_TYPE_FIXED)
                {
                    val_size = SANE_UNFIX(*(SANE_Word*) optval);
                    qDebug("size Botton-right x= %d constraint_type=%d\n", val_size, opt->constraint_type);
                }

                if(opt->constraint_type == SANE_CONSTRAINT_RANGE)
                {
                    get_option_sizes(device, optnum);
                }
                break;
            case 11:
                if(opt->type == SANE_TYPE_FIXED)
                {
                    val_size = SANE_UNFIX(*(SANE_Word*) optval);
                    qDebug("size Botton-right y= %d constraint_type=%d\n", val_size, opt->constraint_type);
                }

                if(opt->constraint_type == SANE_CONSTRAINT_RANGE)
                {
                    get_option_sizes(device, optnum);
                }
                break;

            default:
                qDebug("optnum = %d\n", optnum);
        }

        //display_option_value(device, optnum);

        //if (status == SANE_STATUS_GOOD) {
            switch(opt->type) {
            case SANE_TYPE_BOOL:
                if (*(SANE_Word*) optval == SANE_FALSE) {
                    strcpy(str, "FALSE");
                } else {
                    strcpy(str, "TRUE");
                }
                break;

            case SANE_TYPE_INT:
                sprintf(str, "%d", *(SANE_Word*) optval);
                break;

            case SANE_TYPE_FIXED: {
                int i;
                i = SANE_UNFIX(*(SANE_Word*) optval);
                sprintf(str, "%d", i);
            }
            break;

            case SANE_TYPE_STRING:
                strcpy(str, (char *)optval);
                break;

            default:
                str[0] = 0;
            }
        /* } else { */
        /*     [> Shouldn't happen. <] */
        /*     strcpy(str, "backend default"); */
        /* } */

        guards_free(optval);

    } else {
        /* The option does not exists. */
        strcpy(str, "backend default");
    }

    return(str);
}

/* Display the parameters that used for a scan. */
char *kylin_display_scan_parameters(SANE_Handle device)
{
    static char str[150];
    char *p = str;

    *p = 0;

    p += sprintf(p, "scan source=[%s] ", get_option_value(device, SANE_NAME_SCAN_SOURCE));
    p += sprintf(p, "scan mode=[%s] ", get_option_value(device, SANE_NAME_SCAN_MODE));
    p += sprintf(p, "resolution=[%s] ", get_option_value(device, SANE_NAME_SCAN_RESOLUTION));

    p += sprintf(p, "tl_x=[%s] ", get_option_value(device, SANE_NAME_SCAN_TL_X));
    p += sprintf(p, "tl_y=[%s] ", get_option_value(device, SANE_NAME_SCAN_TL_Y));

    //backend/sharp.c
    //A4
    //s->val[OPT_BR_X].w = SANE_FIX(210);
    //s->val[OPT_BR_Y].w = SANE_FIX(297);
    p += sprintf(p, "br_x=[%s] ", get_option_value(device, SANE_NAME_SCAN_BR_X));
    p += sprintf(p, "br_y=[%s] ", get_option_value(device, SANE_NAME_SCAN_BR_Y));

    return(str);
}



// Start scanning
//扫描文档
SANE_Status start_scan(SANE_Handle sane_handle, SANE_String_Const fileName)
{
    device = sane_handle; //全局静态变量初始化

    return do_scan(fileName);
}

// Cancel scanning
//扫描结束
void cancle_scan(SANE_Handle sane_handle)
{
    sane_cancel(sane_handle);
}

// Close SANE device
//关闭设备
void close_device(SANE_Handle sane_handle)
{
    sane_close(sane_handle);
}

// Release SANE resources
//释放所有资源
void my_sane_exit()
{
    sane_exit();
}

// 可以借此整理出未识别设备的情况
int check_search_scan_devices()
{
    // 1. initialize SANE
    qDebug("SANE Init\n");
    init();

    // 2. get all devices
    const SANE_Device ** device_list = nullptr;
    SANE_Status sane_status;
    sane_status = get_devices(&device_list);
    if (sane_status)
    {
        // 6. release resources
        qDebug("Exit\n");
        my_sane_exit();
        return -1;
    }	
    return 0;
}

void kylinNorScanOpen()
{
    SANE_Status sane_status;
    KylinSane& instance = KylinSane::getInstance();
    char name[512] = {0};

    // 1. initialize SANE
    qDebug("SANE Init\n");
    init();

    do
    {
        // 2. get all devices
        const SANE_Device ** device_list = nullptr;
        sane_status = get_devices((&device_list));
        if (sane_status)
        {
            instance.setKylinSaneStatus(false);
            break;
        }

        // display all devices
        int i = 0;
        unsigned int column = 80;

        for (i = 0; device_list[i]; ++i)
        {
            if (column + strlen (device_list[i]->name) + 1 >= 80)
            {
                qDebug ("\n    ");
                column = 4;
            }
            if (column > 4)
            {
                fputc (' ', stdout);
                column += 1;
            }
            fputs (device_list[i]->name, stdout);
            column += strlen (device_list[i]->name);
        }
        fputc ('\n', stdout);



        for (i = 0; device_list[i]; ++i)
        {
            qDebug ("device `%s' is a %s %s %s\n",
                     device_list[i]->name, device_list[i]->vendor,
                     device_list[i]->model, device_list[i]->type);

            // just for one scan device
            snprintf(name, 512, "%s %s", device_list[i]->vendor, device_list[i]->model);

            instance.setKylinSaneName(name);
            //instance.setKylinSaneName(device_list[i]->name);
            instance.setKylinSaneType(device_list[i]->type);
            break;
        }
        if (!device_list[0])
        {
            qDebug ("no SANE devices found\n");
            sane_status = SANE_STATUS_UNSUPPORTED;
            instance.setKylinSaneStatus(false);
            break;
        }

        // 3. open a device
        qDebug("Open a device\n");
        SANE_Handle sane_handle;
        SANE_Device *device = const_cast<SANE_Device *>(*device_list);
        if (!device)
        {
            qDebug("No device connected!\n");
            sane_status = SANE_STATUS_UNSUPPORTED;
            instance.setKylinSaneStatus(false);
            break;
        }

        sane_status = open_sane_device(device, &sane_handle);
        if (sane_status)
        {
            qDebug("Open device failed!\n");
            instance.setKylinSaneStatus(false);
            break;
        }
        instance.handle = sane_handle;

        // 4. start scanning
        qDebug("Scanning...\n");
        //start_scan(sane_handle, "helloworld");
        qDebug("start_scan: %s\n", kylin_display_scan_parameters(sane_handle));

        cancle_scan(sane_handle);

        /*
        // 5. close device
        printf("Close the device\n");
        close_device(sane_handle);
        */
        sane_status = SANE_STATUS_GOOD;
    }while(0);

    if(sane_status)
    {
        instance.setKylinSaneStatus(false);
        qDebug() << "set status false";
    }
    else {
        instance.setKylinSaneStatus(true);
    }

    /*
    // 6. release resources
    qDebug("Exit\n");
    my_sane_exit();
    */

}

#ifdef __cplusplus
}
#endif

KylinSane::KylinSane(QWidget *parent) : QWidget(parent)
{

}

KylinSane::~KylinSane()
{

}

bool KylinSane::getKylinSaneStatus()
{
    return devicesInfo.status;
}
QString KylinSane::getKylinSaneName()
{
    return devicesInfo.name;
}
QString KylinSane::getKylinSaneType()
{
    return devicesInfo.type;
}
QStringList KylinSane::getKylinSaneResolutions()
{
    return  devicesInfo.resolution;
}
QStringList KylinSane::getKylinSaneSizes()
{
    return devicesInfo.size;
}
QStringList KylinSane::getKylinSaneColors()
{
    return devicesInfo.color;
}

void KylinSane::setKylinSaneStatus(bool status)
{
    devicesInfo.status = status;
}
void KylinSane::setKylinSaneType(QString type)
{
    devicesInfo.type = type;
}
void KylinSane::setKylinSaneName(QString name)
{
    devicesInfo.name = name;
}
void KylinSane::setKylinSaneResolutions(QStringList resolution)
{
    devicesInfo.resolution = resolution;
}
void KylinSane::setKylinSaneSizes(QStringList size)
{
    devicesInfo.size = size;
}
void KylinSane::setKylinSaneColors(QStringList color)
{
    devicesInfo.color = color;
}

device_info KylinSane::open_device()
{
    KylinSane& instance = KylinSane::getInstance();
    kylinNorScanOpen();

    return instance.devicesInfo;
}
int KylinSane::start_scanning(user_selected_info info)
{
    KylinSane& instance = KylinSane::getInstance();
    int ret = 0;
    SANE_Status status = SANE_STATUS_GOOD;
    string strColor, strResolution, strSize;
    SANE_String s_color, s_resolution, s_size;

    strColor = info.color.toStdString();
    strResolution = info.resolution.toStdString();
    strSize = info.size.toStdString();

    // For colors
    s_color = const_cast<SANE_String>(strColor.c_str());
    status = set_option_colors(instance.handle, s_color);
    if(status != SANE_STATUS_GOOD)
    {
      qDebug("cannot set option 2 to %s (%s)\n",s_color, sane_strstatus(status));
    }

    // For resolutions
    s_resolution = const_cast<SANE_String>(strResolution.c_str());
    SANE_Int i_resolution;
    if(!strcmp("auto", s_resolution) || !strcmp("自动", s_resolution))
    {
        i_resolution = 300; //自动时设置为300
    }
    else {
        i_resolution = static_cast<SANE_Int>(atoi(s_resolution));
    }

    status = set_option_resolutions(instance.handle, i_resolution);
    if(status != SANE_STATUS_GOOD)
    {
      qDebug("cannot set option 2 to %s (%s)\n",s_resolution, sane_strstatus(status));
    }

    // For sizes
    int type = 0;
    s_size = const_cast<SANE_String>(strSize.c_str());
    if(!strcmp("A2", s_size))
    {
        type = A2;
    }
    else if (!strcmp("A3", s_size)) {
        type = A3;
    }
    else if (!strcmp("A4", s_size)) {
        type = A4;
    }
    else if (!strcmp("A5", s_size)) {
        type = A5;
    }
    else if (!strcmp("A6", s_size)) {
        type = A6;
    }
    status = set_option_sizes_all(instance.handle, type);
    if(status != SANE_STATUS_GOOD)
    {
      qDebug("cannot set option 2 to %s (%s)\n",s_size, sane_strstatus(status));
    }

    ret = start_scan(instance.handle, "scan");
    cancle_scan(instance.handle);
    //kylinNorScan();
    return ret;
}
