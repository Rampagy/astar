# A*

Compare the two versions of the A* algorithm - branchless and branched.  Also explores the build automation tool SCons.

## Installation

    python -m pip install -r requirements.txt

## Building

Ensure you either have visual studio (Windows) or g++ (Linux) installed.

To build use the folowing command in the base folder of this project:

    scons -j128

To clean the build files use the following command:

    scons -c