#include "port.h"

/*Constructor Definition*/
Port::Port(const String &rule) : rule_data(rule), rule_type(SRC) {
    port_range[0] = 0;
    port_range[1] = 0;
    rule_data = rule;
    rule_data.trim();
    StringArray rules_fields = rule_data.split("=");
    port_range_extract(rules_fields, port_range);

    if ((rules_fields.get(0))->as_string()[0] == 's') {
        rule_type = SRC;
    } else {
        rule_type = DST;
    } 
}

void Port::port_range_extract(StringArray &rule, int port_range[2]) {
    //[ ,22-22]
    String splitted_rule = (rule.get(1))->as_string();
    StringArray rule_range = splitted_rule.split("-");
    
    port_range[0] = (rule_range.get(0))->to_integer();
    port_range[1] = (rule_range.get(1))->to_integer();
    

}

bool Port::match(const GenericString &packet) const {
    String t_packet = packet.as_string();
    t_packet.trim();
    StringArray splitted_packet = t_packet.split(",");
    for (int i = 0 ; i < 4 ; i++) {
        (splitted_packet.get(i))->trim();
        char s_or_d = splitted_packet.get(i)->as_string()[0];

        if (((s_or_d == 's') && (this->rule_type == DST)) || 
            ((s_or_d == 'd') && (this->rule_type == SRC))){
            continue;
        }

        char ip_or_port = splitted_packet.get(i)->as_string()[4];
    
    if (ip_or_port != 'p') {
        continue;
    } else {
    StringArray port_data = splitted_packet.get(i)->split("=");

    String target_port = (port_data.get(1))->as_string();
    int port = target_port.to_integer();
    if ((port >= port_range[0]) &&
         (port <= port_range[1])){
        return true;
    } 
    }
    
    }
    return false;
}

