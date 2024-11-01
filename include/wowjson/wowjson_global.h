#ifndef _wowjson_wowjson_global_h_
#define _wowjson_wowjson_global_h_

#if !defined(SAG_COM) && (!defined(WINAPI_FAMILY) || WINAPI_FAMILY==WINAPI_FAMILY_DESKTOP_APP) && (defined(WIN64) || defined(_WIN64) || defined(__WIN64__))
#  define WOW_OS_WIN32
#  define WOW_OS_WIN64
#elif !defined(SAG_COM) && (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
#  if defined(WINAPI_FAMILY)
#    ifndef WINAPI_FAMILY_PC_APP
#      define WINAPI_FAMILY_PC_APP WINAPI_FAMILY_APP
#    endif
#    if defined(WINAPI_FAMILY_PHONE_APP) && WINAPI_FAMILY==WINAPI_FAMILY_PHONE_APP
#      define WOW_OS_WINRT
#    elif WINAPI_FAMILY==WINAPI_FAMILY_PC_APP
#      define WOW_OS_WINRT
#    else
#      define WOW_OS_WIN32
#    endif
#  else
#    define WOW_OS_WIN32
#  endif
#endif
#if defined(__GNUC__)
#  define WOW_CC_GNU
#endif


#if defined(WOW_OS_WIN32) || defined(WOW_OS_WIN64) || defined(WOW_OS_WINRT)
#  define WOW_OS_WIN
#endif

typedef signed char wowint8;
typedef unsigned char wowuint8;
typedef short wowint16;
typedef unsigned short wowuint16;
typedef int wowint32;
typedef unsigned int wowuint32;
#if defined(WOW_OS_WIN) && !defined(WOW_CC_GNU)
typedef __int64 wowint64;
typedef unsigned __int64 wowuint64;
#else
typedef long long wowint64;
typedef unsigned long long wowuint64;
#endif


#ifdef wowjson_EXPORTS
#define wowjson_api __declspec(dllexport)
#else
#define wowjson_api __declspec(dllimport)
#endif // wowjson_EXPORTS

#endif/_wowjson_wowjson_global_h_
