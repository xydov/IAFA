#!/bin/sh

while true
	do
	trap "echo Can\'t press ctrl-c" 2
	date +"%T"
	sleep 1
done
