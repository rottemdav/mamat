#!/bin/bash

and_clause() {
#  Read all packets from stdin into “$packets” -> $packets and $rule
    local packets="$1"
    local fields="$2"

#  In each iteration, keep only the packets that match the field
    for field in $fields; do
        packets=$(echo "$packets" | ./firewall.exe "$field")
    done

    echo "$packets" | sort | uniq
}

#  Read all packets from stdin into “$packets”
packets=$(cat -)

# Read rule file, convert commas to whitespace
rules=$(sed '/^$/d' "$1" | sed '/^#/d' | sed 's/#.*//')

# All the clean packets
pkts=""
IFS=$'\n'

# In each iteration, append to total packets only those that matched the
# current rule
for rule in $rules; do
    matched_packets=$(and_clause "$packets" "$rule")
    if [ -n "$pkts" ]; then
        pkts+=$'\n'
    fi

# Append matched packets to the total packets
    pkts+="$matched_packets"
    pkts+=$'\n'
done

# Echo the final list of packets. Sort and remove duplicates
echo "$pkts" | sort | uniq | sed 's/* ,/,/g' | sed 's/, */,/g' | \
sed '0,/^$/d' |  sed 's/[ \t]*$//'
