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

#include "src/settings.h"
#include <LXQt/Application>
#include <LXQt/lxqtsettings.h>
#include <QApplication>
#include <QDebug>
#include <QFile>

// Should be after Qt headers
#include "src/app-switcher.h"

LXQt::LXQtTheme currentTheme()
{
    QString themeName = "kvantum";//Settings::instance().theme();
    qWarning() << "theme name" << themeName;
    for (const LXQt::LXQtTheme& theme : LXQt::LXQtTheme::allThemes()) {
        if (theme.name() == themeName) {
            qWarning() << "a1";
            return theme;
        }
    }
    qWarning() << "a2";
    return LXQt::LXQtTheme::currentTheme();
}

int main(int argc, char* argv[])
{
    LXQt::Application app(argc, argv);
    app.setQuitOnLastWindowClosed(false);

    LXQt::LXQtTheme theme = currentTheme();
    if (QFile::exists(theme.path() + "/lxqt-app-switcher.qss")) {
        qWarning() << "theme path" << theme.path();
        app.setStyleSheet("file:///" + theme.path() + "/lxqt-app-switcher.qss");
    }

    QWidget     hiddenPreviewParent(0, Qt::Tool);
    AppSwitcher switcher(&hiddenPreviewParent);

    return app.exec();
}
