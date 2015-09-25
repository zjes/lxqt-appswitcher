#include <QDebug>
#include <QApplication>
#include <QFile>
#include <LXQt/lxqtsettings.h>
#include <LXQt/Application>
#include "src/app-switcher.h"
#include "src/settings.h"

LXQt::LXQtTheme currentTheme()
{
    QString themeName = Settings::instance().theme();
    for(const LXQt::LXQtTheme & theme: LXQt::LXQtTheme::allThemes()){
        if (theme.name() == themeName)
            return theme;
    }
    return LXQt::LXQtTheme::currentTheme();
}

int main(int argc, char *argv[])
{
    LXQt::Application app(argc, argv);
    app.setQuitOnLastWindowClosed(false);

    LXQt::LXQtTheme theme = currentTheme();
    qDebug() << theme.name();
    if(QFile::exists(theme.path()+"/lxqt-app-switcher.qss")){
        app.setStyleSheet( "file:///" + theme.path()+"/lxqt-app-switcher.qss");
    }

    QWidget hiddenPreviewParent(0, Qt::Tool);
    AppSwitcher switcher(&hiddenPreviewParent);

    return app.exec();
}

