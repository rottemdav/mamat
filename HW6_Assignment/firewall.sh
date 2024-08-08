#!/bin/bash

and_clause() {
    local packets="$1"
    local fields="$2"

    for field in $fields; do
        packets=$(echo "$packets" | ./firewall.exe "$field")
    done

    echo "$packets" | sort | uniq
}

packets=$(cat -)

rules=$(sed '/^$/d' "$1" | sed '/^#/d' | sed 's/#.*//')

pkts=""
IFS=$'\n'

for rule in $rules; do
    #clean_rule=$(echo "$rule" | sed 's/^[ \t]*//' | sed 's/[ \t]*$//' | sed 's/ * , */,/g')

    matched_packets=$(and_clause "$packets" "$rule")

    if [ -n "$pkts" ]; then
        pkts+=$'\n'
    fi
    pkts+="$matched_packets"
    pkts+=$'\n'
done

echo "$pkts" | sort | uniq | sed 's/* ,/,/g' | sed 's/, */,/g' | \
sed '0,/^$/d' |  sed 's/[ \t]*$//'
