### LXQt application switcher.
This is a simple application to switch between applications in lxqt. Have lxqt integration, including theming.
For example ambiance theme it looks like this:

![](https://raw.githubusercontent.com/wiki/zjes/lxqt-appswitcher/images/appswitcher.png)

After installation, to configure this switcher you just go to lxqt-settings/Session Settings and enable this:

![](https://raw.githubusercontent.com/wiki/zjes/lxqt-appswitcher/images/session.png)

And in lxqt-settings/Application switcher setup switcher as you wish.

In openbox, you must disable default application switcher. You can do it in ~/.config/openbox/rc.xml and comment section 
```
<keybind key="A-Tab">
...
</keybind>
```
