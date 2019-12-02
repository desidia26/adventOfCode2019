#!/bin/bash

calc_fuel () {
    MODULES_IN=("$@")
    TOTAL_FUEL=0
    for MODULE in "${MODULES_IN[@]}"
    do
        MODULE_TRUNCATED=${MODULE%.*}
        let RESULT=($MODULE_TRUNCATED/3)-2
        TOTAL_FUEL=$[TOTAL_FUEL+RESULT]
        while [ $[(RESULT/3)-2] -gt -1 ]
        do
            RESULT=$[(RESULT/3)-2]
            TOTAL_FUEL=$[TOTAL_FUEL+RESULT]
        done
    done
    echo $TOTAL_FUEL
}

declare -a MODULES 
readarray -t MODULES < $1
calc_fuel "${MODULES[@]}"