# What is Anwalic?
Anwalic means Anime Watch List Creator.

It manages your Animes you are currently watching, you finished & and which you plan to watch. For that purpose Anwalic counts the current episode and saves the URL to the streaming platform.


# 1 Screenshots
Please note, that I set a custom background for the application, which you can also do. I do not own the background image and the background image is not distributed with this software.

## 1.1 Windows Screenshot
![Anwalic1.3DevBuild3.jpg](doc/images/Anwalic1.3DevBuild3.jpg)

## 1.2 Linux Screenshot
![Anwalic1.4-DevBuild1.1-linux.png](doc/images/Anwalic1.4-DevBuild1.1-linux.png)

# 2 Downloads
## 2.1 Windows Downloads

*TODO: upload windows build without copyright material*

## 2.2 Linux Downloads

* Anwalic 1.4 DevBuild 2: <a href="https://app.box.com/s/lby30po0c2yun846wko35kbtfkm0sjps" target="_blank">https://app.box.com/s/lby30po0c2yun846wko35kbtfkm0sjps</a> [LATEST VERSION]
  

# 3 Dependencies
* Qt5 (tested with Qt 5.13.0 and Qt 5.14.2)
* Boost

Mainly developed with Microsoft Visual Studio 2013


# 4 Building from source
We will create a standalone version of the application with
[CQtDeployer](https://github.com/QuasarApp/CQtDeployer).


## 4.1 Build on Linux
1. run `install.sh`
  * this compiles all source files and creates an executable
  * run as root if you also want the desktop icon to be installed. Otherwise
    you can copy the created desktop icon file from `./icon/desktop-icon/Anwalic.desktop`
    to `/usr/share/applications` manually. You might want to adjust the paths
    in the .desktop file.
2. install CQtDeployer. See the
[build instructions for CQtDeployer](https://github.com/QuasarApp/CQtDeployer#build-for-linux)
  * hints for the install instructions
    * for **qmake -r**. Do not use any version you might have installed from apt,
      since it use an older version of Qt. You use the correction version by
      running the qmake from the Qt version you just installed => 
      `~/Qt/5.14.2/gcc_64/bin/qmake -r`
    * for **make deploy** you actually need a CQtDeployer installed. You build
      your CQtDeployer from source by using an already compiled version of
      CQtDeployer. So, you you have to download 
      [CQtDeployer from snap](https://snapcraft.io/cqtdeployer) and then run
      `make deploy`
        * if you do not have snap on your system, install it with `sudo apt-get install snap snapd`
3. run `deploy.sh`
  * this will create a standalone version of the application
  * it copies all needed libraries, resources and the executable into the folder
    ./deploy/linux
    * extract the .tar.gz where you want the application to be installed.
  * you can run the application with the file anwalic.sh


## 4.2 Build on Windows
for Windows I create a static compiled version. Build and configure Qt from source, so it builds a static compiled version of Anwalic, see below.


### 4.2.1 Static Build
You can also put all dependencies inside the executable to have no shared
libraries / DLLs. No shared libraries like libQt5Core.dll or
libQt5Core.so.5.13.0). Therefore, you have to recompile Qt from sources.

I show how I once configured Qt to create static builds on Windows. This documentation has been done on linux, but also applies to Windows. Make sure to have all needed tools accessible from command line.

* create a static compiled version of Qt by compiling Qt from source
  * go inside the Qt source folder and run the following commands (adjust paths for Qt source directory)
  * create the "static-build" folder beforehand
  * `gregor@6r390r:~/.Qt/5.13.0/Src$ ./configure -static -prefix /home/gregor/.Qt/5.13.0/static-build -skip webengine -nomake tools -nomake tests -nomake examples`
    * if you are already in the Src folder you cannot put a dot for -prefix, you have to put the whole path. Otherwise some components cannot be found.
  * `make -j8` or `make -j$(nproc)`
    * -j8 will create 8 threads for building Qt. So adjust this value for
      the number of processors you have.
    * if the build fails, some dependencies might be missing. Read the error log on console.
  * `make -j8 install`

for additional information on building Qt from source, see also https://wiki.qt.io/Building_Qt_5_from_Git#Getting_the_source_code

  
# 5 Tested On
* Windows 7
* Windows 10
* Ubuntu 16.04.7
* Ubuntu 20.04
* Linuxmint 19.1


# 6 Licenses
This software uses Qt which is licensed under the GPLv3. Therefore, this software
is also licensed under GPLv3. See LICENSE file

This software uses Boost which is licensed under the Boost Software License.
The Boost Software License has been put where the boost library is, in src/boost/LICENSE_1_0.txt.
