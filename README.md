# Driver Library for IO-Link-Master-Shield and IO-Link-Master-Hat

## Autors
- Pascal Frei
- Markus Gafner

## Readme how to build the application for Arduino
### Requirements on the host system
The easiest way to deploy for Arduino is to use the Arduino IDE, It's available for Windows, Mac OS X and Linux as well. It could get downloaded there: [download]( https://www.arduino.cc/en/Main/Software)

In the Arduino IDE, click File->Open and select the *.ino File in the local Git-Repository in the subfolder Demonstrator. If the code is open you can click Sketch->Upload and the IDE will compile the code, and flash it to the Arduino.

To edit the code, it is more comfortable is to use Visual Studio Code. The big advantage is, that Visual Studio Code can do syntax highlighting and IntelliJ works. The problem in the Arduino IDE is, that it doesn't display files in subfolders, so only the project file is displayed at startup.

## Readme how to build the application for Raspberry Pi 3B
### Requirements on the host System
To communicate with the Raspberry Pi, a SSH based client is required. On Windows, I suggest using Putty, on Linux and macOS, the client is already installed.
To copy files from or to the Raspberry Pi, an SCP based application can get used. This could be an application like FileZilla or WinSCP.

- Open an SSH connection to the Raspberry Pi. The IP-address gets printed on the boot screen when you connect the HDMI-port

#### Requirements on the Raspberry Pi
To use the application on Raspberry Pi 3B, the operating system Raspbian is used. Also, the library WiringPi and the build-tool CMake is required.

This can get installed using the command 

``` sudo apt-get install wiringpi cmake ```

After a successful installation, the Raspberry Pi is ready to use.

#### Compiling the Project

The easiest was to compile the project is, to copy all sources to the Raspberry Pi, and compile the project on the Raspberry Pi itself.

- Copy all source files to a folder you like, for example ```/home/pi/projects/```
- With the SSH-connection, move to the folder you copied the files: ```cd /home/pi/projects/```
- Move to the project folder: ```cd Demonstrator/```
- Initialize CMake: ```cmake .```
- Build the binary: ```make```

If every step was successful, in the project folder should be an executable file, for example ```Demonstrator_v1_0.bin``` which could get executed using ```./Demonstrator_v1_0.bin```

#### Editing on the target
If a problem in the application exists, there is a possibility to edit the files on the target. This can be done for example using WinSCP.

More comfortable is to use Visual Studio Code with the plugin "SSH FS" [find it on the Visual Studio Marketplace](https://marketplace.visualstudio.com/items?itemName=Kelvin.vscode-sshfs). This plugin can mount a filesystem over ssh to the local filesystem. This means, all changes will made online. The big advantage is, that Visual Studio Code can do syntax highlighting and IntelliJ works.

#### Debugging on the System
When you like to debug the application using Windows, cross-compiling is quite difficult. You must download the source files from Raspberry Pi, compile the executable, and upload the binary file.

It is very easy to deploy an application using Visual Studio. Since VS2017 (maybe also older versions, but untested) is possible to create a Linux-project, see [here](https://docs.microsoft.com/en-us/cpp/linux/create-a-new-linux-project?view=vs-2019).

If the project has been created, a readme shows how to connect to the target platform. It is only necessary to add all source and include files to the Project, and to add the library wiringPi as a linker input (also described in the readme). Finally, VS will copy all files to the target, build the application on the target, and is then able to debug the build application on the target. It does not cross compile, but it is a nice way to debug the application.
