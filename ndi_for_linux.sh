#!/bin/bash


arc="$(uname -m)"
dir=$(pwd)/'NDI SDK for Linux'

if [ -d "$dir" ]; then


    if [ "$(uname -m | cut -d 'v' -f 1)" = "arm" ];then
        echo "ASDASD"
        libloc="$(ldconfig -p | grep libz.so.1 | cut -d '>' -f2- | cut -d '/' -f 3)"
        rev="$(cat /proc/cpuinfo | grep Revision | cut -d ':' -f2- | cut -d ' ' -f2-)"
        pi1=("0002" "0003" "0004" "0005" "0006" "0007" "0008" "0009" "000d" "000e" "000f" "0010" "0011" "0012" "0013" "0014" "0015")
        declare -a pi1 || declare -a pi2 || declare -a pi3 || declare -a pi4
        pi1=("0002" "0003" "0004" "0005" "0006" "0007" "0008" "0009" "000d" "000e" "000f" "0010" "0011" "0012" "0013" "0014" "0015" "900021" "900032")
        pi2=("a01040" "a01041" "a21041" "a22042")
        pi3=("a02082" "a020a0" "a22082" "a32082" "a020d3" "9020e0" "a02100")
        pi4=("a03111" "b03111" "b03112" "b03114" "c03111" "c03112" "c03114"  "d03114")
        if [[ "${pi1[@]} " =~ " ${rev} " ]]; then
            sudo ln -f 'NDI SDK for Linux/lib/arm-rpi1-linux-gnueabihf/libndi.so' /lib/
            sudo ln -f 'NDI SDK for Linux/lib/arm-rpi1-linux-gnueabihf/libndi.so' /lib/$libloc/
            sudo ln -f 'NDI SDK for Linux/lib/arm-rpi1-linux-gnueabihf/libndi.so.4' /lib/
            sudo ln -f 'NDI SDK for Linux/lib/arm-rpi1-linux-gnueabihf/libndi.so.4' /lib/$libloc/
            sudo ln -f 'NDI SDK for Linux/lib/arm-rpi1-linux-gnueabihf/libndi.so.4.6.2' /lib/
            sudo ln -f 'NDI SDK for Linux/lib/arm-rpi1-linux-gnueabihf/libndi.so.4.6.2' /lib/$libloc/
            echo "NDI libs linked"  
        elif [[ "${pi2[@]} " =~ " ${rev} " ]]; then
            sudo ln -f 'NDI SDK for Linux/lib/arm-rpi2-linux-gnueabihf/libndi.so' /lib/
            sudo ln -f 'NDI SDK for Linux/lib/arm-rpi2-linux-gnueabihf/libndi.so' /lib/$libloc/
            sudo ln -f 'NDI SDK for Linux/lib/arm-rpi2-linux-gnueabihf/libndi.so.4' /lib/
            sudo ln -f 'NDI SDK for Linux/lib/arm-rpi2-linux-gnueabihf/libndi.so.4' /lib/$libloc/
            sudo ln -f 'NDI SDK for Linux/lib/arm-rpi2-linux-gnueabihf/libndi.so.4.6.2' /lib/
            sudo ln -f 'NDI SDK for Linux/lib/arm-rpi2-linux-gnueabihf/libndi.so.4.6.2' /lib/$libloc/
            echo "NDI libs linked" 
        elif [[ "${pi3[@]} " =~ " ${rev} " ]]; then
            sudo ln -f 'NDI SDK for Linux/lib/arm-rpi3-linux-gnueabihf/libndi.so' /lib/
            sudo ln -f 'NDI SDK for Linux/lib/arm-rpi3-linux-gnueabihf/libndi.so' /lib/$libloc/
            sudo ln -f 'NDI SDK for Linux/lib/arm-rpi3-linux-gnueabihf/libndi.so.4' /lib/
            sudo ln -f 'NDI SDK for Linux/lib/arm-rpi3-linux-gnueabihf/libndi.so.4' /lib/$libloc/
            sudo ln -f 'NDI SDK for Linux/lib/arm-rpi3-linux-gnueabihf/libndi.so.4.6.2' /lib/
            sudo ln -f 'NDI SDK for Linux/lib/arm-rpi3-linux-gnueabihf/libndi.so.4.6.2' /lib/$libloc/
            echo "NDI libs linked" 
        elif [[ "${pi2[@]} " =~ " ${rev} " ]]; then
            echo "WARNGING: Using unsupported Version of NDI for the raspberry pi 4"
            sudo ln -f 'NDI SDK for Linux/lib/arm-rpi3-linux-gnueabihf/libndi.so' /lib/
            sudo ln -f 'NDI SDK for Linux/lib/arm-rpi3-linux-gnueabihf/libndi.so' /lib/$libloc/
            sudo ln -f 'NDI SDK for Linux/lib/arm-rpi3-linux-gnueabihf/libndi.so.4' /lib/
            sudo ln -f 'NDI SDK for Linux/lib/arm-rpi3-linux-gnueabihf/libndi.so.4' /lib/$libloc/
            sudo ln -f 'NDI SDK for Linux/lib/arm-rpi3-linux-gnueabihf/libndi.so.4.6.2' /lib/
            sudo ln -f 'NDI SDK for Linux/lib/arm-rpi3-linux-gnueabihf/libndi.so.4.6.2' /lib/$libloc/
            echo "NDI libs linked"  
        else
            echo "Something went wrong"
        fi 
    
    elif [ "$arc" = "x86_64" ]; then 

        libloc="$(ldconfig -p | grep libz.so.1 | cut -d '>' -f2- | cut -d '/' -f 3)"

        sudo ln -f 'NDI SDK for Linux/lib/x86_64-linux-gnu/libndi.so' /lib
        sudo ln -f 'NDI SDK for Linux/lib/x86_64-linux-gnu/libndi.so' /lib/$libloc/
        sudo ln -f 'NDI SDK for Linux/lib/x86_64-linux-gnu/libndi.so.4' /lib
        sudo ln -f 'NDI SDK for Linux/lib/x86_64-linux-gnu/libndi.so.4' /lib/$libloc/
        sudo ln -f 'NDI SDK for Linux/lib/x86_64-linux-gnu/libndi.so.4.6.2' /lib
        sudo ln -f 'NDI SDK for Linux/lib/x86_64-linux-gnu/libndi.so.4.6.2' /lib/$libloc/   
        echo "NDI libs linked"  
    
    elif [ "$arc" = "i686" ]; then

        libloc="$(ldconfig -p | grep libz.so.1 | cut -d ">" -f2- | cut -d "/" -f 3)"
        sudo ln -f 'NDI SDK for Linux/lib/i686-linux-gnu/libndi.so' /lib
        sudo ln -f 'NDI SDK for Linux/lib/i686-linux-gnu/libndi.so' /lib/$libloc
        sudo ln -f 'NDI SDK for Linux/lib/i686-linux-gnu/libndi.so.4' /lib
        sudo ln -f 'NDI SDK for Linux/lib/i686-linux-gnu/libndi.so.4' /lib/$libloc
        sudo ln -f 'NDI SDK for Linux/lib/i686-linux-gnu/libndi.so.4.6.2' /lib
        sudo ln -f 'NDI SDK for Linux/lib/i686-linux-gnu/libndi.so.4.6.2' /lib/$libloc 
        echo "NDI libs moved"  
    fi
    libloc="$(ldconfig -p | grep libz.so.1 | cut -d ">" -f2- | cut -d "/" -f 3)"
else 
    echo "Move 'NDI SDK for Linux' to $(pwd)"
    
fi

#echo ${pi1[@]}
exit