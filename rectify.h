#ifndef RECTIFY_H
#define RECTIFY_H

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <cmath>
#include <iostream>
#include <QImage>
#include <QPixmap>
#include <QDebug>
using namespace cv;
using namespace std;

#define ERROR 1234


int ImageRectify(char * pInFileName);

#endif // RECTIFY_H
