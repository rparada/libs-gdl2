#
#  Main Makefile for GNUstep Database Library.
#  
#  Copyright (C) 1997,2002,2003,2004,2005 Free Software Foundation, Inc.
#
#  Written by:	Scott Christley <scottc@net-community.com>
#
#  This file is part of the GNUstep Database Library.
#
#  This library is free software; you can redistribute it and/or
#  modify it under the terms of the GNU Library General Public
#  License as published by the Free Software Foundation; either
#  version 2 of the License, or (at your option) any later version.
#
#  This library is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
#  Library General Public License for more details.
#
#  You should have received a copy of the GNU Library General Public
#  License along with this library; see the file COPYING.LIB.
#  If not, write to the Free Software Foundation, Inc.,
#  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
#

include $(GNUSTEP_MAKEFILES)/common.make

include ./Version

PACKAGE_NAME=gnustep-dl2
PACKAGE_VERSION=${VERSION}

SVN_MODULE_NAME=gdl2
SVN_BASE_URL=http://svn.gna.org/svn/gnustep/libs

#
# The list of subproject directories
#
SUBPROJECTS = EOControl EOAccess EOAdaptors Tools

ifeq ($(GUI_MAKE_LOADED),yes)
SUBPROJECTS += EOInterface EOModeler DBModeler
endif

include config.make

DOCUMENT_NAME = GDL2

GDL2_AGSDOC_FILES = GDL2.gsdoc

-include Makefile.preamble

include $(GNUSTEP_MAKEFILES)/aggregate.make
ifeq ($(doc),yes)
include $(GNUSTEP_MAKEFILES)/documentation.make
endif

-include Makefile.postamble

