/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * LXDE-Qt - a lightweight, Qt based, desktop toolset
 * https://lxqt.org/
 *
 * Copyright: 2015 LXQt team
 * Authors:
 *   zjesclean@gmail.com
 *
 * This program or library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
 * END_COMMON_COPYRIGHT_HEADER */

#include "app-model.h"
#include "settings.h"
#include <QApplication>
#include <QDebug>
#include <QScreen>
#include <KX11Extras>
#include <KWindowInfo>

AppModel::AppModel(QObject* parent)
    : QAbstractListModel(parent)
{
    create();
}

void AppModel::create()
{
    int  iconSize = Settings::instance().iconSize();
    bool byDesk   = Settings::instance().filterCurrentDesktop();
    bool byScreen = Settings::instance().filterCurrentScreen();

    for (WId wid : KX11Extras::stackingOrder()) {
        KWindowInfo     info(wid, NET::WMVisibleName | NET::WMState | NET::XAWMState | NET::WMWindowType);
        NET::WindowType type = info.windowType(NET::AllTypesMask);
        if (!info.hasState(NET::SkipTaskbar) && (type == NET::Normal || type == NET::Dialog || type == NET::Unknown) &&
            filter(wid, byDesk, byScreen)) {
            m_list.prepend({wid, info.visibleName(), KX11Extras::icon(wid, iconSize, iconSize, true)});
        }
    }
}

int AppModel::rowCount(const QModelIndex& /*parent*/) const
{
    return m_list.size();
}

QVariant AppModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= m_list.size())
        return QVariant();

    switch (role) {
        case AppRole::Display:
            return m_list[index.row()].name;
        case AppRole::Icon:
            return m_list[index.row()].pixmap;
        case AppRole::Window:
            return m_list[index.row()].windowId;
    }
    return QVariant();
}

bool AppModel::filter(WId window, bool byDesk, bool byScreen) const
{
    KWindowInfo info(window, NET::WMDesktop | NET::WMFrameExtents);
    if (byDesk) {
        if (KX11Extras::currentDesktop() != info.desktop() && info.desktop() != NET::OnAllDesktops) {
            return false;
        }
    }

    if (byScreen) {
        if (!QGuiApplication::screenAt(QCursor::pos())->geometry().intersects(info.frameGeometry())) {
            return false;
        }
    }
    return true;
}
