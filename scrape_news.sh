#!/bin/bash

site="https://ynetnews.com/category/3082"

data=$(wget --no-check-certificate -O - $site 2>/dev/null)

articles=$(echo "$data" | \
            grep -oP "https://(www.)?ynetnews.com/article/[0-9a-zA-Z]+" | \
            sort --parallel=8 | uniq)

process_article() {
    local article=$1

    content=$(wget --no-check-certificate -O - $article 2>/dev/null)

    amount_natanyahu=$(echo "$content" | grep -oP "Netanyahu" | wc -l)
    amount_gantz=$(echo "$content" | grep -oP "Gantz" | wc -l)

    if [ $amount_natanyahu -lt 1 ] && [ $amount_gantz -lt 1 ]; then
        echo "$1, -"
    else
        echo "$1, Netanyahu, $amount_natanyahu, Gantz, $amount_gantz"
    fi
}

for article in $articles; do
    process_article "$article" &
done

wait