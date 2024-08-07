#ifndef STRING_H
#define STRING_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include "generic-string.h"
#include "string-array.h"

enum Rule_Type {
    SRC,
    DST
};

class StringArray;

class String : public GenericString {
    char* string;

public:
    char* get_string() const;
    void set_string(const char *str);
    String(const char* str);
    String(const String &other);

    /* Opeartors override */
    GenericString& operator=(const char *str);

    bool operator==(const GenericString &other) const;
    bool operator==(const char *other) const ;

    char operator[](std::size_t index) const;

    /* Class's required function */
    StringArray split(const char *delimiters) const override;
    GenericString& trim();
    int to_integer() const ;
    String& as_string();
    const String& as_string() const;   

    /* Destrcutor */
    virtual ~String();
};

/* Global function that creates a String class */
GenericString* make_string(const char *str);

bool white_space(char letter);

#endif // STRING_H