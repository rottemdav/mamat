#ifndef STRING_H
#define STRING_H
#include <stdio.h>
#include <string.h> // for strtok function
#include <stdlib.h> // for atoi function
#include <iostream>
#include "generic-string.h"
#include "string-array.h"

class StringArray;

class String : public GenericString {
    char* string;

public:

    String() : string(nullptr) {};

    /* Opeartors override */
    GenericString& operator=(const char *str);

    bool operator==(const GenericString &other) const;
    bool operator==(const char *other) const ;

    /* Class's required function */
    StringArray split(const char *delimiters) const override;
    GenericString& trim();
    int to_integer() const ;
    String& as_string();
    const String& as_string() const;

    /* Destrcutor */
    virtual ~String() {};
};

/* Global function that creates a String class */
GenericString* make_string(const char *str);


#endif STRING_H