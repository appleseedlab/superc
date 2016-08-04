# (C) Copyright IBM Corp 2005-2007.

# uncomment the following to see in detail what this Makefile is doing
# export VERBOSE_MAKE=true

# put default target before include, otherwise it gets hidden
default: test

ifdef JAVA_DEV_ROOT

JEANNIE_TEST_DIR = $(JAVA_DEV_ROOT)/fonda/jeannie_testsuite
FIND = find

include $(JAVA_DEV_ROOT)/Makerules
include $(JEANNIE_TEST_DIR)/Makerules

TESTS = $(patsubst input/%sugared,%,$(wildcard input/*sugared))

cleanall:
	$(FIND) $(JEANNIE_TEST_DIR) -name '*~' -exec $(RM) \{\} \;
	$(RM) -r tmp
	$(RM) core.*.dmp javacore.*.txt

test: $(foreach TEST,$(TESTS),test_$(TEST))
	@echo ==== integration tests completed ====

test_%: starttest_% tmp/%mangled/output.txt tmp/%sugared/output.txt
	-diff tmp/$*mangled/output.txt tmp/$*sugared/output.txt

starttest_%:
	@echo ==== integration test_$* ====

.PRECIOUS : tmp/%/output.txt tmp/%mangled/Main.class tmp/%sugared/Main.class

tmp/%/output.txt : tmp/%/Main.class
ifdef VERBOSE_MAKE
	@echo ---- running $* ----
	cls=`find tmp/$* -name Main.java`; \
        cls=$${cls#tmp/$*/}; cls=$${cls%.java}; cls=$${cls//\//.}; \
	pth=`find tmp/$* -name Main.java`; pth=$${pth%/Main.java}; \
        export PATH="$$pth:$$PATH"; \
        export LD_LIBRARY_PATH="$$pth:$$LD_LIBRARY_PATH"; \
        $(JAVA) -cp tmp/$* -Djava.library.path=$$pth $$cls > $@
	@echo ---- output $@ ----
	@cat $@
else
	@cls=`find tmp/$* -name Main.java`; \
        cls=$${cls#tmp/$*/}; cls=$${cls%.java}; cls=$${cls//\//.}; \
	pth=`find tmp/$* -name Main.java`; pth=$${pth%/Main.java}; \
        export PATH="$$pth:$$PATH"; \
        export LD_LIBRARY_PATH="$$pth:$$LD_LIBRARY_PATH"; \
        $(JAVA) -cp tmp/$* -Djava.library.path=$$pth $$cls > $@
endif

prepare_%_compilation :
ifdef VERBOSE_MAKE
	@echo ---- compiling $* ----
	@mkdir -p tmp
	cp -R input/$* tmp/$*
else
	@mkdir -p tmp
	@cp -R input/$* tmp/$*
endif

tmp/%mangled/Main.class : prepare_%mangled_compilation
ifdef VERBOSE_MAKE
	@if [ -e tmp/$*mangled/Main.c ]; then \
          src=`find tmp/$*mangled -name '*.c'`; \
	  tgt=tmp/$*mangled/$(DLL_PREFIX)Main$(JNI_DLL_SUFFIX); \
	  echo $(DLL_CC) -lm -o $$tgt $$src; \
	  $(DLL_CC) -lm -o $$tgt $$src; fi
	$(JAVAC) -sourcepath tmp/$*mangled -d tmp/$*mangled tmp/$*mangled/Main.java
else
	@if [ -e tmp/$*mangled/Main.c ]; then \
          src=`find tmp/$*mangled -name '*.c'`; \
	  tgt=tmp/$*mangled/$(DLL_PREFIX)Main$(JNI_DLL_SUFFIX); \
	  $(DLL_CC) -lm -o $$tgt $$src; fi
	@$(JAVAC) -sourcepath tmp/$*mangled -d tmp/$*mangled tmp/$*mangled/Main.java
endif

tmp/%sugared/Main.class : prepare_%sugared_compilation
ifdef VERBOSE_MAKE
	@main=`find tmp/$*sugared -name Main.jni`; \
	  main=$${main#tmp/$*sugared/}; \
	  rest=`find tmp/$*sugared -name '*.c'`; \
	  echo "$(JAVA_DEV_ROOT)/src/xtc/lang/jeannie/jeannie.sh -g -v -sourcepath tmp/$*sugared -d tmp/$*sugared $$main $$rest"; \
	  $(JAVA_DEV_ROOT)/src/xtc/lang/jeannie/jeannie.sh -g -lm -v -sourcepath tmp/$*sugared -d tmp/$*sugared $$main $$rest
else
	@main=`find tmp/$*sugared -name Main.jni`; \
	  main=$${main#tmp/$*sugared/}; \
	  rest=`find tmp/$*sugared -name '*.c'`; \
	  $(JAVA_DEV_ROOT)/src/xtc/lang/jeannie/jeannie.sh -g -lm -sourcepath tmp/$*sugared -d tmp/$*sugared $$main $$rest
endif

endif
