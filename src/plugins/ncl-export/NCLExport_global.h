/*
 * Copyright 2011-2013 TeleMidia/PUC-Rio.
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either 
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public 
 * License along with this library.  If not, see
 * <http://www.gnu.org/licenses/>. 
 */
#ifndef NCLEXPORT_GLOBAL_H
#define NCLEXPORT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(NCLEXPORT_LIBRARY)
#  define NCLEXPORTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define NCLEXPORTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // NCLEXPORT_GLOBAL_H
