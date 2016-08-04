default: programs

ifdef JAVA_DEV_ROOT
ifndef JAVAC
JAVAC = javac
endif
DJAVAC = $(JAVAC) -classpath . -source 1.5 -g
OSTYPE = $(shell echo $$OSTYPE)
ifdef JAVA_HOME
ifeq (,$(findstring linux,$(OSTYPE)))
  DLL_CC  = $(CC) -g -shared -I $(JAVA_HOME)/include -I $(JAVA_HOME)/include/linux -o 
  DLL_PREFIX = lib
  DLL_SUFFIX = .so
  JNI_DLL_SUFFIX = $(DLL_SUFFIX)
else
ifeq  ($(OSTYPE),cygwin)
  JNI_HDIR=$(shell cygpath $(JAVA_HOME)/include)
  DLL_CC  = gcc -g  -Wall -Wl,--add-stdcall-alias -shared -I $(JNI_HDIR) -I $(JNI_HDIR)/win32 -o
  DLL_PREFIX = 
  DLL_SUFFIX = .dll
  JNI_DLL_SUFFIX = $(DLL_SUFFIX)
else
ifeq ($(OSTYPE),win32)
  DLL_CC = cl /Zi /I "$(JAVA_HOME)/include" /I "$(JAVA_HOME)/include/win32" /LD /Fe
  DLL_PREFIX =
  DLL_SUFFIX = .dll
  JNI_DLL_SUFFIX = $(DLL_SUFFIX)
else
ifneq (,$(findstring darwin,$(OSTYPE)))
  JNI_HDRDIR     = /System/Library/Frameworks/JavaVM.framework/Headers
  DLL_CC = cc -Wall -g $(CFLAGS) -DSPECIALIZE_RELPROD -DSPECIALIZE_AND -DSPECIALIZE_OR -DSMALL_NODES -U__BLOCKS__ -fomit-frame-pointer -fno-common -I$(JNI_HDRDIR) -o
  DLL_PREFIX = lib
  DLL_SUFFIX = .dylib
  JNI_DLL_SUFFIX = .jnilib
else
  $(error uknown OSTYPE = $(OSTYPE))
endif
endif
endif
endif
endif

# JNI programs
JNI_PROGS=PingPong CompoundData BadErrorChecking BadNullArgument
ifeq ($(OSTYPE),win32)
TEST_PROGS=PingPong
JEANNIE_PROGS=
else
TEST_PROGS=$(basename $(basename $(wildcard *.test.exp)))
JEANNIE_PROGS=$(basename $(wildcard *.jni))
endif
PROGS=$(JNI_PROGS) $(JEANNIE_PROGS)

.PHONY: programs jni_programs jeannie_programs check clean

programs: jni_programs jeannie_programs

jni_programs: $(addsuffix .class,$(JNI_PROGS)) $(addsuffix $(JNI_DLL_SUFFIX),$(addprefix $(DLL_PREFIX),$(JNI_PROGS)))

jeannie_programs: $(JEANNIE_PROGS)

check: programs *.test.exp
	for P in $(TEST_PROGS);do env CLASSPATH=.:$(CLASSPATH) expect $${P}.test.exp;done


%: %.jni
	@if [ ! -f $@.class ];then jeannie.sh -g JeannieMain.jni; cp JeannieMain.jni.symbols.ref JeannieMain.jni.symbols;fi

%.class: %.java
	$(DJAVAC) $<

$(DLL_PREFIX)%$(JNI_DLL_SUFFIX): %.c
	$(DLL_CC)$@ $<

clean: 
	rm -f *~ lib*.so *.dll *.class *.ilk  *.pdb *.lib *.obj
	rm -f JeannieMain.i JeannieMain.java JeannieMain.jni.i JeannieMain.jni.pp JeannieMain.jni.symbols
else
  $(error  JAVA_DEV_ROOT is not set)
endif
