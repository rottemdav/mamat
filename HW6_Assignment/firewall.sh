# #!/bin/bash

# # Read all packets from stdin into “$packets”
# packets=$(cat -)

# # Read rule file, convert commas to whitespace
# fields=$(cat $1 | sed ‘s/,/ /g’)

# # In each iteration, keep only the packets that match the field
# for field in $fields; do
#  packets=$(echo “$packets” | ./firewall.exe “$field”)
# done

# # Echo the final list of packets. Sort and remove duplicates
# echo “$packets” | sort | uniq

#!/bin/bash

# Check if the correct number of arguments is provided
if (( $# >2 )); then
        echo "Wrong number of arguments" >&2
        exit 1
fi
#the first argument is the rules file
#rules include the lines trimmed
rules=$(sed '/^$/d' "$1" | sed '/^#/d' | sed 's/#.*//')
#good_ptks=""
og_stdin=$(cat | sed 's/ //g')
while IFS= read -r line; do
        input="$og_stdin"
        fields=$(echo "$line" | awk -F ',' '{for (i=1; i<=NF; i++) print $i}')
        for field in $fields; do
                input=$(echo "$input" | ./firewall.exe "$field")
        done
        good_ptks+="$input"$'\n'
done < <(echo "$rules")
echo "$(echo "$good_ptks" | sort -u | sed '1d')"