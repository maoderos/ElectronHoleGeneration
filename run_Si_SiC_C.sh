#!/bin/bash

#Create results directory if not exists

mkdir -p results;

materials=(Si SiC C);

for i in "$materials[@]"
do
	echo "Simulating $i material"
  mkdir -p results/$i;
	./ElectronHoleGeneration -m ../macros/$i.in -t 24
  #Store all .root files in the results folder 
	mv *.root results/$i;
	echo "$i simulation finished"
done

echo "DONE"
