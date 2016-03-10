# fadc-tools
Software for parsing/analyzing fADC125-generated root files.

### Installation

A complete ROOT install is required.

`cd src`

`make`

`sudo make install`

This will compile the `fadc` executable and its dependencies and install them in your system

### Usage

This utility is accessed easily through the use of the `fadc` command. It uses this syntax:

`fadc [...OPTIONS] COMMAND CHANNEL ROOT_FILE`

For example:

`fadc -p average view 13 220.root`

This uses the `average` peak detection method to `view` the peak on channel `13` in the file `220.root`.

Available Commands:
* `view`: displays waveforms, including detected peak windows if a peak detection method is specified.
* `analyze`: If peak detection method is specified, prints computed characteristics of detected peaks to standard out.

Available Options:
* `-p` `--peakmethod`: Chooses a peak detection method, one of `average` or `fractional`. The average method computes the average value of the waveform, and defines the peak as the first region where the waveform goes above and then below the average. WARNING: this method will find a peak in ever ywaveform. The fractional method looks for successive significant increases in the value of the waveform.
* `-y`, `--yrange`: Sets the maximum of the y axis in the plots displayed by the `view` command.

`channel` may be an integer fADC125 channel number (0-24), or `all` to display all the waveforms in the file regardless of channel.

`ROOT_FILE` is a data file from the fADC, converted to `.root` format.

### TODO
* Better peak detection
* More analysis and analysis config

### Author

Written by [Sean McGrath](www.smcgrath.me) for UMass Physics with help from David Lawrence of JLab.
