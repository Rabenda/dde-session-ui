/*
 * Copyright (C) 2015 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     sbw <sbw@sbw.so>
 *             kirigaya <kirigaya@mkacg.com>
 *             Hualet <mr.asianwang@gmail.com>
 *
 * Maintainer: sbw <sbw@sbw.so>
 *             kirigaya <kirigaya@mkacg.com>
 *             Hualet <mr.asianwang@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QDebug>

#include "shutdownframe.h"

const QString WallpaperKey = "pictureUri";

ShutdownFrame::ShutdownFrame(QWidget *parent)
    : FullscreenBackground(parent)
{
    m_shutdownFrame = new ContentWidget(this);

    connect(m_shutdownFrame, &ContentWidget::requestBackground,
            this, static_cast<void (ShutdownFrame::*)(const QString &)>(&ShutdownFrame::updateBackground));

    setContent(m_shutdownFrame);
}

void ShutdownFrame::powerAction(const Actions action)
{
    m_shutdownFrame->powerAction(action);
}

void ShutdownFrame::setConfirm(const bool confrim)
{
    m_shutdownFrame->setConfirm(confrim);
}

ShutdownFrame::~ShutdownFrame()
{
}

ShutdownFrontDBus::ShutdownFrontDBus(ShutdownFrame *parent):
    QDBusAbstractAdaptor(parent),
    m_parent(parent)
{
}

ShutdownFrontDBus::~ShutdownFrontDBus()
{
}

void ShutdownFrontDBus::Ping()
{
}

void ShutdownFrontDBus::Shutdown()
{
    m_parent->setConfirm(true);
    m_parent->powerAction(Actions::Shutdown);
    m_parent->show();
}

void ShutdownFrontDBus::Restart()
{
    m_parent->setConfirm(true);
    m_parent->powerAction(Actions::Restart);
    m_parent->show();
}

void ShutdownFrontDBus::Logout()
{
    m_parent->setConfirm(true);
    m_parent->powerAction(Actions::Logout);
    m_parent->show();
}

void ShutdownFrontDBus::Suspend()
{
    m_parent->powerAction(Actions::Suspend);
}

void ShutdownFrontDBus::SwitchUser()
{
    m_parent->powerAction(Actions::SwitchUser);
}

void ShutdownFrontDBus::Show()
{
    if (m_parent) {
        m_parent->show();
    }
}
