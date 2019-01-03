1. Open SysProg_CLion_Project in CLion
2. CLion will detect the CMakeList.txt file (No changes should be needed there)
3. Go to Build Configurations and add following parameters to the Scanner Build Goal:
   ../assets/program_1.txt ../output/output_1.txt
   This will scan program_1 in the assets folder and write the output to output_1 in the output folder
4. Binaries, copied assets and output files can be found in the cmake-build-debug folder

