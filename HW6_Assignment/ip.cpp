#include "ip.h"
#define BYTE 8

/* Will recieve either */
Ip::Ip(const String &rule) : rule_data(rule), type_of_rule(SRC) {

    /* Get the type of rule (Source / Destination) */
    StringArray rule_fields = rule_data.split("=");

    printf("After split %s \n", rule_fields.get(1)->as_string().get_string());
    if (rule_fields.get(0) == nullptr || rule_fields.get(1) == nullptr){
        throw std::invalid_argument("Invalid rule format");
    }

    if ((rule_fields.get(0))->as_string()[0] == 's') {
        type_of_rule = SRC;
    } else {
        type_of_rule = DST;
    }

    /* rule_data_prefix: {138.0.0.10, 24} */
    /* Seperate between ip and prefix*/
    StringArray rule_data_prefix = rule_fields.get(1)->split("/");
    if (rule_data_prefix.get(1) == nullptr){
        throw std::invalid_argument("Invalid rule format");
    }
    prefix = rule_data_prefix.get(1)->to_integer();

    /* Transform the rule ip into int for match function */
    int_rule = Ip::build_ip_to_int((rule_data_prefix.get(0))->as_string());
    
    rule_data_prefix.~StringArray();
}

unsigned int Ip::build_ip_to_int (const String &ip_data) const {
    String data = ip_data;

    /* data_array = {138, 0, 0, 10} */
    StringArray data_array = data.split("."); // split the ip 
    
    unsigned int ip_int = 0;
    unsigned int byte_to_int = 0;

    for (int i = 0; i < 4; i++){
        /* Turn the current byte of data into Uinteger, will start from MSB */
        byte_to_int = data_array.get(i)->to_integer();
        
        ip_int = (ip_int << BYTE) | byte_to_int; // Add the current ip field 
                                                 // and shift left by 8 bits
                                                 // for all besides last byte  
    }

    return ip_int;
}

bool Ip::ip_matches_rule(unsigned int ip, unsigned int rule_ip, int prefix)
                        const{
    int suffix = 32 - prefix;
    unsigned int msk = -1U << suffix;

    unsigned int lo = rule_ip & msk;
    unsigned int hi = lo | (~msk);
    return (ip >= lo) && (ip <= hi);
}

/* Will get the entire packet, need to find relevant field from rule */
bool Ip::match(const GenericString &packet) const{
    String packet_data = packet.as_string();
    packet_data.trim();

    /* Will split the packet by fields */
    StringArray packet_fields = packet_data.split(",");
    for (int i = 0; i < 4; i++){
        packet_fields.get(i)->trim();

        /* Check if the type of rule is the same, if not continue */
        char s_or_d = packet_fields.get(i)->as_string()[0];
        char ip_or_port = packet_fields.get(i)->as_string()[4];

        /* If not ip rule or not the same type of ip rule will continue */
        if (s_or_d != this->type_of_rule || ip_or_port != 'i'){
            continue;
        } else {
            StringArray ip_data = packet_fields.get(i)->split("=");
            
            /* Convert ip string to unsigned int*/
            ip_data.get(1)->trim();
            String ip_to_transfer = (ip_data.get(1))->as_string();
            unsigned int ip_to_check = build_ip_to_int(ip_to_transfer);
            
            if (ip_matches_rule(ip_to_check,this->int_rule,this->prefix)){
                return true;
            }

        }
    }
    return false;
}


