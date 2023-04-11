#!/bin/bash

row_helper()
{
    i=`tput cols`
    printf "%"$i"s"|tr ' ' '~'
}

get_parameters()
{
    row_helper
    echo -e "\e[35mInformacje dot. jadra systemu >\e[0m"
    uname -s
    uname -r
    uname -v
    row_helper 
    echo -e "\e[35mInformacje dot. nazwy systemu operacyjnego >\e[0m"
    uname -o
    row_helper
    echo -e "\e[35mInformacje dot. nazwy komputera >\e[0m"
    uname -n
    row_helper
    echo -e "\e[35mInformacje dot. magistrali PCI >\e[0m"
    lspci
    row_helper
    echo -e "\e[35mInformacje dot. magistrali USB >\e[0m"
    lsusb
    row_helper
    echo -e "\e[35mInformacje dot. procesora >\e[0m"
    lscpu
    row_helper
    echo -e "\e[35mInformacje dot. BIOS'u >\e[0m"
    dmidecode -t bios
    row_helper
    echo -e "\e[35mInformacje dot. plyty glownej >\e[0m"
    dmidecode -t baseboard
}

main()
{
    echo -e "\e[44mDominik Jalowiecki > ParameterInfo\e[0m"
    echo -ne "Sprawdzanie parametrow komputera. Prosze czekac " ; get_parameters > /tmp/parameterinfo.tmp
    sleep 2
    for ((z=1 ; z<=3 ; z++));
    do
        echo -ne "."
        sleep 2
    done

    clear
    cat /tmp/parameterinfo.tmp
    echo -e "\e[44mDominik Jalowiecki > ParameterInfo\e[0m"
    echo -en "\e[35mPlik z parametrami zostal zapisany w podanej sciezce > /tmp/parameterinfo.tmp [ENTER]...\e[0m" ; read
}

main