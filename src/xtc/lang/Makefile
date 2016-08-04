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

PACKAGE     = xtc.lang
PACKAGE_LOC = xtc/lang

SOURCE = \
	JavaAstSimplifier.java \
	JavaTypeConverter.java \
	JavaExternalAnalyzer.java \
	JavaNoSourceAnalyzer.java \
	JavaEntities.java \
	JavaAnalyzer.java \
	JavaUnitTests.java \
	JavaPrinter.java \
	JavaRecognizer.java \
	JavaParser.java \
	JavaFiveParser.java \
	JavaSevenParser.java \
	JavaReader.java \
	JavaFiveReader.java \
	JavaSevenReader.java \
	Java.java \
	CAnalyzer.java \
	CCounter.java \
	CFeatureExtractor.java \
	CPrinter.java \
	CParserState.java \
	CParser.java \
	CReader.java \
	C.java \
	CFactoryParser.java \
	JavaFactoryParser.java \
	FactoryFactory.java \
	TypedLambdaParser.java \
	TypedLambdaPrinter.java \
	TypedLambda.java \
	ClassfileSourceRemapper.java \
	SourceMapExtractor.java

JNI_SOURCE =

JAR_EXTRAS = 


#***************************************************************************
#
# Include common part of makefile
#
#***************************************************************************

ifdef JAVA_DEV_ROOT
include $(JAVA_DEV_ROOT)/Makerules

parsers :
	$(RATS) -option 'parser(xtc.lang.JavaRecognizer)' \
		-option genericAsVoid Java.rats
	$(RATS) -option 'parser(xtc.lang.JavaParser)' Java.rats
	$(RATS) -option 'parser(xtc.lang.JavaReader)' \
		-option withParseTree Java.rats
	$(RATS) -option 'parser(xtc.lang.JavaFiveParser)' JavaFive.rats
	$(RATS) -option 'parser(xtc.lang.JavaFiveReader)' \
		-option withParseTree JavaFive.rats
	$(RATS) -option 'parser(xtc.lang.JavaSevenParser)' JavaSeven.rats
	$(RATS) -option 'parser(xtc.lang.JavaSevenReader)' \
		-option withParseTree JavaSeven.rats
	$(RATS) -option 'parser(xtc.lang.CParser)' C.rats
	$(RATS) -option 'parser(xtc.lang.CReader)' -option withParseTree C.rats
	$(RATS) -option 'parser(xtc.lang.TypedLambdaParser)' TypedLambda.rats
	$(RATS) -option 'parser(xtc.lang.JavaFactoryParser)' JavaFactory.rats
	$(RATS) -option 'parser(xtc.lang.CFactoryParser)' CFactory.rats
	$(JAVAC) $(JAVAC_OPTIONS) JavaRecognizer.java
	$(JAVAC) $(JAVAC_OPTIONS) JavaParser.java
	$(JAVAC) $(JAVAC_OPTIONS) JavaReader.java
	$(JAVAC) $(JAVAC_OPTIONS) JavaFiveParser.java
	$(JAVAC) $(JAVAC_OPTIONS) JavaFiveReader.java
	$(JAVAC) $(JAVAC_OPTIONS) JavaSevenParser.java
	$(JAVAC) $(JAVAC_OPTIONS) JavaSevenReader.java
	$(JAVAC) $(JAVAC_OPTIONS) CParser.java
	$(JAVAC) $(JAVAC_OPTIONS) CReader.java
	$(JAVAC) $(JAVAC_OPTIONS) TypedLambdaParser.java
	$(JAVAC) $(JAVAC_OPTIONS) JavaFactoryParser.java
	$(JAVAC) $(JAVAC_OPTIONS) CFactoryParser.java

endif
