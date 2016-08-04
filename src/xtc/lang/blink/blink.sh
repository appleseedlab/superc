#!/bin/bash

exec java -classpath $JAVA_DEV_ROOT/classes -ea xtc.lang.blink.Blink $*
