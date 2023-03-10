#MIP

mkdir MIP_data;
cd MIP_data;
./ElectronHoleGeneration -m ../macros/C_MIP.in -t 24;
cd ..;
mkdir MIP_data_NoMSC;
cd MIP_data_NoMSC;
./ElectronHoleGeneration -m ../macros/C_MIP_NoMSC.in -t 24;
cd ..;
mkdir MIP_data_NoSEC;
cd MIP_data_NoSEC;
./ElectronHoleGeneration -m ../macros/C_MIP_NoSEC.in -t 24;
cd ..;
mkdir MIP_data_NoMSCSEC;
cd MIP_data_NoMSCSEC;
./ElectronHoleGeneration -m ../macros/C_MIP_NoMSCSEC.in -t 24;
cd ..;

#dE/dx
mkdir dEdx_data;
cd dEdx_data;
./ElectronHoleGeneration -m ../macros/C_dEdx.in -t 24;
cd ..;
mkdir dEdx_data_NoMSC;
cd dEdx_data_NoMSC;
./ElectronHoleGeneration -m ../macros/C_dEdx_NoMSC.in -t 24;
cd ..;
mkdir dEdx_data_NoSEC;
cd dEdx_data_NoSEC;
./ElectronHoleGeneration -m ../macros/C_dEdx_NoSEC.in -t 24;
cd ..;
mkdir dEdx_data_NoMSCSEC;
cd dEdx_data_NoMSCSEC;
./ElectronHoleGeneration -m ../macros/C_dEdx_NoMSCSEC.in -t 24;
cd ..;



