#pragma once

#include <QListWidget>
#include <QVBoxLayout>
#include <X11/Xlib.h>

namespace GlobalKeyShortcut
{ class Action; }

class AppSwitcher: public QListView
{
    Q_OBJECT
public:
    AppSwitcher(QWidget *parent);
protected:
    void keyReleaseEvent(QKeyEvent *event) override;
    void closeEvent(QCloseEvent *) override;
private:
    void showSwitcher(bool forward = true);
    void selectItem(bool forward = true);
    void timer();
private:
    GlobalKeyShortcut::Action *m_globalShortcut;
    GlobalKeyShortcut::Action *m_globalRShortcut;
    QTimer *m_timer;
    int m_current = 0;
};
