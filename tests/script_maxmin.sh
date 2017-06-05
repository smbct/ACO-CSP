#!/bin/bash

function save {

    str=$(cat outputMaxMin)
    printf "$str\n"

    best=$(printf "$str" | grep -o -E 'best: [-+0-9.e]+' | cut -d ' ' -f2 )

    printf ";$best" >> $2

}

function run {

    name="MaxMin/csp-MaxMin.txt"
    rm $name

    printf "instance" >> $name
    # all the seeds
    for i in ${seed[@]}
    do
        printf ";$i" >> $name
    done
    printf "\n" >> $name

    for f in ../instances/*.csp
    do

        # keep only the name of the instance (not "instances/")
        a=$(printf "$f" | grep -o -E 'instances/.*' | cut -d '/' -f2)

        # print the instance into the file
        printf "$a" >> $name

        for i in ${seed[@]}
        do
            ./../aco_csp "--instance" $f "--algo" "MaxMin" "--seed" $i "--default" > outputMaxMin
            # cat outputMaxMin
            save $a $name
        done
        printf "\n" >> $name
    done

}

declare -a seed=("123" "234" "345" "456" "567" "789" "8910" "91011" "101112" "111213")

run

rm outputMaxMin
