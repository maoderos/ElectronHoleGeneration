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
NoMSCSEC=false;
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

		--Material <Symbol>
		  Choose the target material. (default: SiC)
			Options: SiC, C, Si
		
		--Name <value>
			Name of file. (default: macro_script)

		--NoMSCSEC
			Disable multiple scattering and increase the cut for generating secondary particles (default: disabled)

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
		--NoMSCSEC)
			NoMSCSEC=true
			shift 1 
			;;
	esac
done 
	
#Create macro and write it
#first loop in thickness

echo "/run/initialize" > ${Name}.in
echo "/gun/particle $Particle" >> ${Name}.in
if $NoMSCSEC; then 
	echo "/process/inactivate msc" >> ${Name}.in
	echo "/run/setCut 1 km" >> ${Name}.in
fi
echo "/setTarget/sensitiveThickness $Thick um" >> ${Name}.in
echo "/setTarget/material $Material" >> ${Name}.in
for ((j=$Emin; j<=$Emax; j+=$step)); do  
  echo "/gun/energy $j MeV" >> ${Name}.in
  echo "/run/beamOn $Nevent" >> ${Name}.in
done

