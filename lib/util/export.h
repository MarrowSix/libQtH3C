#ifndef EXPORT_H
#define EXPORT_H

#include <QtGlobal>

#ifdef QH3C_STATIC
#  define QH3C_EXPORT
#elif defined(QH3C_LIBRARY)
#  define QH3C_EXPORT Q_DECL_EXPORT
#else
#  define QH3C_EXPORT Q_DECL_IMPORT
#endif

#endif
