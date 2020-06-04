#!/bin/sh

TOTAL=0
VALIDATED=0

for entry in 'tests/*'
do
    NOPATH1=$(basename -- "$entry")

    TOTAL=$((TOTAL+1))
    FILE=${NOPATH1%%.*}
    echo -e "\033[33m-------$FILE-------\033[0m"

    #execute pgn
    ./MarioLANG $entry >> tests/$FILE.tmp

    for entry2 in 'tests/out/*'
    do
        NOPATH2=$(basename -- "$entry2")
        OUT=${NOPATH2%%.*}

        if [ "$OUT" = "$FILE" ]; then
            diff --color tests/$FILE.tmp $entry2
            if [ "$?" = 0 ]; then
                VALIDATED=$((VALIDATED+1))
                echo -e "\033[32m[OK]\033[0m"
            fi
        fi
    done
    echo
done

echo

if [ $VALIDATED = $TOTAL ]; then
    echo -e "\033[32m $VALIDATED\033[0m files succeeded on $TOTAL"
else
    echo -e "\033[31m $VALIDATED\033[0m files succeeded on $TOTAL"
fi

# Delete temp file
cd tests/
rm *.tmp

