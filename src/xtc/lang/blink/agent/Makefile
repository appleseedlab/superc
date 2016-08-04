PACKAGE     = xtc.lang.blink.agent
PACKAGE_LOC = xtc/lang/blink/agent
SOURCE = $(wildcard *.java)
JNI_SOURCE = 
JAR_EXTRAS = 

.PHONY: agent default

default: classes agent

include $(JAVA_DEV_ROOT)/Makerules

ifndef JAVA_DEV_ROOT
  $(error JAVA_DEV_ROOT must be defined)
endif

ifndef JAVA_HOME
  $(error JAVA_HOME must be defined)
endif


JAVAC_OPTIONS  = -g -Xlint:unchecked -d $(CLASS_DIR) -sourcepath $(SOURCE_DIR)
AGENT_SOURCES=Agent.java AgentVariable.java
AGENT_CLASS_DIR=$(JAVA_DEV_ROOT)/classes/xtc/lang/blink/agent/
AGENT_CLASSES=$(addprefix $(AGENT_CLASS_DIR),$(patsubst	%.java,%.class,$(AGENT_SOURCES)))
AGENT_C_SOURCE_FILES=agent.c agent_main.c util.c state.c \
  j2c_proxy.c c2j_proxy.c agent_class.c options.c jnicheck.c

ifneq (,$(findstring darwin,$(OSTYPE)))
  DLL_CC  = gcc -lm -g -shared -I /System/Library/Frameworks/JavaVM.framework/Headers -o
  AGENT_DLL=$(JAVA_DEV_ROOT)/bin/libjinn.jnilib
else
ifneq (,$(findstring linux,$(OSTYPE)))
  DLL_CC  = gcc -lm -g -shared -I $(JAVA_HOME)/include -I $(JAVA_HOME)/include/linux -o 
  AGENT_DLL=$(JAVA_DEV_ROOT)/bin/libjinn.so
else
ifeq  ($(OSTYPE),mingw)
  DLL_CC  = mingw32-gcc -Wl,--add-stdcall-alias -lm -g -shared -g -I $(JAVA_HOME)/include -I $(JAVA_HOME)/include/win32 -o 
  AGENT_DLL=$(JAVA_DEV_ROOT)/bin/jinn.dll
else
ifeq ($(OSTYPE),win32)
  DLL_CC = cl /Zi /LD /I $(JAVA_HOME)/include /I $(JAVA_HOME)/include/win32 /Fe
  AGENT_DLL=$(JAVA_DEV_ROOT)/bin/jinn.dll
else
  $(error agent does not yet support $(OSTYPE))
endif # win32
endif # mingw
endif # linux
endif # darwin

agent: $(AGENT_DLL) 

$(AGENT_DLL): $(AGENT_C_SOURCE_FILES) 
	$(DLL_CC)$@ $(AGENT_C_SOURCE_FILES)

c2j_proxy.c: GenerateJNIFunctionProxy.java $(CLASS)
	java -ea xtc.lang.blink.agent.GenerateJNIFunctionProxy -o c2j_proxy.c

agent_class.c: $(AGENT_CLASSES) $(CLASS)
	java -ea xtc.lang.blink.agent.GenerateHardcodedJavaClass \
	-h agent_class.h -o agent_class.c \
	class_agent $(AGENT_CLASS_DIR)/Agent.class \
	class_agent_variable $(AGENT_CLASS_DIR)/AgentVariable.class \
	class_agent_jni_assertion_failure $(AGENT_CLASS_DIR)/JNIAssertionFailure.class

cleanagent: 
	rm -f $(AGENT_DLL) $(AGENT_CLASSES)
agent:


