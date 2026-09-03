
#ifndef OGL_API_H
#define OGL_API_H

#ifdef OGL_API_STATIC_DEFINE
#  define OGL_API
#  define OPENGL_API_NO_EXPORT
#else
#  ifndef OGL_API
#    ifdef opengl_api_EXPORTS
        /* We are building this library */
#      define OGL_API __declspec(dllexport)
#    else
        /* We are using this library */
#      define OGL_API __declspec(dllimport)
#    endif
#  endif

#  ifndef OPENGL_API_NO_EXPORT
#    define OPENGL_API_NO_EXPORT 
#  endif
#endif

#ifndef OPENGL_API_DEPRECATED
#  define OPENGL_API_DEPRECATED __declspec(deprecated)
#endif

#ifndef OPENGL_API_DEPRECATED_EXPORT
#  define OPENGL_API_DEPRECATED_EXPORT OGL_API OPENGL_API_DEPRECATED
#endif

#ifndef OPENGL_API_DEPRECATED_NO_EXPORT
#  define OPENGL_API_DEPRECATED_NO_EXPORT OPENGL_API_NO_EXPORT OPENGL_API_DEPRECATED
#endif

/* NOLINTNEXTLINE(readability-avoid-unconditional-preprocessor-if) */
#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef OPENGL_API_NO_DEPRECATED
#    define OPENGL_API_NO_DEPRECATED
#  endif
#endif

#endif /* OGL_API_H */
