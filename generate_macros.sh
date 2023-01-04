#!/bin/bash
#default versions
Emin=1;
Emax=10;
Thick=500;
Dstep=1;
Nevent=100;
Particle=proton;
Material=SiC;
step=1;
Name=macro_script;
Help()
{

	cat <<-END
	${0##*/}: Script for running SiDetector
	Usage:
		--Emin <value(MeV)>
			Minimum energy. (default: 1 MeV)
		
		--Emax <value(MeV)>
			Maximum energy. (default: 10 MeV)
			
		--Thick <value(um)>
			Minimum sensitive thickness. (default: 25 um)
			
		--step <value>
			step in for loop. (default: 1 MeV)
		
		--Nevent <value>
			Number of events. (default: 100)

		--Particle <value>
		  Choose the primary particle. (default: proton)
			Options: proton

		--Material
		  Choose the target material. (default: SiC)
			Options: SiC, C, Si
		
		--Name <value>
			Name of file. (default: macro_script)
	END
	exit
}

while [ $# -gt 0 ]; do
	case $1 in
		--help)
			Help
    	exit
			;;
	  	--Emin)
			Emin=$2
			shift 2
			;;
		--Emax)
			Emax=$2
			shift 2
			;;
		--Thick)
			Thick=$2
			shift 2
			;;
		--step)
			step=$2
			shift 2
			;;
		--Nevent)
			Nevent=$2
			shift 2
			;;
		--Particle)
			Particle=$2
			shift 2
			;;
		--Material)
			Material=$2
			shift 2
			;;
		--Name)
			Name=$2
			shift 2
			;;
	esac
done 
	
#Create macro and write it
#first loop in thickness

echo "/run/initialize" > ${Name}.in
#echo "/analysis/setDefaultFileType root" >> ${Name}.in
#echo "/analysis/openFile $Particle" >> ${Name}.in
echo "/gun/particle $Particle" >> ${Name}.in
echo "/setTarget/sensitiveThickness $Thick um" >> ${Name}.in
echo "/setTarget/material $Material" >> ${Name}.in
for ((j=$Emin; j<=$Emax; j+=$step)); do  
  echo "/gun/energy $j MeV" >> ${Name}.in
  echo "/run/beamOn $Nevent" >> ${Name}.in
#	echo "/analysis/write" >> ${Name}.in
#	echo "/analysis/reset" >> ${Name}.in
done


#run geant4 simulation

#./SiDetector ${Name}.in
#mv result/data.dat result/${Name}.dat
