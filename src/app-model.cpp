#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
#include <kwindowsystem.h>
#include "app-model.h"
#include "settings.h"

AppModel::AppModel(QObject *parent):
    QAbstractListModel(parent)
{
    create();
}

void AppModel::create()
{
    int iconSize = Settings::instance().iconSize();
    bool byDesk = Settings::instance().filterCurrentDesktop();
    bool byScreen = Settings::instance().filterCurrentScreen();

    for(WId wid: KWindowSystem::stackingOrder()){
        KWindowInfo info(wid, NET::WMVisibleName | NET::WMState | NET::XAWMState | NET::WMWindowType);
        NET::WindowType type = info.windowType(NET::AllTypesMask);
        if((type == NET::Normal || type == NET::Dialog || type == NET::Unknown) && filter(wid, byDesk, byScreen)){
            m_list.prepend({wid, info.visibleName(), KWindowSystem::icon(wid, iconSize, iconSize, true)});
        }
    }
}

int AppModel::rowCount(const QModelIndex &/*parent*/) const
{
    return m_list.size();
}

QVariant AppModel::data(const QModelIndex &index, int role) const
{
    switch(role){
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
    if (byDesk){
        if (KWindowSystem::currentDesktop() != info.desktop())
            return false;
    }

    if (byScreen) {
        if (!QApplication::desktop()->screenGeometry(QCursor::pos()).intersects(info.frameGeometry()))
            return false;
    }
    return true;
}
