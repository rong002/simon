#ifndef RECOGNITIONCONTROL_EXPORT_H
#define RECOGNITIONCONTROL_EXPORT_H
 
// needed for KDE_EXPORT and KDE_IMPORT macros
#include <kdemacros.h>
 
#ifndef RECOGNITIONCONTROL_EXPORT
# if defined(MAKE_RECOGNITIONCONTROL_LIB)
   // We are building this library
#  define RECOGNITIONCONTROL_EXPORT KDE_EXPORT
# else
   // We are using this library
#  define RECOGNITIONCONTROL_EXPORT KDE_IMPORT
# endif
#endif
 
# ifndef RECOGNITIONCONTROL_EXPORT_DEPRECATED
#  define RECOGNITIONCONTROL_EXPORT_DEPRECATED KDE_DEPRECATED RECOGNITIONCONTROL_EXPORT
# endif
 
#endif
