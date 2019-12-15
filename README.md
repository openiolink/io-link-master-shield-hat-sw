# Driver Library for IO-Link-Master-Shield/Hat for Arduino and Raspberry Pi


## Autors

- Pascal Frei
- Markus Gafner, BFH


## How to build the application for [Arduino Due](https://store.arduino.cc/arduino-due)

### Requirements on the host system

The easiest way to deploy for Arduino is to use the [Arduino IDE]( https://www.arduino.cc/en/Main/Software). It is available for Windows, macOS, and Linux.

In the Arduino IDE, click File->Open and select the `*.ino` file in the local Git repository in the subfolder `Demonstrator/`. If the code is open, you can click Sketch->Upload and the IDE will compile the code and flash it to the Arduino.

To edit the code, it is more comfortable to use Visual Studio Code. The big advantage is that VS Code can do syntax highlighting and IntelliSense works. The problem in the Arduino IDE is that it doesn't display files in subfolders, so only the project file is displayed at startup.


## How to build the application for [Raspberry Pi 3B](https://www.raspberrypi.org/products/raspberry-pi-3-model-b/)


### Requirements on the host System

To communicate with the Raspberry Pi, a SSH client is required. On Windows, we suggest to use [Putty](https://putty.org/). On Linux and macOS, the SSH client (typically a version of [OpenSSH](https://www.openssh.com/)) is usually already installed.
SCP can be used to copy files from or to the Raspberry Pi on the command line or via a GUI such as [FileZilla](https://filezilla-project.org/) or [WinSCP](https://winscp.net/eng/index.php).

- Open an SSH connection to the Raspberry Pi. The IP address gets printed on the boot screen when you connect the HDMI port.


#### Requirements on the Raspberry Pi

To use the application on Raspberry Pi 3B, the operating system [Raspbian](http://raspbian.org) is used. Also, the library [WiringPi](http://wiringpi.com) and the build tool [CMake](https://cmake.org) is required.

This can get installed using the command:
```bash
sudo apt-get install wiringpi cmake
```

After a successful installation, the Raspberry Pi is ready to use.


#### Compiling the Project

The easiest was to compile the project is, to copy all sources to the Raspberry Pi, and compile the project on the Raspberry Pi itself.

- Copy all source files to a folder you like, for example `/home/pi/projects/`
- With the SSH-connection, move to the folder you copied the files: `cd /home/pi/projects/`
- Move to the project folder: `cd Demonstrator/`
- Initialize CMake: `cmake .`
- Build the binary: `make`

If every step was successful, in the project folder should be an executable file, for example `Demonstrator_v1_0.bin`. This one can be executed using `./Demonstrator_v1_0.bin`.


#### Editing on the target

If a problem in the application exists, there is a possibility to edit the files on the target. This can be done for example using WinSCP.

More comfortable is to use Visual Studio Code with the plugin "SSH FS", which is available on the [Visual Studio Marketplace](https://marketplace.visualstudio.com/items?itemName=Kelvin.vscode-sshfs). This plugin can mount a filesystem over SSH to the local filesystem. This means, all changes will be made online. The big advantage is that Visual Studio Code can do syntax highlighting and IntelliSense works.


#### Debugging on the System

If you would like to debug the application using Windows, cross-compiling is quite difficult. You must download the source files from Raspberry Pi, compile the executable, and upload the binary file.

It is very easy to deploy an application using Visual Studio. Since VS 2017 (maybe also older versions, but untested), is possible to create a Linux project, see [here](https://docs.microsoft.com/en-us/cpp/linux/create-a-new-linux-project?view=vs-2019).

If the project has been created, a README shows how to connect to the target platform. It is only necessary to add all source and include files to the Project as well as to add the library wiringPi as a linker input (also described in the README). Finally, VS will copy all files to the target, build the application on the target, and it is then able to debug the built application on the target. It does not cross compile, but it is a nice way to debug the application.
