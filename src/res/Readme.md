# YaGE Theme & YaGE Icon Theme
    
YaGE theme and YaGE icon theme are designed for YaGE programs only,so their content are less than other common GTK themes and GTK icon themes very much.They are inspired by Material Design style.

The YaGE theme and most of YaGE icons are embedded in YaGE library.But still some of YaGE icons can't be embedded by GTK APIs,so they are placed in the YaGE extent icon pack.
    

## Designer

* Shengyun Zhou


## Note

Both of them only support YaGE Windows version.

To let the YaGE icon theme work normally,you should enable `libpixbufloader-svg.dll` first.

Type the following command to enable libpixbufloader-svg.dll:

```
gdk-pixbuf-query-loaders > %GTKDIR%\lib\gdk-pixbuf-2.0\2.10.0\loaders.cache
```
The `%GTKDIR%` is the directory where the GTK lib was installed.
win32_tutorial

Reference: [http://www.gtk.org/download/win32_tutorial.php](http://www.gtk.org/download/win32_tutorial.php)

To use the extent icon pack,please copy the directory `yage-extent-icon-pack\YaGE` to `%GTKDIR%\share\icons`.