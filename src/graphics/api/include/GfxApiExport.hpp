
#ifndef GFX_API_H
#define GFX_API_H

#ifdef GFX_API_STATIC_DEFINE
#  define GFX_API
#  define GRAPHICS_API_NO_EXPORT
#else
#  ifndef GFX_API
#    ifdef graphics_api_EXPORTS
        /* We are building this library */
#      define GFX_API __declspec(dllexport)
#    else
        /* We are using this library */
#      define GFX_API __declspec(dllimport)
#    endif
#  endif

#  ifndef GRAPHICS_API_NO_EXPORT
#    define GRAPHICS_API_NO_EXPORT 
#  endif
#endif

#ifndef GRAPHICS_API_DEPRECATED
#  define GRAPHICS_API_DEPRECATED __declspec(deprecated)
#endif

#ifndef GRAPHICS_API_DEPRECATED_EXPORT
#  define GRAPHICS_API_DEPRECATED_EXPORT GFX_API GRAPHICS_API_DEPRECATED
#endif

#ifndef GRAPHICS_API_DEPRECATED_NO_EXPORT
#  define GRAPHICS_API_DEPRECATED_NO_EXPORT GRAPHICS_API_NO_EXPORT GRAPHICS_API_DEPRECATED
#endif

/* NOLINTNEXTLINE(readability-avoid-unconditional-preprocessor-if) */
#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef GRAPHICS_API_NO_DEPRECATED
#    define GRAPHICS_API_NO_DEPRECATED
#  endif
#endif

#endif /* GFX_API_H */
