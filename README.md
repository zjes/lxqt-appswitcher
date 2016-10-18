# LXQt application switcher

## Overview

LXQt application switcher is an application switcher, hence a tool to change the active window by cycling through the available ones, geared towards the [LXQt desktop environment](http://lxqt.org).   

![](https://raw.githubusercontent.com/wiki/zjes/lxqt-appswitcher/images/appswitcher.png)

It integrates closely with LXQt including theming and is meant to be more configurable and featureful than e. g. its counterpart provided by Openbox.   
(For now theme Ambiance only is supported. Other themes can still be used but make LXQt application switcher fall back to a default theme.)   

## Installation

### Compiling source code

The application's runtime dependencies are Qt Base, KWindowSystem, [liblxqt](https://github.com/lxde/liblxqt) and [lxqt-globalkeys](https://github.com/lxde/lxqt-globalkeys). To build CMake is needed, optionally Git to clone VCS code.   

Code configuration is handled by CMake, its variable `CMAKE_INSTALL_PREFIX` has to be set to `/usr` most of the time.   

To build run `make`, to install `make install` which accepts variable `DESTDIR` as usual.   

### Binary packages

These aren't exactly wide-spread so far. In Arch Linux the application can be installed via [AUR](https://aur.archlinux.org/) package [lxqt-appswitcher-git](https://aur.archlinux.org/packages/lxqt-appswitcher-git/).   

## Configuration

### Keyboard shortcuts

LXQt application switcher is using the shortcuts configured by [lxqt-globalkeys](https://github.com/lxde/lxqt-globalkeys).   
These are configured in dialogue "Global Actions Manager" (binary `lxqt-config-globalkeyshortcuts`) - topics "[reverse] switch applications" in column "Description". Default settings are `Alt+Tab` and `Alt+Shift+Tab` to cycle in regular and reverse order respectively.   

It must be ensured that these shortcuts aren't used by the window manager. (Technically it's possible to assign different shortcuts to LXQt application switcher and e. g. an application switcher of a window manager and hence use the two in parallel. This will hardly ever make sense, though.)   
In **Openbox** [actions](http://openbox.org/wiki/Help:Actions) `NextWindow` and/or `PreviousWindow` have to be detached from the keyboard [bindings](http://openbox.org/wiki/Help:Bindings). Unfortunately a really convenient GUI to handle this does not exist so editing the user specific configuration file is needed. As of LXQt release 0.11 this is file `~/.config/openbox/lxqt-rc.xml` as far as LXQt sessions are concerned, see section [LXQt specific configuration of window manager Openbox](https://github.com/lxde/lxqt-common#lxqt-specific-configuration-of-window-manager-openbox) in file `README.md` of [lxqt-common](https://github.com/lxde/lxqt-common) to which the configuration file's template belongs. The sections themselves are
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
In **KWin** the shortcuts can be handled from KDE's "System Settings" (binary `systemsettings[5]`) under Workspace - Window Management - Task Switcher, using **Xfwm4** in dialogue "Window Manager" (binary `xfwm4-settings`), both times changes take effect at once.   

### Auto start

The application itself is run as so-called [LXQt Module](https://github.com/lxde/lxqt-session#lxqt-modules). As such it has to be enabled from dialogue "LXQt Session Settings" (binary `lxqt-config-session`) of [lxqt-session](https://github.com/lxde/lxqt-session).   

![](https://raw.githubusercontent.com/wiki/zjes/lxqt-appswitcher/images/session.png)

### Settings

The actual configuration can be tweaked by dialogue "Application switcher" which can be found in LXQt's main panel menu as well as in the [LXQt Configuration Center](https://github.com/lxde/lxqt-config#configuration-center).   
