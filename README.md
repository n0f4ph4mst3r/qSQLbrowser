![Build Status](https://github.com/n0f4ph4mst3r/qSQLbrowser/actions/workflows/ccpp-windows-x64.yml/badge.svg)
![Build Status](https://github.com/n0f4ph4mst3r/qSQLbrowser/actions/workflows/ccpp-ubuntu-gcc.yml/badge.svg)
![Build Status](https://github.com/n0f4ph4mst3r/qSQLbrowser/actions/workflows/ccpp-ubuntu-clang.yml/badge.svg)
![Github Releases](https://img.shields.io/github/v/release/n0f4ph4mst3r/qSQLbrowser)

# qSQLbrowser
Description
-----------
Browser for visualizing the results of SQL statements on a live database.

Build
-----
## Prerequisites

* **cmake** >= 3.26.0
* **vcpkg** more recent than 2023-07-19 (e.g. commit id [4c1734ba2a969b1e6daa0ac79bc46ead7324df90](https://github.com/microsoft/vcpkg/commit/4c1734ba2a969b1e6daa0ac79bc46ead7324df90))
* **A working compiler supporting C++ 20 functions



### Cmake

On Windows, please use the [prebuilt binaries](https://cmake.org/download/). Ensure you select one of the options to add cmake to the system path.

On Linux, `cmake` is usually available from the system package manager. Alternatively, `sudo pip3 install cmake` can be used to install the latest version of CMake.

### Vcpkg
Clone the repo with the `--recurse-submodules` flag

    git clone --recurse-submodules https://github.com/n0f4ph4mst3r/qSQLbrowser
	
Run `./vcpkg/bootstrap-vcpkg.sh` or `.\vcpkg\bootstrap-vcpkg.bat`.

## Building

### Windows
I build using Microsoft Visual Studio 2022. However, it is likely possible to build it with Visual Studio 2019.


### Linux
I use Clang 15, but any compilers supporting C++ 20 functions should work. Also, `qtbase` requires packages from the system package manager. They
can be installed on Ubuntu systems via:

	sudo apt-get install autoconf-archive '^libxcb.*-dev' libx11-xcb-dev libglu1-mesa-dev libxrender-dev libxi-dev libxkbcommon-dev libxkbcommon-x11-dev


#### Building on Windows

1. Clone this repository from GitHub project.

For example, in the git-bash run:

    git clone --recurse-submodules https://github.com/n0f4ph4mst3r/qSQLbrowser
	
2. Run `.\vcpkg\bootstrap-vcpkg.bat -disableMetrics`.

3. Configure project using CMake:

       $ mkdir build && cd build
       $ cmake .. -G "Visual Studio 17 2022"
    
4. Open Visual Studio project:

       $ .\qSQLbrowser.sln
    
    and build using the IDE.

5. Deploy Qt libraries using `windeployqt.exe`:

        $ .\vcpkg_installed\x64-windows-mixed\tools\Qt6\bin\windeployqt.exe .\Release\qSQLbrowser.exe

For debug configuration use `windeployqt.debug.bat`:

    $ .\vcpkg_installed\x64-windows-mixed\tools\Qt6\bin\windeployqt.debug.bat .\Debug\qSQLbrowser.exe

#### Linux 

1. Clone repository from GitHub project.

       git clone --recurse-submodules https://github.com/n0f4ph4mst3r/qSQLbrowser
	
2. Run `./vcpkg/bootstrap-vcpkg.sh -disableMetrics`.
    
3. Configure project using CMake:

       $ mkdir build && cd build
       $ cmake .. -G "Unix Makefiles" 
	   
   `Ninja` generator working too:

       $ cmake .. -G "Ninja" 
	   
	Use `-DCMAKE_BUILD_TYPE=Debug` for debug configuration.
  
4. Install project
   
        $ cmake --install . 
    
5. Test the build:

       $ cd ../bin
       $ ./qSQLbrowser