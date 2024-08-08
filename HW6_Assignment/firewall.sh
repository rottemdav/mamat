#!/bin/bash

and_clause() {
#  Read all packets from stdin into “$packets”
    local packets="$1"
    local fields="$2"

# Read rule file
    for field in $fields; do
        packets=$(echo "$packets" | ./firewall.exe "$field")
    done

# In each iteration, keep only the packets that match the field
    echo "$packets" | sort | uniq
}

# Read all packets from stdin into "$packets"
packets=$(cat -)

# Read the rules 
rules=$(cat "$1")

# Holds all matched packets
pkts="" # Holds all matched packets
IFS=$'\n' # Set internal field separator

# Process each rule line by line
for rule in $rules; do
# In each iteration, append to total packets only those that matched the
# current rule
    rule=$(echo "$rule" | sed 's/^[ \t]*//;s/[ \t]*$//')

    matched_packets=$(and_clause "$packets" "$rule")
    
    # Append matched packets to the total packets
    pkts+="$matched_packets"$'\n'
done

# Echo the final list of packets. Sort and remove duplicates
echo -e "$pkts" | sort | uniq