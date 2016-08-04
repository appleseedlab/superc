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

PACKAGE     = xtc.lang.jeannie
PACKAGE_LOC = xtc/lang/jeannie

GRAMMARS = Jeannie PreJeannie
FACTORIES = JeannieCFactory JeannieJavaFactory

SOURCE = \
	$(patsubst %,%Parser.java,$(GRAMMARS)) \
	$(patsubst %,%.java,$(FACTORIES)) \
	$(wildcard *.java)

JNI_SOURCE = 

JAR_EXTRAS = 



#***************************************************************************
#
# Include common part of makefile
#
#***************************************************************************

ifdef JAVA_DEV_ROOT
include $(JAVA_DEV_ROOT)/Makerules

JAVAC_OPTIONS  = -Xlint:unchecked -d $(CLASS_DIR) -sourcepath $(SOURCE_DIR)

parsers :
	$(RATS) Jeannie.rats
	$(JAVAC) $(JAVAC_OPTIONS) JeannieParser.java
	$(RATS) PreJeannie.rats
	$(JAVAC) $(JAVAC_OPTIONS) PreJeannieParser.java

analyzers :
	$(JAVAC) $(JAVAC_OPTIONS) Analyzer.java

factories :
	$(FACTORY) -C JeannieCFactory.ffc
	$(JAVAC) $(JAVAC_OPTIONS) JeannieCFactory.java
	$(FACTORY) JeannieJavaFactory.ffj
	$(JAVAC) $(JAVAC_OPTIONS) JeannieJavaFactory.java


documentation : $(patsubst %,doc/xtc.lang.jeannie.%.html,$(GRAMMARS))

doc/xtc.lang.jeannie.PreJeannie.html : PreJeannie.rats
	$(RATS) -silent -processed -html -out doc $<

doc/xtc.lang.jeannie.Jeannie.html : Jeannie.rats JeannieC.rats JeannieJava.rats
	$(RATS) -silent -processed -html -out doc $<

endif
