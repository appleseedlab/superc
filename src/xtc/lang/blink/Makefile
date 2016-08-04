
PACKAGE     = xtc.lang.blink
PACKAGE_LOC = xtc/lang/blink

GRAMMARS =  Command
FACTORIES =

SOURCE = \
	$(patsubst %,%Parser.java,$(GRAMMARS)) \
	$(patsubst %,%.java,$(FACTORIES)) \
	$(wildcard *.java)

JNI_SOURCE = 

JAR_EXTRAS = 

ifdef JAVA_DEV_ROOT
include $(JAVA_DEV_ROOT)/Makerules

JAVAC_OPTIONS  = -Xlint:unchecked -d $(CLASS_DIR) -sourcepath $(SOURCE_DIR)

parsers :
	$(RATS) Command.rats
	$(JAVAC) $(JAVAC_OPTIONS) CommandParser.java

documentation : $(patsubst %,doc/xtc.lang.blink.%.html,$(GRAMMARS))

endif
