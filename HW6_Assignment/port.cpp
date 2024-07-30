#include "port.h"

/*Constructor Definition*/
Port::Port(const String &rule) : rule_data(nullptr), rule_type(SRC) {
    port_range[0] = 0;
    port_range[1] = 0;
    rule_data = rule;
    rule_data.trim();
    StringArray rules_fields = rule_data.split('=')
    port_range_extract(rule_fields, port_range);

    if (rules_field.get(0)->as_string[0] == 's') {
        rule_type = SRC;
    } else {
        rule_type = DST;
    } 
}

void port_range_extract(const StringArray &rule, int* port_range[2]) {
    //[ ,22-22]
    String splitted_rule = rule.get(1);
    StringArray rule_range = splitted_rule.split('-');
    if (rule_range.size == 2) {
        port_range[0] = rule_range.get(0).to_integer;
        port_range[1] = rule_range.get(1).to_integer;
    }

}

bool Port::match(const GenericString &packet) const {
    String t_packet = packet.as_string();
    t_packet.trim();
    StringArray splitted_packet = t_packet.split(',');
    for (i = 0 ; i < 4 ; i++) {
        splitted_packet.get(i).trim();
        char s_or_d = splitted_packet.get(i)->as_string()[0];
        char ip_or_port = splitted_packet.get(i)->as_string()[4];
    }

    if (s_or_d != this->rule_type || ip_or_port != 'i') {
        continue;
    } else {
        StringArray port_data = splitted_packet.get(i)->split("=");
    }

    String targeted_filed = port_data.get(1);
    StringArray packet_range = targeted_filed.split('-');
    if (packet_range.get(0).to_integer >= rule_range[0] && packet_range.get(1).to_integer <= rule_range[1]){
        return true;
    } else {
        false;
    }
    
}

Port::~Port() {
    delete this->rule_data;
}