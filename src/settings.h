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
#include <QSettings>

class Settings
{
public:
    static Settings& instance()
    {
        static Settings sets;
        return sets;
    }

    QString theme() const
    {
        return m_sets.value("appearance/lxqt-theme", "ambiance").toString();
    }

    void setTheme(const QString& theme)
    {
        m_sets.setValue("appearance/lxqt-theme", theme);
    }

    int iconSize() const
    {
        return m_sets.value("appearance/icon-size", 38).toInt();
    }

    void setIconSize(int size)
    {
        m_sets.setValue("appearance/icon-size", size);
    }

    int maxDisplayApps() const
    {
        return m_sets.value("appearance/max-disp-apps", 15).toInt();
    }

    void setDisplayApps(int size)
    {
        m_sets.setValue("appearance/max-disp-apps", size);
    }

    int maxTextWidth() const
    {
        return m_sets.value("appearance/max-text-width", 50).toInt();
    }

    void setMaxTextWidth(int width)
    {
        m_sets.setValue("appearance/max-text-width", width);
    }

    bool filterCurrentDesktop() const
    {
        return m_sets.value("filter/current-desktop", true).toBool();
    }

    void setFilterCurrentDesktop(bool filter)
    {
        m_sets.setValue("filter/current-desktop", filter);
    }

    bool filterCurrentScreen() const
    {
        return m_sets.value("filter/current-screen", true).toBool();
    }

    void setFilterCurrentScreen(bool filter)
    {
        m_sets.setValue("filter/current-screen", filter);
    }

    bool customFontSizeEnabled() const
    {
        return m_sets.value("appearance/enable-font-size", 0).toBool();
    }

    void setCustomFontSizeEnabled(bool enable)
    {
        m_sets.setValue("appearance/enable-font-size", enable);
    }

    int customFontSize() const
    {
        return m_sets.value("appearance/font-size", 0).toInt();
    }

    void setCustomFontSize(int size)
    {
        m_sets.setValue("appearance/font-size", size);
    }

    void sync()
    {
        m_sets.sync();
    }

private:
    Settings()
        : m_sets("lxqt", "app-switcher")
    {
    }

private:
    QSettings m_sets;
};
