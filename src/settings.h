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
    { return m_sets.value("appearance/lxqt-theme", "ambiance").toString(); }

    void setTheme(const QString& theme)
    { m_sets.setValue("appearance/lxqt-theme", theme); }

    int iconSize() const
    { return m_sets.value("appearance/icon-size", 38).toInt(); }

    void setIconSize(int size)
    { m_sets.setValue("appearance/icon-size", size); }

    int maxDisplayApps() const
    { return m_sets.value("appearance/max-disp-apps", 15).toInt(); }

    void setDisplayApps(int size)
    { m_sets.setValue("appearance/max-disp-apps", size); }

    int maxTextWidth() const
    { return m_sets.value("appearance/max-text-width", 50).toInt(); }

    void setMaxTextWidth(int width)
    { m_sets.setValue("appearance/max-text-width", width); }

    bool filterCurrentDesktop() const
    { return m_sets.value("filter/current-desktop", true).toBool(); }

    void setFilterCurrentDesktop(bool filter)
    { m_sets.setValue("filter/current-desktop", filter); }

    bool filterCurrentScreen() const
    { return m_sets.value("filter/current-screen", true).toBool(); }

    void setFilterCurrentScreen(bool filter)
    { m_sets.setValue("filter/current-screen", filter); }

    void sync()
    { m_sets.sync(); }
private:
    Settings():
        m_sets("lxqt", "app-switcher")
    {}
private:
    QSettings m_sets;
};
