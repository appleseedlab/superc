// java_lang.cc            see license.txt for copyright and terms of use
// code for java_lang.h

#include "java_lang.h"     // this module

static void setWarning(Bool3 &b, bool enable)
{
  if (enable) {
    if (b == B3_TRUE) {
      b = B3_WARN;       // accept with warning
    }
  }
  else {
    if (b == B3_WARN) {
      b = B3_TRUE;       // accept silently
    }
  }
}

void JavaLang::setAllWarnings(bool enable)
{
}

// EOF
