#ifndef STRING_ARRAY_H
#define STRING_ARRAY_H
#include "generic-string.h"
#include "string.h"



class StringArray {
    std::vector<GenericString*> strings;
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