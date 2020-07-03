/*
* Copyright (C) 2020 KYLIN SOFTWARE Information Technology Co., Ltd.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 3, or (at your option)
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, see <http://www.gnu.org/licenses/&gt;.
*
*/
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include "title_bar.h"

#include <QDebug>


TitleBar::TitleBar(QWidget *parent)
    : QWidget(parent)
{
    setFixedHeight(32);

    m_pIconLabel = new QLabel(this);
    m_pTitleLabel = new QLabel(this);
    m_pMinimizeButton = new QPushButton(this);
    m_pMaximizeButton = new QPushButton(this);
    m_pCloseButton = new QPushButton(this);

 //   m_pIconLabel->setFixedSize(10,10);
    m_pIconLabel->setScaledContents(true);

    m_pTitleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  //  m_pTitleLabel->setFixedSize(10,10);
    m_pMinimizeButton->setFixedSize(12, 12);
    m_pMaximizeButton->setFixedSize(12, 12);
    m_pCloseButton->setFixedSize(12, 12);

    m_pTitleLabel->setObjectName("whiteLabel");
    m_pMinimizeButton->setObjectName("minimizeButton");
    m_pMaximizeButton->setObjectName("maximizeButton");
    m_pCloseButton->setObjectName("closeButton");

    m_pMinimizeButton->setToolTip("Minimize");
    m_pMaximizeButton->setToolTip("Maximize");
    m_pCloseButton->setToolTip("Close");

    m_pMinimizeButton->setStyleSheet("QPushButton{border-image: url(:/icon/icon/min.png);border:none;background-color:rgb(47,44,43);border-radius:0px;}"
                              "QPushButton:hover{border-image: url(:/icon/icon/min-click.png);border:none;background-color:rgb(47,44,43);border-radius:0px;}"
                                "QPushButton:checked{border-image: url(:/icon/icon/min-click.png);border:none;background-color:rgb(47,44,43);border-radius:0px;}");

    m_pMaximizeButton->setStyleSheet("QPushButton{border-image: url(:/icon/icon/normal.png);border:none;background-color:rgb(47,44,43);border-radius:0px;}"
                              "QPushButton:hover{border-image: url(:/icon/icon/normal-click.png);border:none;background-color:rgb(47,44,43);border-radius:0px;}"
                                "QPushButton:checked{border-image: url(:/icon/icon/max-click.png);border:none;background-color:rgb(47,44,43);border-radius:0px;}");

    m_pCloseButton->setStyleSheet("QPushButton{border-image: url(:/icon/icon/close.png);border:none;background-color:rgb(47,44,43);border-radius:0px;}"
                              "QPushButton:hover{border-image: url(:/icon/icon/close-click.png);border:none;background-color:rgb(47,44,43);border-radius:0px;}"
                                "QPushButton:checked{border-image: url(:/icon/icon/close-click.png);border:none;background-color:rgb(47,44,43);border-radius:0px;}");

    QHBoxLayout *pLayout = new QHBoxLayout(this);
 //   pLayout->addWidget(m_pIconLabel);
    pLayout->addSpacing(0);
  //  pLayout->addWidget(m_pTitleLabel);
    pLayout->addStretch();
    pLayout->addWidget(m_pMinimizeButton);
    pLayout->addWidget(m_pMaximizeButton);
    pLayout->addWidget(m_pCloseButton);
    pLayout->setSpacing(28);
    pLayout->setAlignment(Qt::AlignCenter);
    pLayout->setContentsMargins(0, 0, 14, 0);

    setLayout(pLayout);

    connect(m_pMinimizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_pMaximizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_pCloseButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
}

TitleBar::~TitleBar()
{

}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    emit m_pMaximizeButton->clicked();
}

void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons().testFlag(Qt::LeftButton) && mMoving)
    {
        QWidget *pWindow = this->window();
        pWindow->move(pWindow->pos() + (event->globalPos() - mLastMousePosition));
        mLastMousePosition = event->globalPos();
    }
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        mMoving = true;
        mLastMousePosition = event->globalPos();
    }
}

void TitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        mMoving = false;
    }
}

bool TitleBar::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type())
    {
/*    case QEvent::WindowTitleChange:
    {
        QWidget *pWidget = qobject_cast<QWidget *>(obj);
        if (pWidget)
        {
            m_pTitleLabel->setText(pWidget->windowTitle());
            return true;
        }
    }
    case QEvent::WindowIconChange:
    {
        QWidget *pWidget = qobject_cast<QWidget *>(obj);
        if (pWidget)
        {
            QIcon icon = pWidget->windowIcon();
            m_pIconLabel->setPixmap(icon.pixmap(m_pIconLabel->size()));
            return true;
        }
    }*/
    case QEvent::WindowStateChange:
    case QEvent::Resize:
        updateMaximize();
        return true;
    }
    return QWidget::eventFilter(obj, event);
}

void TitleBar::onClicked()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        if (pButton == m_pMinimizeButton)
        {
            pWindow->showMinimized();
        }
        else if (pButton == m_pMaximizeButton)
        {
            pWindow->isMaximized() ? pWindow->showNormal() : pWindow->showMaximized();
        }
        else if (pButton == m_pCloseButton)
        {

            pWindow->close();
        }
    }
}

void TitleBar::updateMaximize()
{
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        bool bMaximize = pWindow->isMaximized();
        if (bMaximize)
        {
            m_pMaximizeButton->setToolTip(tr("Restore"));
            m_pMaximizeButton->setProperty("maximizeProperty", "restore");
            m_pMaximizeButton->setStyleSheet("QPushButton{border-image: url(:/icon/icon/max.png);border:none;background-color:rgb(47,44,43);border-radius:0px;}"
                                      "QPushButton:hover{border-image: url(:/icon/icon/max-click.png);border:none;background-color:rgb(47,44,43);border-radius:0px;}"
                                        "QPushButton:checked{border-image: url(:/icon/icon/max-click.png);border:none;background-color:rgb(47,44,43);border-radius:0px;}");
        }
        else
        {
            m_pMaximizeButton->setProperty("maximizeProperty", "maximize");
            m_pMaximizeButton->setToolTip(tr("Maximize"));
            m_pMaximizeButton->setStyleSheet("QPushButton{border-image: url(:/icon/icon/normal.png);border:none;background-color:rgb(47,44,43);border-radius:0px;}"
                                      "QPushButton:hover{border-image: url(:/icon/icon/normal-click.png);border:none;background-color:rgb(47,44,43);border-radius:0px;}"
                                        "QPushButton:checked{border-image: url(:/icon/icon/max-click.png);border:none;background-color:rgb(47,44,43);border-radius:0px;}");
        }

        m_pMaximizeButton->setStyle(QApplication::style());
    }
}
