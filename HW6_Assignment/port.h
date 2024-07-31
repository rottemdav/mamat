#ifndef PORT_H
#define PORT_H
#include "generic-field.h"
#include "string.h"
#include "string-array.h"

//range: 0-65535

class Port : public GenericField {
String rule_data;
Rule_Type rule_type;
int port_range[2];

public: 
    /* Constructor*/
    Port(const String &rule) : rule_data(rule), rule_type(SRC), 
                               port_range{0} {};

    /* Extracts the port range from the rule in order to define the bounds*/
    void port_range_extract(StringArray &rule_data, int port_range[2]);

    /* Condition verification - takes the rule data and packets and search 
       for comparison match */
    bool match(const GenericString &packet) const;

    /* Desctructor */
    ~Port() {};

};

#endif