#include "ip.h"
#define BYTE 8

/* Will recieve either */
Ip::Ip(const String &rule) {
    rule_data = rule;
    rule_data.trim();

    /* Get the type of rule (Source / Destination) */
    StringArray rule_fields = rule_data.split('=');
    if (rule_fields.get(0)->as_string[0] == 's') {
        type_of_rule = SRC;
    } else {
        type_of_rule = DST;
    }

    /* rule_data_prefix: {138.0.0.10, 24} */
    /* Seperate between ip and prefix*/
    StringArray rule_data_prefix = rule_fields.get(1)->split('/');
    prefix = rule_data_prefix.get(1)->to_integer();
    
    /* Transform the rule ip into int for match function */
    int_rule = build_ip_to_int(rule_data_prefix.get(0));
    
}

unsigned int Ip::build_ip_to_int (String ip) {
    String data = ip;

    /* data_array = {138, 0, 0, 10} */
    StringArray data_array = ip.split("."); // split the ip 
    
    unsigned int ip_int = 0;
    unsigned int byte_to_int = 0;

    for (int i = 0; i < 4; i++){
        /* Turn the current byte of data into Uinteger, will start from MSB */
        byte_to_int = data_array.get(i)->to_integer();
        
        ip_int += byte_to_int;  // add the current ip field
        ip_int << BYTE;         // Shift left by 8 bit 
    }

    ~data_array;

    return ip_int;
}

bool Ip::ip_matches_rule(unsigned int ip, unsigned int rule_ip, int prefix){
    int suffix = 32 - prefix;
    unsigned int msk = -1U << suffix;

    unsigned int lo = rule_ip & msk;
    unsigned int hi = lo | (~msk);
    return (ip >= lo) && (ip <= hi);
}

/* Will get the entire packet, need to find relevant field from rule */
bool Ip::match(const GenericString &packet) {
    String packet_data = packet.as_string();
    packet_data.trim();

    /* Will split the packet by fields */
    StringArray packet_fields = packet_data.split(",");
    for (int i = 0; i < 4; i++){
        packet_fields.get(i).trim();

        /* Check if the type of rule is the same, if not continue */
        char s_or_d = packet_fields.get(i)->as_string()[0];
        char ip_or_port = packet_fields.get(i)->as_string()[4];

        /* If not ip rule or not the same type of ip rule will continue */
        if (s_or_d != this->type_of_rule || ip_or_port != 'i'){
            continue;
        } else {
            StringArray ip_data = packet_fields.get(i)->split("=");
            
            /* Convert ip string to unsigned int*/
            unsigned int ip_to_check = build_ip_to_int(ip_data.get(1));
            
            if (ip_matches_rule(ip_to_check,this->int_rule,this->prefix)){
                return true;
            } else {
                return false;
            }

        }
    }
}

Ip::~Ip(){
    delete this->rule_data;
}

