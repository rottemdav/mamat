#ifndef STRING_ARRAY_H
#define STRING_ARRAY_H
#include "string.h"


class StringArray : public String {
    GenericString* string_arr[4];

public:
    /* Constructor */
    StringArray ();
    
    /* Getter functions */
    void set_src_ip(const GenericString* src_ip);
    void set_dst_ip(const GenericString* dst_ip);
    void set_src_port(const GenericString* src_port);
    void set_dst_port(const GenericString* dst_port);
    
    /* Setter functions */
    GenericString* get_src_ip();
    GenericString* get_dst_ip();
    GenericString* get_src_port();
    GenericString* get_dst_port();

    /* Dstructor */
    ~StringArray () {};
    
};

#endif