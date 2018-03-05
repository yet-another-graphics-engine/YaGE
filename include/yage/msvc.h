#ifndef _YAGE_MSVC_H
#define _YAGE_MSVC_H

#ifdef _MSC_VER

#if _MSC_VER >= 1400 // YaGE officially supports Visual C++ 2005 and higher
#    pragma comment(lib, "atk-1.0.lib")
#    pragma comment(lib, "cairo.lib")
#    pragma comment(lib, "fontconfig.lib")
#    pragma comment(lib, "gailutil.lib")
#    pragma comment(lib, "gdk-win32-3.0.lib")
#    pragma comment(lib, "gdk_pixbuf-2.0.lib")
#    pragma comment(lib, "gio-2.0.lib")
#    pragma comment(lib, "glib-2.0.lib")
#    pragma comment(lib, "gmodule-2.0.lib")
#    pragma comment(lib, "gobject-2.0.lib")
#    pragma comment(lib, "gthread-2.0.lib")
#    pragma comment(lib, "gtk-win32-3.0.lib")
#    pragma comment(lib, "pango-1.0.lib")
#    pragma comment(lib, "pangocairo-1.0.lib")
#    pragma comment(lib, "pangoft2-1.0.lib")
#    pragma comment(lib, "pangowin32-1.0.lib")

#if _MSC_VER == 1400 // Visual C++ 2005
#    ifdef _DEBUG
#        pragma comment(lib, "yagevc8d.lib")
#    else
#        pragma comment(lib, "yagevc8.lib")
#    endif
#elif _MSC_VER == 1500 // Visual C++ 2008
#    ifdef _DEBUG
#        pragma comment(lib, "yagevc9d.lib")
#    else
#        pragma comment(lib, "yagevc9.lib")
#    endif
#elif _MSC_VER == 1600 // Visual C++ 2010
#    ifdef _DEBUG
#        pragma comment(lib, "yagevc10d.lib")
#    else
#        pragma comment(lib, "yagevc10.lib")
#    endif
#elif _MSC_VER == 1700 // Visual C++ 2012
#    ifdef _DEBUG
#        pragma comment(lib, "yagevc11d.lib")
#    else
#        pragma comment(lib, "yagevc11.lib")
#    endif
#elif _MSC_VER == 1800 // Visual C++ 2013
#    ifdef _DEBUG
#        pragma comment(lib, "yagevc12d.lib")
#    else
#        pragma comment(lib, "yagevc12.lib")
#    endif
#elif _MSC_VER == 1900 // Visual C++ 2015 RC
#    ifdef _DEBUG
#        pragma comment(lib, "yagevc14d.lib")
#    else
#        pragma comment(lib, "yagevc14.lib")
#    endif
#elif _MSC_VER == 1910 // Visual C++ 2017
#    ifdef _DEBUG
#        pragma comment(lib, "yagevc15d.lib")
#    else
#        pragma comment(lib, "yagevc15.lib")
#    endif
#endif

#else
#endif // _MSC_VER >= 1400

#endif // _MSC_VER
#endif // _YAGE_MSVC_H
