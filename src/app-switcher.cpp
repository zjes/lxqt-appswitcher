#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
#include <LXQtGlobalKeys/Action>
#include <LXQtGlobalKeys/Client>
#include <QKeyEvent>
#include <QTimer>
#include <kwindowsystem.h>

#include "app-switcher.h"
#include "app-model.h"
#include "app-itemdelegate.h"
#include "settings.h"

AppSwitcher::AppSwitcher(QWidget *parent):
    QListView(parent)
{
    setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint);
    setObjectName("AppSwitcher");

    m_globalShortcut  = GlobalKeyShortcut::Client::instance()->addAction("Alt+Tab", "/app_switcher/switch", tr("Switch applications"), this);
    m_globalRShortcut = GlobalKeyShortcut::Client::instance()->addAction("Shift+Alt+Tab", "/app_switcher/rswitch", tr("Reverse switch applications"), this);

    connect(m_globalShortcut, &GlobalKeyShortcut::Action::activated, [this]{
        if (isVisible())
            selectItem();
        else
            showSwitcher();
    });

    connect(m_globalRShortcut, &GlobalKeyShortcut::Action::activated, [this]{
        if (isVisible())
            selectItem(false);
        else
            showSwitcher(false);
    });

    setItemDelegate(new AppItemDelegate(this));
    setContentsMargins(5, 5, 5, 5);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_timer = new QTimer(this);
    m_timer->setInterval(100);
    m_timer->setSingleShot(true);
    connect(m_timer, &QTimer::timeout, this, &AppSwitcher::timer);
}

void AppSwitcher::showSwitcher(bool forward)
{
    Settings::instance().sync();
    setModel(new AppModel(this));
    dynamic_cast<AppItemDelegate*>(itemDelegate())->init();

    m_current = 0;

    if (!model()->rowCount())
        return;

    QStyleOptionViewItem option;
    QFont fnt = font();
    if (Settings::instance().customFontSizeEnabled()){
        int fontSize = Settings::instance().customFontSize();
        fnt.setPointSize(fontSize);
        option.font.setPointSize(fontSize);
    } else {
        fnt.setPointSize(qApp->font().pointSize());
        option.font.setPointSize(qApp->font().pointSize());
    }
    setFont(fnt);

    int w = 0;
    int h = 0;
    int maxApp = Settings::instance().maxDisplayApps();

    for(int i = 0; i < model()->rowCount(); ++i){
        QSize siz = itemDelegate()->sizeHint(option, model()->index(i, 0));
        w = qMax(w, siz.width());
        h += siz.height();
        if (i > maxApp)
            break;
    }

    resize(w+contentsMargins().left()+contentsMargins().right(), h+contentsMargins().top()+contentsMargins().bottom());

    QRect active = QApplication::desktop()->screenGeometry(QCursor::pos());
    move(active.left()+active.width()/2 - width() / 2, active.top()+active.height()/2 - height() / 2);
    selectItem(forward);
    show();
    m_timer->start();
}

void AppSwitcher::selectItem(bool forward)
{
    m_timer->start();
    m_current += forward ? 1 : -1;
    if(m_current >= model()->rowCount())
        m_current = 0;
    if(m_current < 0)
        m_current = model()->rowCount()-1;

    setCurrentIndex(model()->index(m_current, 0));
}

void AppSwitcher::activateWindow(WId id)
{
    KWindowInfo info(id, NET::WMDesktop);

    if (KWindowSystem::currentDesktop() != info.desktop())
        KWindowSystem::setCurrentDesktop(info.desktop());

    KWindowSystem::forceActiveWindow(id);
}

void AppSwitcher::keyReleaseEvent(QKeyEvent *event)
{
    if (event->modifiers() == 0){
        close();
        activateWindow(model()->data(model()->index(m_current, 0), AppRole::Window).value<WId>());
    }
    QWidget::keyReleaseEvent(event);
}

void AppSwitcher::timer()
{
    if (QApplication::queryKeyboardModifiers() == Qt::NoModifier){
        close();
        activateWindow(model()->data(model()->index(m_current, 0), AppRole::Window).value<WId>());
    } else {
        m_timer->start();
    }
}

void AppSwitcher::closeEvent(QCloseEvent *)
{
    m_timer->stop();
}
