#!/bin/bash

site="https://ynetnews.com/category/3082"

data=$(wget --no-check-certificate -O - $site 2>/dev/null)

articles=$(echo "$data" | \
            grep -oP "https://(www.)?ynetnews.com/article/[0-9a-zA-Z]+" | \
            sort | uniq) 

for article in $articles; do
    declare -A amount_array
    echo -n "$article,"

    content=$(wget --no-check-certificate -O - $article 2>/dev/null 0)

    amount_natanyahu=$(echo "$content" | grep -oP "Netanyahu" | wc -l)
    amount_gantz=$(echo "$content" | grep -oP "Gantz" | wc -l)

    if [ $amount_natanyahu -lt 1 ] && [ $amount_gantz -lt 1 ]; then
            echo -n " -"
    else 
        echo -n " Netanyahu, $amount_natanyahu, Gantz, $amount_gantz"
    fi
     
    echo
done
echo "$articles"
echo "Total: $(echo "$articles" | wc -l) articles"