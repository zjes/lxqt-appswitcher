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

#pragma once

#include <QAbstractListModel>
#include <QPixmap>

struct AppInfo
{
    WId     windowId;
    QString name;
    QPixmap pixmap;
};

namespace AppRole {
enum Role
{
    Display = Qt::DisplayRole,
    Icon    = Qt::UserRole + 1,
    Window  = Qt::UserRole + 2
};
}

class AppModel : public QAbstractListModel
{
    Q_OBJECT
public:
    AppModel(QObject* parent);

protected:
    virtual int      rowCount(const QModelIndex& parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

private:
    void create();
    bool filter(WId window, bool byDesk, bool byScreen) const;

private:
    QList<AppInfo> m_list;
};
