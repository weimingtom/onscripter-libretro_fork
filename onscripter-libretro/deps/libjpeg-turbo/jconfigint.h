/* libjpeg-turbo build number */
#define BUILD "0"

/* Compiler's inline keyword */
#include <retro_inline.h>

/* Define to the full name of this package. */
#define PACKAGE_NAME "jpeg-turbo"

/* Version number of package */
#define VERSION "80"

#if defined(_MSC_VER) && defined(HAVE_INTRIN_H)
#if (SIZEOF_SIZE_T == 8)
#define HAVE_BITSCANFORWARD64
#elif (SIZEOF_SIZE_T == 4)
#define HAVE_BITSCANFORWARD
#endif
#endif

#if defined(__has_attribute)
#if __has_attribute(fallthrough)
#define FALLTHROUGH  __attribute__((fallthrough));
#else
#define FALLTHROUGH
#endif
#else
#define FALLTHROUGH
#endif

