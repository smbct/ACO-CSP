#!/bin/bash

function run {

    ./../aco_csp "--instance" "../instances/20-10-10000-1-9.csp" "--algo" "MinMax" "--seed" "123" "--default" "--iterations" "2000" > output

    cat output

    str=$(cat output)
    imp=$(printf "$str" | grep -o -E 'improvement: [-+0-9.e]+' | cut -d ' ' -f2 )
    ev=$(printf "$str" | grep -o -E 'eval: [-+0-9.e]+' | cut -d ' ' -f2 )

    file="20-10-10000-1-9-MinMax"

    printf "evaluation;cost\n" >> $file

    array1=(${ev//"\n"/ })
    array2=(${imp//"\n"/ })

    len=$((${#array1[*]}-1))
    for i in $(seq 0 $len)
    do
        printf "${array1[$i]};${array2[$i]}\n" >> $file
    done

}

run

rm output
