// java_lang.h            see license.txt for copyright and terms of use
// language options that the parser (etc.) is sensitive to

#ifndef JAVALANG_H
#define JAVALANG_H


// This type is used for options that nominally either allow or
// disallow some syntax, but can also trigger a warning.  Values of
// this type are intended to be tested like booleans in most places.
enum Bool3 {
  B3_FALSE = 0,      // syntax not allowed
  B3_TRUE = 1,       // accepted silently
  B3_WARN = 2,       // accept with a warning
};


class JavaLang {
public:
                     
private:     // funcs
  void setAllWarnings(bool enable);

public:      // funcs
  JavaLang() { }

  // set any B3_TRUE to B3_WARN
  void enableAllWarnings() { setAllWarnings(true); }

  // set any B3_WARN to B3_TRUE
  void disableAllWarnings() { setAllWarnings(false); }
};

#endif // JAVALANG_H
