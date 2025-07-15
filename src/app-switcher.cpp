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

#include "app-itemdelegate.h"
#include "app-model.h"
#include "settings.h"
#include <LXQtGlobalKeys/Action>
#include <LXQtGlobalKeys/Client>
#include <QApplication>
#include <QDebug>
#include <QScreen>
#include <QKeyEvent>
#include <QScreen>
#include <QTimer>
#include <KX11Extras>
#include <KWindowInfo>

// Should be after Qt headers
#include "app-switcher.h"

AppSwitcher::AppSwitcher(QWidget* parent)
    : QListView(parent)
{
    setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint);
    setObjectName("AppSwitcher");

    m_globalShortcut = GlobalKeyShortcut::Client::instance()->addAction(
        "Alt+Tab", "/app_switcher/switch", tr("Switch applications"), this);
    m_globalRShortcut = GlobalKeyShortcut::Client::instance()->addAction(
        "Shift+Alt+Tab", "/app_switcher/rswitch", tr("Reverse switch applications"), this);

    connect(m_globalShortcut, &GlobalKeyShortcut::Action::activated, [this] {
        if (isVisible()) {
            selectItem();
        } else {
            showSwitcher();
        }
    });

    connect(m_globalRShortcut, &GlobalKeyShortcut::Action::activated, [this] {
        if (isVisible()) {
            selectItem(false);
        } else {
            showSwitcher(false);
        }
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

    if (!model()->rowCount()) {
        return;
    }

    QStyleOptionViewItem option;
    QFont                fnt = font();
    if (Settings::instance().customFontSizeEnabled()) {
        int fontSize = Settings::instance().customFontSize();
        fnt.setPointSize(fontSize);
        option.font.setPointSize(fontSize);
    } else {
        fnt.setPointSize(qApp->font().pointSize());
        option.font.setPointSize(qApp->font().pointSize());
    }
    setFont(fnt);

    int w      = 0;
    int h      = 0;
    int maxApp = Settings::instance().maxDisplayApps();

    for (int i = 0; i < model()->rowCount(); ++i) {
        QSize siz = itemDelegate()->sizeHint(option, model()->index(i, 0));
        w         = qMax(w, siz.width());
        h += siz.height();
        if (i > maxApp)
            break;
    }

    resize(w + contentsMargins().left() + contentsMargins().right(),
        h + contentsMargins().top() + contentsMargins().bottom());

    QRect active = QGuiApplication::screenAt(QCursor::pos())->geometry();
    move(active.left() + active.width() / 2 - width() / 2, active.top() + active.height() / 2 - height() / 2);
    selectItem(forward);
    show();
    m_timer->start();
}

void AppSwitcher::selectItem(bool forward)
{
    m_timer->start();
    m_current += forward ? 1 : -1;
    if (m_current >= model()->rowCount()) {
        m_current = 0;
    }
    if (m_current < 0) {
        m_current = model()->rowCount() - 1;
    }

    setCurrentIndex(model()->index(m_current, 0));
}

void AppSwitcher::activateWindow(WId id)
{
    KWindowInfo info(id, NET::WMDesktop);

    if (KX11Extras::currentDesktop() != info.desktop()) {
        KX11Extras::setCurrentDesktop(info.desktop());
    }

    KX11Extras::forceActiveWindow(id);
}

void AppSwitcher::keyReleaseEvent(QKeyEvent* event)
{
    if (event->modifiers() == 0) {
        close();
        activateWindow(model()->data(model()->index(m_current, 0), AppRole::Window).value<WId>());
    }
    QWidget::keyReleaseEvent(event);
}

void AppSwitcher::timer()
{
    if (QApplication::queryKeyboardModifiers() == Qt::NoModifier) {
        close();
        activateWindow(model()->data(model()->index(m_current, 0), AppRole::Window).value<WId>());
    } else {
        m_timer->start();
    }
}

void AppSwitcher::closeEvent(QCloseEvent*)
{
    m_timer->stop();
}
