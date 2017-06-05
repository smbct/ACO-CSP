#!/bin/bash

function save {

    str=$(cat outputMaxMin)
    printf "$str\n"

    best=$(printf "$str" | grep -o -E 'best: [-+0-9.e]+' | cut -d ' ' -f2 )

    printf "$1;$best\n" >> $2

}

function run {

    for i in ${seed[@]}
    do

        name="MaxMin/csp-MaxMin-$i.txt"
        rm $name

        printf "instance;best\n" >> $name

        for f in ../instances/*.csp
        do
            # keep only the name of the instance (not "instances/")
            a=$(printf "$f" | grep -o -E 'instances/.*' |cut -d '/' -f2)

            ./../aco_csp "--instance" $f "--algo" "MaxMin" "--seed" $i "--default" > outputMaxMin
            # cat outputMaxMin
            save $a $name
        done
    done

}

declare -a seed=("123" "234" "345" "456" "567" "789" "8910" "91011" "101112" "111213")

run

rm outputMaxMin
