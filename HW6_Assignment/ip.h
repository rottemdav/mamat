#ifndef IP_H
#define IP_H
#include "string.h"
#include "generic-field.h"
#include "string-array.h"

/* The Object is an IP rule */
class Ip : public GenericField {
String rule_data;       // Will only contain the data of the rule (after the = )
Rule_Type type_of_rule; 
unsigned int int_rule;  
int prefix;

public:
    /* Constructor */
    Ip(const String &rule) : rule_data(rule), type_of_rule(SRC) {};

    /* Will convert the ip array into the ip unsigned int */
    unsigned int build_ip_to_int (const String &ip_data) const ;

    /* Will check if the two ip matches */
    bool ip_matches_rule(unsigned int ip, unsigned int rule_ip, int prefix) 
                        const;

    /* */
    bool match(const GenericString &packet) const;

    /* Destructor */
    ~Ip() {};
};

#endif 