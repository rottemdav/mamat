#include "input.h"
#include "port.h"
#include "ip.h"

#define ERROR -1

int main(int argc, char const *argv[]) {

    String rule_string = String(argv[1]);
    rule_string.trim();
    char *type = rule_string.get_string(rule_string);
    if (type[4] == 'i'){
        Ip check_ip_rule = Ip(rule_string);
        parse_input(check_ip_rule);
    } else if (type[4] == 'p'){
        Port check_port_rule = Port(rule_string);
        parse_input(check_port_rule);
    } else {
        return ERROR;
    }
   
    return 0;
}