#ifndef STRING_ARRAY_H
#define STRING_ARRAY_H
#include "string.h"
#include <vector>


class StringArray : public GenericString {
    std::vector<GenericString> strings;
    int size;
public:
    /* Constructor */
    StringArray ();
    
    void add(GenericString* str){};

    /* Getter function */
    GenericString* get(size_t index) const;

    /* Dstructor */
    ~StringArray();
    
};

#endif