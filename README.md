# Driver Library for IO-Link Master Shield/Hat for Arduino and Raspberry&nbsp;Pi

> :warning: **Under development**:  The library *openiolink* is a work in progress, and we expect it to change rapidly, including breaking API changes. Feedback is highly appreciated.

## Authors

- Janik Lehmann
- Pascal Frei
- Markus Gafner, BFH

## How to build the application for [Arduino Due](https://store.arduino.cc/arduino-due)

### Requirements on the host system

The easiest way to deploy for Arduino is to use the [Arduino&nbsp;IDE]( https://www.arduino.cc/en/Main/Software). It is available for Windows, macOS, and Linux.

In the Arduino IDE, click File->Open and select the `*.ino` file in the local Git repository in the subfolder `Demonstrator/`. If the code is open, you can click Sketch->Upload and the IDE will compile the code and flash it to the Arduino.

To edit the code, it is more comfortable to use Visual&nbsp;Studio&nbsp;Code. The big advantage is that VS&nbsp;Code can do syntax highlighting and IntelliSense works. The problem in the Arduino&nbsp;IDE is that it doesn't display files in subfolders, so only the project file is displayed at startup.


## How to build the application for [Raspberry Pi 3B](https://www.raspberrypi.org/products/raspberry-pi-3-model-b/)


### Requirements on the host System

To communicate with the Raspberry&nbsp;Pi, a SSH&nbsp;client is required. On Windows, we suggest to use [Putty](https://putty.org/). On Linux and macOS, the SSH&nbsp;client (typically a version of [OpenSSH](https://www.openssh.com/)) is usually already installed.
SCP can be used to copy files from or to the Raspberry Pi on the command line or via a GUI such as [FileZilla](https://filezilla-project.org/) or [WinSCP](https://winscp.net/eng/index.php).

- Open an SSH&nbsp;connection to the Raspberry&nbsp;Pi. The IP&nbsp;address gets printed on the boot screen when you connect the HDMI&nbsp;port.


#### Requirements on the Raspberry&nbsp;Pi

To use the application on Raspberry&nbsp;Pi&nbsp;3B, the operating system [Raspbian](http://raspbian.org) is used. Also, the library [WiringPi](http://wiringpi.com) and the build tool [CMake](https://cmake.org) is required.

This can get installed using the command:
```bash
sudo apt-get install wiringpi cmake
```

After a successful installation, the Raspberry&nbsp;Pi is ready to use.


#### Testing on Raspberry Pi

If you want to execute the board test on the Raspberry Pi, you have to install gcc9. Today, the default Version of gcc on Raspberry Pi ist the version 8. So you have to follow a few steps listed in the following gist: [Install_GCC9](https://gist.github.com/sol-prog/95e4e7e3674ac819179acf33172de8a9)


#### Compiling the Project

The easiest was to compile the project is, to copy all sources to the Raspberry&nbsp;Pi, and compile the project on the Raspberry&nbsp;Pi itself.

1. Copy all source files to a folder you like, for example `/home/pi/projects/`
2. With the SSH&nbsp;connection, move to the folder you copied the files: `cd /home/pi/projects/`
3. Move to the project folder: `cd Demonstrator/`
4. Initialize CMake: `cmake .`
5. Build the binary: `make`

If every step was successful, an executable file (e.g. `Demonstrator_v1_0.bin`) is created in the project folder. This one can be executed using `./Demonstrator_v1_0.bin`.


#### Editing on the target

If a problem in the application exists, there is a possibility to edit the files on the target. This can be done for example using WinSCP.

It is more comfortable to use Visual Studio Code with the plugin "SSH FS", which is available on the [Visual Studio Marketplace](https://marketplace.visualstudio.com/items?itemName=Kelvin.vscode-sshfs). This plugin can mount a filesystem over SSH to the local filesystem. This means, all changes will be made online. The big advantage is that Visual Studio Code can do syntax highlighting and IntelliSense works.


#### Debugging on the System

If you would like to debug the application using Windows, cross-compiling is quite difficult. You must download the source files from Raspberryi&nbsp;Pi, compile the executable, and upload the binary file.

It is very easy to deploy an application using Visual&nbsp;Studio. Since VS&nbsp;2017, it is possible to create a Linux project, see [here](https://docs.microsoft.com/en-us/cpp/linux/create-a-new-linux-project?view=vs-2019).

If the project has been created, a README shows how to connect to the target platform. It is only necessary to add all source and include files to the project as well as to add the library `wiringPi` as a linker input (also described in the `README`). Finally, VS will copy all files to the target, build the application on the target, and it is then able to debug the built application on the target. It does not cross compile, but it is a nice way to debug the application.

