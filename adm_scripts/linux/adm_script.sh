#!/bin/bash

echo -e "   db    888b. 8b   d8 888 8b  8 
  dPYb   8   8 8YbmdP8  8  8Ybm8 
 dPwwYb  8   8 8  \"  8  8  8  \"8 
dP    Yb 888P' 8     8 888 8   8\n"

# Create new group
exits=true
while [ $exist = true ]
do
	exist=false
	echo -n "Input group name: "
	read groupname
	if [ $(getent group $groupname) ] ; then
		echo "Group already exist. Try another name..."
		exist=true
	fi
done

groupadd $groupname


# Create new user
exits=true
while [ $exist = true ]
do
	exist=false
	echo -n "Input user name: "
	read username
	if [ $(grep -q -E "^${username}:" /etc/passwd) ] ; then
		echo "User already exist. Try another name..."
		exist=true
	fi
done

useradd -g $groupname -s /bin/bash $username
passwd $username


# Print user informations
echo -n "User ${username} groups: "
echo $(groups $username)


# Create user private directory
dir="/${username}"
mkdir $dir
chown $username $dir
chmod 1770 $dir


# Print formated informations about running services
cat /etc/services | grep -E "(tcp|udp|ddp)" | cut -d " " -f 1 | cut -f $'\t' -f 1 | sort -u