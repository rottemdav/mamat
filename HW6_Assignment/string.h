#ifndef STRING_H
#define STRING_H
#include "generic-string.h"
#include "string-array.h"

class StringArray;

class String : public GenericString {

public:
    /* Opeartors override */
    GenericString& operator=(const char *str);

    bool operator==(const GenericString &other);
    bool operator==(const char *other);

    /* Class's required function */
    StringArray split(const char *delimiters) const;
    GenericString& trim();
    int to_integer();
    
    /* Class's method - enabling access to the string (this) */
    String& as_string();
    const String& as_string() const;

    /* Destrcutor */
    virtual ~String() {};
};

/* Global function that creates a String class */
GenericString* make_string(const char *str);

#endif STRING_H