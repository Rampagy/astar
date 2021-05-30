# C# (Mono-Project) Implementation

## Building

[Download and install](https://www.mono-project.com/download/stable/) the Mono compiler for your system.  This porject was built and verified using version 6.12.0 Stable (6.12.0.122).

To build use the folowing command in the base folder of this project:

    scons -j128

To clean the build files use the following command:

    scons -c

## Running

When running the C# executable ensure that you add executable permissions:

    chmod +x builds/astar_search.exe

Then to run the executable:

    ./builds/astar_search.exe