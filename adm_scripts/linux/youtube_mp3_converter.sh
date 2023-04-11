#!/bin/bash

cat list.tmp | wc -l

for link in $(cat /root/mp3/list.tmp);
do
	echo "Downloading: $link"
	youtube-dl --extract-audio --audio-format mp3 $link
done