default: programs

ifdef JAVA_DEV_ROOT
ifndef JAVAC
JAVAC = javac
endif
DJAVAC = $(JAVAC) -classpath . -source 1.5 -g
OSTYPE = $(shell echo $$OSTYPE)
ifdef JAVA_HOME
ifneq (,$(findstring linux,$(OSTYPE)))
  DLL_CC  = $(CC) -g -shared -I $(JAVA_HOME)/include -I $(JAVA_HOME)/include/linux -o 
  DLL_PREFIX = lib
  DLL_SUFFIX = .so
  JNI_DLL_SUFFIX = $(DLL_SUFFIX)
else
ifeq  ($(OSTYPE),cygwin)
  JNI_HDIR=$(shell cygpath $(JAVA_HOME)/include)
  DLL_CC  = gcc -g -mno-cygwin -Wall -Wl,--add-stdcall-alias -shared -I $(JNI_HDIR) -I $(JNI_HDIR)/win32 -o
  DLL_PREFIX = 
  DLL_SUFFIX = .dll
  JNI_DLL_SUFFIX = $(DLL_SUFFIX)
else
ifeq ($(OSTYPE),win32)
  DLL_CC = cl /Zi /I $(JAVA_HOME)/include /I $(JAVA_HOME)/include/win32 /LD /Fe
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
PROGS=$(basename $(wildcard *.java))

.PHONY: programs test clean

programs:  $(addsuffix .class,$(PROGS)) $(addsuffix $(JNI_DLL_SUFFIX),$(addprefix $(DLL_PREFIX),$(PROGS)))

%.class: %.java
	$(DJAVAC) $<

$(DLL_PREFIX)%$(JNI_DLL_SUFFIX): %.c
	$(DLL_CC)$@ $<

test:
	perl jinn.test.pl

clean: 
	for P in $(PROGS);do \
	  rm -f $${P}.class ${DLL_PREFIX}$${P}${JNI_DLL_SUFFIX};\
	done
	rm -f *~

else
  $(error  JAVA_DEV_ROOT is not set)
endif
