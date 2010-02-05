#ifndef SIMON_SIMONVOICEUI_EXPORT_H_F1032DFE61FA42E3B31933515AF33099
#define SIMON_SIMONVOICEUI_EXPORT_H_F1032DFE61FA42E3B31933515AF33099
 
// needed for KDE_EXPORT and KDE_IMPORT macros
#include <kdemacros.h>
 
#ifndef SIMONVOICEUI_EXPORT
# if defined(MAKE_SIMONVOICEUI_LIB)
   // We are building this library
#  define SIMONVOICEUI_EXPORT KDE_EXPORT
# else
   // We are using this library
#  define SIMONVOICEUI_EXPORT 
# endif
#endif
 
# ifndef SIMONVOICEUI_EXPORT_DEPRECATED
#  define SIMONVOICEUI_EXPORT_DEPRECATED KDE_DEPRECATED SIMONVOICEUI_EXPORT
# endif
 
#endif