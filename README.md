# root-analysis-scripts
Scripts for parsing/analyzing fADC125-generated root files.

## Usage
* Clone this repository to a convenient local folder: `git clone https://github.com/SeanMcGrath/root-analysis-scripts`
* If you don't want to use git, download and unzip the repository contents. 
* Copy .root files to be analyzed into top level of the repository (same directory as this README).
* To view waves & peaks: `./view_waves your_file.root` Hit enter to advance through the waves.
* To compute integrals & leading edge times: `./integrate_peaks your_file.root` The results will be printed comma-separated  on standard out by default. To print them to a file, give its name as second argument: `./integrate_peaks your_file.root output_file.csv`
* If the scripts won't execute, set them as executable: `chmod +x view_waves integrate_peaks`
