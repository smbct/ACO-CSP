#!/bin/bash

function save {

    str=$(cat output)
    printf "$str\n"

    best=$(printf "$str" | grep -o -E 'Best: [-+0-9.e]+' | cut -d ' ' -f2 )
    t=$(printf "$str" | grep -o -E 'Time: [-+0-9.e]+' | cut -d ' ' -f2 )

    printf "$1;$best;$t\n" >> $2

}

function run {

    for i in ${algo[@]}
    do
        for j in ${seed[@]}
        do

            name="csp-$i-$j.txt"
            rm $name

            printf "instance;best\n" >> $name

            for f in instances/*.csp
            do
                # keep only the name of the instance (not "instances/")
                a=$(printf "$f" | grep -o -E 'instances/.*' |cut -d '/' -f2)

                echo $i $j
                ./aco_csp "--instance" $f "--algo" $i "--seed" $j "--default" > output
                save $a $name
            done
        done
    done

}

declare -a algo=("MaxMin" "ACS")
declare -a seed=("123" "234" "345" "456" "567" "789" "8910" "91011" "101112" "111213")


run

rm output
