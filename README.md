# LXQt application switcher

## Overview

LXQt application switcher is an application switcher, hence a tool to change the active window by cycling
through the available ones, geared towards the [LXQt desktop environment](http://lxqt.org).

![](https://raw.githubusercontent.com/wiki/zjes/lxqt-appswitcher/images/appswitcher.png)

It integrates with LXQt including theming and is meant to be more configurable and featureful than e. g.
its counterpart provided by Openbox.   
(For now theme Ambiance only is supported. Other themes can still be used but make LXQt application
switcher fall back to a default theme.)

## Installation

LXQt component [lxqt-globalkeys](https://github.com/lxde/lxqt-globalkeys) is the only mandatory build- and
runtime dependency as it's needed itself and pulls all other needed dependencies including Qt as well.

LXQt application switcher is relying on CMake and can hence be installed by running `cmake`, `make` and
`make install`, optionally from a dedicated build directory.   
A CMake option like `-DCMAKE_INSTALL_PREFIX=/usr` will be needed most of the time to have the program installed
at paths commonly used these days.

In Arch Linux the tool can be installed via [AUR](https://aur.archlinux.org/) package
[lxqt-appswitcher-git](https://aur.archlinux.org/packages/lxqt-appswitcher-git/).

## Configuration

### Keyboard shortcuts

LXQt application switcher is using the shortcuts defined by lxqt-globalkeys.  
These are configured in dialogue "Global Actions Manager" (binary `lxqt-config-globalkeyshortcuts`) - topics
"[reverse] switch applications" in column "Description". Default settings are `Alt+Tab` and `Alt+Shift+Tab` to
cycle in regular and reverse order respectively.

It must be ensured that these shortcuts aren't used by the window manager. (Technically it's possible to assign
different shortcuts to LXQt application switcher and e. g. an application switcher of a window manager and hence
use the two in parallel. This will hardly ever make sense, though.)   
In **Openbox** [actions](http://openbox.org/wiki/Help:Actions) `NextWindow` and/or `PreviousWindow` have to be
detached from the keyboard [bindings](http://openbox.org/wiki/Help:Bindings). This is best done by uncommenting or
removing the corresponding sections in `~/.config/openbox/rc.xml`. If the file is missing `/etc/xdg/openbox/rc.xml`
can be copied and used as template, the sections themselves will look like
```
<keybind key="A-Tab">
    <action name="NextWindow">
[...]
</keybind>
```
and
```
<keybind key="A-S-Tab">
    <action name="PreviousWindow">
[...]
</keybind>
```
For changes to take effect either start a new session or run `openbox --reconfigure`.   
In **KWin** the shortcuts can be handled from KDE's "System Settings" (binary `systemsettings[5]`) under Workspace -
Window Management - Task Switcher, using **Xfwm4** in dialogue "Window Manager" (binary `xfwm4-settings`), both
times changes take effect at once.

### Auto start

The application itself is run as so-called LXQt Module. As such it has to be enabled from dialogue
"LXQt Session Settings" (binary `lxqt-config-session`).

![](https://raw.githubusercontent.com/wiki/zjes/lxqt-appswitcher/images/session.png)

### Settings

The actual configuration can be tweaked by dialogue "Application switcher" which can be found in LXQt's main panel
menu as well as in the "LXQt Configuration Center".
