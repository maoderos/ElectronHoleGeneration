# ElectronHoleGeneration

Geant4 simulation of electron-hole pair generation in materials. 3 materials are allowed: Si, SiC and C.

The mean energies of electron-hole pair generation for the materials were taken from:

* Si: doi: 10.3390/s18072289
* SiC: doi: 10.3390/s18072289
* C: https://doi.org/10.1002/pssa.201600195

The stopping power tables:
* Si and C: DOI: https://dx.doi.org/10.18434/T4NC7P
*
## Instructions 

Once you loaded the Geant4 environment, create a folder to build the application, in this example we will name it "build", and enter in it:

`$ mkdir build && cd build`

Compile:

`$ cmake .. && make`

In order to run the application in the visualization mode, one must start the application without any arguments:

`$ ./ElectronHoleGeneration`

Or one can use a macro as input:

`$ ./ElectronHoleGeneration -m <macro> -t <numberOfThreads>`

The folder contains a macro named "macro_script.in" that can be used as an example for testing:

`$ ./ElectronHoleGeneration -m ../macro_script.in -t 3`

A script called "generate_macros.sh" was developed to create macros easily. Running it with the `--help` argument to see all the available options.


