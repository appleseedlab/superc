# Makefile 2
#***************************************************************************
#
# Java development root directory.
#
# (C) 1999 Jacob Dreyer - Geotechnical Software Services
# jacob.dreyer@geosoft.no - http://geosoft.no
#
# Modifications Copyright (C) 2001, 2004 Robert Grimm
# rgrimm@alum.mit.edu
#
# Modifications Copyright (C) 2007 New York University
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#
#***************************************************************************




#***************************************************************************
#
# This section describes the current package.
#
# o PACKAGE     - The complete package name.
# o PACKAGE_LOC - Same as PACKAGE but with "/"s instead of "."s.
# o SOURCE      - List of the source files. Remember extension.
# o JNI_SOURCE  - Files from SOURCE that are to be built with the JAVAH
#                 compiler.
# o JAR_EXTRAS  - None-class files and directories that are to be bundled
#                 into the jar archive.
#
#***************************************************************************

PACKAGE     = superc.cdesugarer
PACKAGE_LOC = superc/cdesugarer

SOURCE = \
	CParseTables.java \
	CTag.java \
	CLexer.java \
	CLexerCreator.java \
	CTokenCreator.java \
	CValues.java \
	NamedFunctionT.java \
	OldSymbolTable.java \
	SymbolTable.java \
	Multiverse.java \
	TypeSpecifier.java \
	Declarator.java \
	Initializer.java \
	Declaration.java \
	DesugarOps.java \
	CContext.java \
	CActions.java

JNI_SOURCE =

JAR_EXTRAS =


#***************************************************************************
#
# Include common part of makefile
#
#***************************************************************************

ifdef JAVA_DEV_ROOT
include $(JAVA_DEV_ROOT)/Makerules

.PHONY: parser clobber

generate:
	$(MAKE) -f generate.make

clobber:
	$(MAKE) -f generate.make clean

endif
