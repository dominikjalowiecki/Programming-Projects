#!/bin/bash

echo y | apt-get install net-tools > nul
echo y | apt-get install vnstat > nul

calosc()
{
	usecpu()
	{
		#ps -eo comm,pcpu | awk '{print $2}' | sort -t '.' -k2 | tail -5 > /tmp/cpuuse.tmp
		#ps -eo comm,pcpu | sort -t '.' -k2 | tail -5 | awk '{print $1}' > /tmp/cpuuse2.tmp
		#cpuuse32=&(/tmp/cpuuse2.tmp)
		#ps -eo comm,pcpu | sort -k2 -g | tail -5 > /tmp/usecpu.tmp
		#read -p "hfsfhsdkfhsdjk"
		#cat /tmp/usecpu.tmp | sort -nrk 2 | head |cut -d " " -f1 > /tmp/usecpu1.tmp
		#cat /tmp/usecpu.tmp | sort -nrk 2 | head  > /tmp/usecpu2.tmp
		#ps -eo comm,pcpu | sort -t '.' -k1.18,1.20 | cut -c 18- > /tmp/cpuuse.tmp
		#ps -eo comm,pcpu | sort -t '.' -k1.18,1.20 | cut -c-17 | tail -n 6 | head -n 5 > /tmp/cpuuse2.tmp
		ps -eo comm,pcpu | sort -t '.' -k1.18,1.20 | tail -n 6 | head -n 5 > /tmp/cpuuse.tmp
		#printf "%-1s %-15s %-1s %-15s %-1s %-20s %-1s %-15s %-1s %-20s %-1s %s\n" "|" "" "" "" "" "CPUuse " "" "" "" "" "|"
		printf "%-1s %-15s %-1s %-15s %-1s \e[95m%-20s\e[0m %-1s \e[7;96m%-15s\e[0m %-1s %-20s %-1s %s\n" "|" "Procesy" "|" "UzycieCPU" "|" "Numer ID" "|" "Z-zamknij" "|" "" "|"
		for a in 1 2 3 4 5
		do
			#echo $cpuse
			proc1=$(cat /tmp/cpuuse.tmp | cut -c-17 | sed -n "$a"p | tr -d ' ')
			proc2=$(cat /tmp/cpuuse.tmp | cut -c 18- | sed -n "$a"p | tr -d ' ')
			printf "%-1s %-15s %-1s %-15s %-1s \e[95m%-20s\e[0m %-1s %-15s %-1s %-20s %-1s %s\n" "|" "$proc1" "" "$proc2" "" "$a" "|" "" "" "" "|"
		done
		#sleep 2
		#clear usecpu
		#usecpu
		printf "%-1s %-15s %-1s %-15s %-1s %-20s %-1s %-15s %-1s %-20s %-1s %s\n" "|" "" "" "" "" "" "|" "---------------" "-" "--------------------" "|"
	}

	statlan()
	{
		vnstat  > /tmp/lan.tmp
		odebrane=$(cat /tmp/lan.tmp|grep "'18"|awk '{print $3}')
		odebrane2=$(cat /tmp/lan.tmp|grep "'18"|awk '{print $4}')
		wyslane=$(cat /tmp/lan.tmp|grep "'18"|awk '{print $6}')
		wyslane2=$(cat /tmp/lan.tmp|grep "'18"|awk '{print $7}')

		odebrane=$(echo $odebrane $odebrane2)
		wyslane=$(echo $wyslane $wyslane2)
	}

	info()
	{
		ramt=$(free -m |grep [0-9]|head -n 1|awk '{print $2}')
		ramf=$(free -m |grep [0-9]|head -n 1 |awk '{print $4}')
		ramu=$(free -m |grep [0-9]|head -n 1 |awk '{print $3}')
		ram=$(cat /proc/meminfo |grep MemTotal |awk '{print $2}')
		cpu1=$(cat /proc/cpuinfo |grep "model name" |head -n 1| cut -f2 -d:|awk '{print $1}')
		cpu2=$(cat /proc/cpuinfo |grep "model name" |head -n 1| cut -f2 -d:|awk '{print $2}')
		cpu5=$(cat /proc/cpuinfo |grep "model name" |head -n 1| cut -f2 -d:|awk '{print $3}')
		cpu3=$(cat /proc/cpuinfo |grep "model name" |head -n 1| cut -f2 -d:|awk '{print $4}')
		cpu4=$(cat /proc/cpuinfo |grep "model name" |head -n 1| cut -f2 -d:|awk '{print $6}')
		rdzenie=$( cat /proc/cpuinfo |grep "model name" | wc -l)
		hdd=$(df -H | grep ^/dev/ |cut -f3 -d '/'|awk '{print $1}'| tr '\n' ' ')
		os=$(uname)
		lan=$( ifconfig |cut -c-10 |tr -d ' '|tr -s '\n' )
		#parametry dyskow przy wyswietlaniu
		#	hddname=$(df -H | grep ^/dev/ |cut -f3 -d '/'| awk '{ print $1 }')
		#	hddfull=$(df -H | grep ^/dev/ |cut -f3 -d '/'| awk '{ print $2 }')
		#	hddzajete=$(df -H | grep ^/dev/ |cut -f3 -d '/'| awk '{ print $3 }')
		#	hdddostepne=$(df -H | grep ^/dev/ |cut -f3 -d '/'| awk '{ print $4 }')
		#	hddprocent=$(df -H | grep ^/dev/ |cut -f3 -d '/'| awk '{ print $5 }')
	}

	#kartasieciowa()
	#{
		#ilekart=$(lspci |grep Ethernet | wc -l)

		#for (( i=1; $i <= $ilekart; i++ )) ;
		#	do
		#	lan=$(lspci |grep Ethernet |cut -d: -f3| tail -n $i|head -n 1)
		#	lan$i=$(lspci |grep Ethernet |cut -d: -f3|tail -n +$i|head -n 1|awk '{print $1}')

		#	done
	#}

	uslugi()
	{
		www=$(service apache2 status |grep Active |awk '{print $3 }')
		baza=$(service mysql status |grep Active |awk '{print $3 }')
		sshstatus=$(service ssh status |grep Active |awk '{print $3 }')


		if [ $www = "(running)" ];
		then
			www=$(echo  -e "\e[32mON\e[0m" )
		else 
			www=$(echo "OFF")
			www=$(echo  -e "\e[31mOFF\e[0m" )
		fi

		if [ $baza = "(running)" ];
		then
			baza=$(echo  -e "\E[32mON\e[0m" )
		else 
			baza=$(echo  -e "\E[31mOFF\e[0m" )
		fi

		if [ $sshstatus = "(running)" ];
		then
			sshstatus=$(echo  -e "\e[32mON\e[0m" )
		else 
			sshstatus=$(echo  -e "\e[31mOFF\e[0m" )
		fi
	}

	printf '\e[5;32;40m Blink Text\e[m\n'

	siec()
	{
		statlan

		#ifconfig |cut -c-10 |tr -d ' '|tr -s '\n' >/tmp/siec.tmp
		ifconfig | cut -c-10 |tr -d ' '|tr -s '\n' | grep ':' | cut -f 1 -d ':' > /tmp/siec.tmp
		printf "%-1s %-15s %-1s %-15s %-1s %-20s %-1s %-15s %-1s %-20s %-1s %s\n" "|" "---------------" "-" "---------------" "-" "--------------------" "|" "---------------" "-" "--------------------" "|"
		printf "%-1s %-15s %-1s %-15s %-1s %-20s %-1s %-15s %-1s %-20s %-1s %s\n" "|" "Karta" "|" "IP" "|" "MAC" "|" "" "|" "" "|"
		printf "%-1s %-15s %-1s %-15s %-1s %-20s %-1s %-15s %-1s %-20s %-1s %s\n" "|" "" "" "" "" "" "|" "" "|" "" "|"
		printf "%-1s %-15s %-1s %-15s %-1s %-20s %-1s %-15s %-1s %-20s %-1s %s\n" "|" "---------------" "-" "---------------" "-" "--------------------" "-" "---------------" "-" "--------------------" "|"

		for karta in $(cat /tmp/siec.tmp)
		do 
			adres=$(ifconfig $karta |grep -w "inet\|inet addr"|awk '{print $2 }'|cut -f2 -d ':')
		#	adresmac=$(ifconfig eth1 |grep HWaddr |awk '{print $5}')
			adresmac=$(ifconfig $karta |grep -w 'HWaddr\|ether' |tr ' ' '\n' | grep [:::::])
			printf "%-1s %-15s %-1s %-15s %-1s %-20s %-1s %-15s %-1s %-20s %-1s %s\n" "|" "$karta " "|" "$adres" "|" "$adresmac" "|" "" "" "" "|"
		done
		printf "%-1s %-15s %-1s %-15s %-1s %-20s %-1s %-15s %-1s %-20s %-1s %s\n" "|" "---------------" "-" "---------------" "-" "--------------------" "-" "---------------" "-" "--------------------" "|"
	}


	stanuslug()
	{
		printf "%-1s %-15s %-1s %-15s %-1s %-20s %-1s %-15s %-1s %-20s %-1s %s\n" "|" "---------------" "-" "---------------" "-" "--------------------" "-" "---------------" "-" "--------------------" "|"

		echo -ne "| \e[7;96mPodaj numer z menu [ENTER]:\e[0m " ; read menu 
		#read  menu
		#read menu
		case $menu in
			a)
			echo -ne "|\e[95m Podaj prawidłowy kod :\e[0m "
			read zmienna1
				case $zmienna1 in
					w)
					service apache2 start
					clear
					calosc
						;;
					x)
					service apache2 stop
					clear
					calosc
						;;
					y)
					service apache2 restart
					clear
					calosc
						;;
					*)
						echo -ne "|\e[31m Błąd [ENTER]...\e[0m" ; read 	
						#read -p $"\e[31m| Błąd [ENTER]...\e[0m"
						;;
				esac
				;;
			m)
			echo -ne "|\e[95m Podaj prawidłowy kod :\e[0m "
			read zmienna2
				case $zmienna2 in
					w)
					service mysql start
					clear
					calosc
						;;
					x)
					service mysql stop
					clear
					calosc
						;;
					y)
					service mysql restart
					clear
					calosc
						;;
					*)
					echo -ne "|\e[31m Błąd [ENTER]...\e[0m" ; read
						;;
				esac
				;;

			s)
			echo -ne "|\e[95m Podaj prawidłowy kod :\e[0m "
			read zmienna3
				case $zmienna3 in
					w)
					service ssh start
					clear
					calosc
						;;
					x)
					service ssh stop
					clear
					calosc
						;;
					y)
					service ssh restart
					clear
					calosc
						;;
					*)
					echo -ne "|\e[31m Błąd [ENTER]...\e[0m" ; read
						;;
				esac
				;;

			*)
				echo -e "\e[91m| BŁAD: podaj numer z menu...\e[0m"	
				read -p "| Naciśnij [ENTER] aby kontynułować..." 
				;;
		esac
		
		clear
		calosc
	}

	dmesg | grep -i dma
	dmesg | grep -i memory
	dmesg | grep -i usb
	dmesg > boot_info

	while true;
	do
		clear
		uslugi
		kartasieciowa
		statlan
		info
		clear
		echo

		wyświetlanie()
		{ 
			printf "%-25s %-30s %-10s %s\n" "" "" ""
			printf "%-1s %-15s %-1s %-15s %-1s %-20s %-1s %-15s %-1s %-20s %-1s %s\n" "" "" "" "" "" "LS - monitor" "" "" "" "" ""
			printf "%-1s %-15s %-1s %-15s %-1s %-20s %-1s %-15s %-1s %-20s %-1s %s\n" "|" "---------------" "-" "---------------" "-" "--------------------" "-" "---------------" "-" "--------------------" "|"
			#
			printf "%-1s %-15s %-1s %-15s %-1s %-20s %-1s %-15s %-1s %-20s %-1s %s\n" "|" "" "" "Pamiec RAM" "" "" "|" "Parametry" "" "komputera" "|"
			printf "%-1s %-15s %-1s %-15s %-1s %-20s %-1s %-15s %-1s %-20s %-1s %s\n" "|" "---------------" "-" "---------------" "-" "--------------------" "|" "---------------" "-" "--------------------" "|"
			printf "%-1s %-15s %-1s %-15s %-1s %-20s %-1s %-15s %-1s %-20s %-1s %s\n" "|" "calkowita" "|" "zajeta" "|" "wolna" "|"  "system" ">" "$os" "|"
			printf "%-1s %-15s %-1s %-15s %-1s %-20s %-1s %-15s %-1s %-20s %-1s %s\n" "|" "" "|" "" "|" "" "|" "procesor" ">" "$cpu1 $cpu2" "|"
			printf "%-1s %-15s %-1s %-15s %-1s %-20s %-1s %-15s %-1s %-20s %-1s %s\n" "|" "" "|" "" "|" "" "|" "model" ">" "$cpu5 $cpu3" "|"
			#
			printf "%-1s %-15s %-1s %-15s %-1s %-20s %-1s %-15s %-1s %-20s %-1s %s\n" "|" "$ramt" "|" "$ramu" "|" "$ramf" "|" "czestotliwosc" ">" "$cpu4" "|"
			printf "%-1s %-15s %-1s %-15s %-1s %-20s %-1s %-15s %-1s %-20s %-1s %s\n" "|" "---------------" "-" "---------------" "-" "--------------------" "|" "rdzenie" ">" "$rdzenie" "|"
			#
			#
			printf "%-1s %-8s %-1s %-10s %-1s %-10s %-1s %-8s %-1s %-8s %-1s %-15s %-1s %-20s %-1s %s\n" "|" "" "" "" "" "DYSKI HDD" "" "" "" "" "|" "RAM" ">" "$ramt MiB" "|"
			printf "%-1s %-8s %-1s %-10s %-1s %-10s %-1s %-8s %-1s %-8s %-1s %-15s %-1s %-20s %-1s %s\n" "|" "--------" "-" "----------" "-" "----------" "-" "--------" "-" "--------" "|" "HDD" ">" "$hdd" "|"
			printf "%-1s %-8s %-1s %-10s %-1s %-10s %-1s %-8s %-1s %-8s %-1s %-15s %-1s %-20s %-1s %s\n" "|" "dysk" "|" "pojemnosc" "|" "zajete" "|" "dostepne" "|" "procent" "|" "" ">" "" "|"
			printf "%-1s %-8s %-1s %-10s %-1s %-10s %-1s %-8s %-1s %-8s %-1s %-15s %-1s %-20s %-1s %s\n" "|" "" "|" "" "|" "" "|" "" "|" "" "|" "" ">" "" "|"
			liczba=$(df -H | grep ^/dev/ |cut -f3 -d '/'| awk '{ print $1 }'| wc -l)
			for((i=1;i<=$liczba;i++));
			do
				hddname=$(df -H | grep ^/dev/ |cut -f3 -d '/'| awk '{print $1 }'|sed -n "$i"p)
				hddfull=$(df -H | grep ^/dev/ |cut -f3 -d '/'| awk '{print $2 }'|sed -n "$i"p)
				hddzajete=$(df -H | grep ^/dev/ |cut -f3 -d '/'| awk '{print $3 }'| sed -n "$i"p)
				hdddostepne=$(df -H | grep ^/dev/ |cut -f3 -d '/'| awk '{print $4 }'| sed -n "$i"p)
				hddprocent=$(df -H | grep ^/dev/ |cut -f3 -d '/'| awk '{print $5 }'| sed -n "$i"p)
				printf "%-1s %-8s %-1s %-10s %-1s %-10s %-1s %-8s %-1s %-8s %-1s %-15s %-1s %-20s %-1s %s\n" "|" "$hddname" "|" "$hddfull" "|" "$hddzajete" "|" "$hdddostepne" "|" "$hddprocent" "|" "" ">" "" "|"
			done
			printf "%-1s %-8s %-1s %-10s %-1s %-10s %-1s %-8s %-1s %-8s %-1s %-15s %-1s %-20s %-1s %s\n" "|" "--------" "-" "----------" "-" "----------" "-" "--------" "-" "--------" "|" "" ">" "" "|"

			printf "%-1s %-15s %-1s %-15s %-1s %-20s %-1s %-15s %-1s %-20s %-1s %s\n" "|" "" "" "Uslugi" "" "" "|" "" ">" "" "|"
			printf "%-1s %-15s %-1s %-15s %-1s %-20s %-1s %-15s %-1s %-20s %-1s %s\n" "|" "---------------" "-" "---------------" "-" "--------------------" "|" "---------------" "-" "--------------------" "|"
			printf "%-1s %-15s %-1s %-24s %-1s %-20s %-1s %-15s %-1s %-20s %-1s %s\n" "|" "Apache" "-" "$www" "|" "" "|" "dane odebrane" "|" "dane  wyslane" "|"
			printf "%-1s %-15s %-1s %-24s %-1s %-20s %-1s %-15s %-1s %-20s %-1s %s\n" "|" "Mysql" "-" "$baza" "|" "" "|" "" "|" "" "|"
			printf "%-1s %-15s %-1s %-24s %-1s %-20s %-1s %-15s %-1s %-20s %-1s %s\n" "|" "SSH" "-" "$sshstatus" "|" "" "|" "$odebrane" "|" "$wyslane" "|"
			printf "%-1s %-15s %-1s %-15s %-1s %-20s %-1s %-15s %-1s %-20s %-1s %s\n" "|" "---------------" "-" "---------------" "-" "--------------------" "-" "---------------" "-" "--------------------" "|"
			printf "%-1s \e[7;96m%-15s\e[0m %-1s \e[7;96m%-15s\e[0m %-1s \e[7;96m%-20s\e[0m %-1s \e[95m%-38s\e[0m %-1s %s\n" "|" "A - Apache2" "-" "M - Mysql" "-" "S - SSH" "-" "W-wlacz      X-wylacz     Y-restart" "|" 
		}

		wyświetlanie
		siec
		usecpu
		stanuslug
		#kartasieciowa
		echo
		read 
	done
}

while true;
do
	calosc
done