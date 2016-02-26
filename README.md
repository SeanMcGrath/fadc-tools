# fadc-tools
Software for parsing/analyzing fADC125-generated root files.

### Installation

A complete ROOT install is required.

`cd src`
`make`
`sudo make install`

This will install a library of ROOT objects and configure ROOT to load it at runtime. It also places some simple macros on ROOT's macro path, and installs command-line tools to facilitate their use.

### Usage

`integrate_peaks ROOT_FILE [OUT_FILE]`

This command will detect peaks in a .root file, integrate them, and compute their leading edge times. The results will be printed to standard out in comma-separated format, or to OUT_FILE if supplied.

`view_waves ROOT_FILE` 

Plots the waveforms in ROOT_FILE one at a time, with computed peak start and end times shown as vertical lines.

### TODO
* Integrate commands into single tool
* Make TSelectors more configurable & take config from CLI tools
* Better peak detection

### Author

Written by [Sean McGrath](www.smcgrath.me) for UMass Physics with help from David Lawrence of JLab.
