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

*TODO: upload Windows build without copyright material*

## 2.2 Linux Downloads

* Anwalic 1.4 DevBuild 2: <a href="https://app.box.com/s/lby30po0c2yun846wko35kbtfkm0sjps" target="_blank">https://app.box.com/s/lby30po0c2yun846wko35kbtfkm0sjps</a> [LATEST VERSION]
  

# 3 Dependencies
* Qt5 (tested with Qt 5.13.0 and Qt 5.14.2)
* Boost (1.74.0)

Mainly developed with Microsoft Visual Studio 2013


# 4 Building from source
We will create a standalone version of the application with
[CQtDeployer](https://github.com/QuasarApp/CQtDeployer).


## 4.1 Build on Linux
1. run `1_install.sh`
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
      CQtDeployer. So, you have to download 
      [CQtDeployer from snap](https://snapcraft.io/cqtdeployer) and then run
      `make deploy`
        * if you do not have snap on your system, install it with `sudo apt-get install snap snapd`
3. run `2_deploy.sh`
  * this will create a standalone version of the application
  * it copies all needed libraries, resources and the executable into the folder
    ./deploy/linux
    * extract the .tar.gz where you want the application to be installed.
  * you can run the application with the file anwalic.sh


## 4.2 Build on Windows
Make sure to have all build tools on your system and available from command line

### 4.2.1 Dynamic Build (with DLLs)
* install [MinGW](http://www.mingw.org/)
* install [Qt 5.14.2](https://download.qt.io/official_releases/qt/5.14/5.14.2/)
* run `windows_build.bat`
    * builds, but cannot link qt static plugins
        * try qt static build (build Qt from source), see below: Static Build (without DLLs)

### 4.2.2 Static Build (without DLLs)
For this we must build Qt from source.

I use Cygwin to install missing libraries such as llvm, clang, libclang, Ninja, ... Add the bin directory of cygwin to Path. You add directories to Path variable by typing "environment variables" into Windows Search. To go to Windows Search, press Windows+Key and start typing. Restart cmd if you added something to Path.

* open a cmd from Qt installation which sets up Qt environment
    * Press Windows+Key, search folder "Qt 5.14.2". Open cmd `Qt 5.14.2 (MinGW 7.3.0 32-bit)`
    * cmd displays: Setting up environment for Qt usage...
* `cd C:\Qt\Qt5.14.2\5.14.2\Src`
* `configure.bat -static -release -prefix C:\Qt\Qt5.14.2\5.14.2\static-build -platform win32-g++ -nomake tests -nomake examples -opengl desktop`
* `mingw32-make`
* `mingw32-make install`

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

