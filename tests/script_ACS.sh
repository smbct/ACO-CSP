#!/bin/bash

function save {

    str=$(cat outputACS)
    printf "$str\n"

    best=$(printf "$str" | grep -o -E 'best: [-+0-9.e]+' | cut -d ' ' -f2 )

    printf "$1;$best\n" >> $2

}

function run {

    for i in ${seed[@]}
    do

        name="ACS/csp-ACS-$i.txt"
        rm $name

        printf "instance;best\n" >> $name

        for f in ../instances/*.csp
        do
            # keep only the name of the instance (not "instances/")
            a=$(printf "$f" | grep -o -E 'instances/.*' |cut -d '/' -f2)

            ./../aco_csp "--instance" $f "--algo" "ACS" "--seed" $i "--default" > outputACS
            # cat outputMaxMin
            save $a $name
        done
    done

}

declare -a seed=("123" "234" "345" "456" "567" "789" "8910" "91011" "101112" "111213")


run

rm outputACS
