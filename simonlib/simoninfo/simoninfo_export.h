#ifndef SIMON_SIMONINFO_EXPORT_H_8CA34A9B8AFC4A6F9E7EE02D02D85646
#define SIMON_SIMONINFO_EXPORT_H_8CA34A9B8AFC4A6F9E7EE02D02D85646
 
// needed for KDE_EXPORT and KDE_IMPORT macros
#include <kdemacros.h>
 
#ifndef SIMONINFO_EXPORT
# if defined(MAKE_SIMONINFO_LIB)
   // We are building this library
#  define SIMONINFO_EXPORT KDE_EXPORT
# else
   // We are using this library
#  define SIMONINFO_EXPORT 
# endif
#endif
 
# ifndef SIMONINFO_EXPORT_DEPRECATED
#  define SIMONINFO_EXPORT_DEPRECATED KDE_DEPRECATED SIMONINFO_EXPORT
# endif
 
#endif
