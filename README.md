# collaborative-text-editor

### About the Project
A decentralized C++ based text editor that allows multiple users to collaborate simultaneously in real-time.

### Prerequisites

- [CMake](https://cmake.org/install/)
- [Boost](https://www.boost.org/doc/libs/release/more/getting_started/unix-variants.html)

 
### Installing and running the application

#### Installing Boost
On a Debian based Linux (like Ubuntu), you can use `apt` to install boost directly. For other distributions, check the official boost documentation linked above.

```console
$ sudo apt install libboost-dev
$ sudo apt install libboost-all-dev
```

-----

The application is built using CMake as build tool. Additionally, SFML is required to compile the application. 
SFML libraries can be installed on linux relatively easily via the following command - `sudo apt-get install libsfml-dev`.

If you are running Ubuntu, or any other supported linux distribution, the above command should work. 
You can get more information about installing SFML on linux based systems [here](https://www.sfml-dev.org/tutorials/2.5/start-linux.php).

*NOTE: if the above command fails to install SFML libraries, that would mean that pre-compiled libraries are not available for your linux distribution, 
in this case you may have to download the SFML source and compile it yourself - that process also requires CMake*. 

To verify that you have the SFML libraries installed on your machine, you can run the following command - `ldconfig -p | grep sfml`. 
This command will search your system for installed libraries with sfml name. 

To verify that CMake is installed on your machine, just run the `cmake` command on terminal.  

#### Using IDE (CLion) to run project
The **CMakeLists.txt** is already configured for linux based systems and opening this project in most IDEs should automatically detect
CMakeLists.txt file and setup the project. 

Prior to running you just need to set the working directory of the C++ project - in CLion, you can do this by clicking the 
*Edit Configurations* option from the dropdown menu beside the run button. Set the working directory to the root of the current project. 

For instance, if you did not change the name of the project folder after cloning repository from GitHub, it should be pointing to `collaborative-text-editor`.

#### Running from CommandLine
If the above option does not work, you can also compile and run project using CMake command line utility. 

[Cmake](https://cmake.org/) is kind of a build wrapper around a *Makefile* that we use to generate a Makefile. Writing CMake is much simpler 
than writing a full-fledged Makefile and you can configure CMake to run differently on different OS. 

1. `cd` into the root of the project
2. `mkdir bin` to create a new folder where all the generated output goes
3. `cd bin` to go to the generated folder.
4. copy the entire fonts folder from `../src/fonts/` into the newly created `../bin/`. 
5. `ls` in bin folder must list fonts folder. 
6. from the root of `bin` folder run `cmake..` to generate the CMake build files.
7. you should now see a lot of generated output including a generated Makefile in the bin folder.
8. simply run `make` to run the MakeFile to get the executable.
9. execute the generated executable as you would for a normal C++ based program `./collaborative-text-editor`. 