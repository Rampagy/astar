# A* Implementations

Implementation of the A* search algorithm in multiple different languages

## Installation

This project uses an SCons build process.  To build the project ensure python version is >= 3.8.5 and the SCons dependencies are installed per the requirements.txt.

    python -m pip install -r requirements.txt

## Comparing

To compare the different languages run either `compare_languages_linux.sh` or `compare_languages_windows.bat` depending on your platform.  Don't forget to give execution privileges:

    chmod +x compare_languages_linux.sh

## Results

3970x with Precision Boost Overdrive on

| Language | Linux | Windows |
|    :-:   |  :-:  |   :-:   |
|   Java   |  12.9 |   13.0  |
|    C++   |  16.3 |   19.2  |
|    C#    |  22.7 |   27.1  |
|  Python  |  284  |   288   |