#!/bin/bash

echo -n "" > pci_bdf_config.txt

IFS=' ' # space ( ) is set as delimiter
read -ra BDF_LIST <<< "$1" # Input string is read into an array as tokens separated by IFS

num=0
for i in "${BDF_LIST[@]}"
do
	num=$((num+1))
	echo Card$num:$i >> pci_bdf_config.txt
done
