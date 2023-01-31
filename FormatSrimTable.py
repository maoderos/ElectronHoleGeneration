import os
import sys
import re
import numpy as np
from io import StringIO 

def line_filter(line):
    line = line.replace(" keV", "E-03")
    line = line.replace(" MeV", "")
    line = line.replace(" GeV", "E03")
    line = line.replace(" A", "E-04")
    line = line.replace(" um", "")
    line = line.replace(" mm", "E03")
    line = line.replace(" m", "E06")
    line = line.replace("   ", " ")
    line = line.replace("  "," ")
    line = line.replace("  "," ")
    line = line.replace(",",".")
    #line = line.replace(" ",",")
    line_final = line[1:]
    return line_final


def format_file(filename,init=25,end=180): # Format SRIM tables and return lists
    file = open("stoppingPowerData/{0}".format(filename), "r") 
    file_write = open("stoppingPowerData/format_{0}".format(filename), "w")
    file_write.write("IonEnergy(MeV) dE/dxElec(MeV/(mg/cm2)) dE/dxNuc(MeV/(mg/cm2)) ProjectedRange(um) LongitudinalStraggling(um) LateralStraggling(um)\n")
    for i, line in enumerate(file):
        if i in np.arange(init, end): 
            correct_line = line_filter(line)
            file_write.write("{0}".format(correct_line))
    file_write.close()
    file.close()
    
argNumber = len(sys.argv)

if argNumber > 1:
    filename = str(sys.argv[1])
    format_file(filename)
else:
    print("You must specify the filename using the following structure:")
    print("python3 FormatSrimTable.py filename")

