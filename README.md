# <img src="img/pwf2tools-x64.png" align="center"> ezisomod - A sleek GUI for isomod! </img>

ezisomod is a modding tool for injecting and extracting files from ISO9660 archives, originally intended for the game "PaRappa the Rapper 2". It is released under the TFRPL (my custom license!). It's free to use and open source (and always will be!). The icon is drawn by [@p4ckles](https://twitter.com/p4ckles).

# Installing and using
Currently, you must install from source. To build libpwf2tools currently, you need the following dependencies on your system: **CMake 3.5** (or newer), **Qt6** (or newer), and a **C/C++ compiler**. At the root of the directory, you will need to run these commands:

    mkdir build
    cd build
    cmake ..
    make

## Outputs
The output executable will be simply called "ezisomod(.exe)"

## Supported files
  * Archives
    - `ISO9660 archives`

## About isomod

isomod deals with the manipulation of ISO9660 files. It is not exclusive to PaRappa the Rapper 2. It can pull from or inject files into an ISO9660 archive without the need of extracting and recreating the entire file.
