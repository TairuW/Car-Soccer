# Getting Started with MinGfx and CMake

If you encounter any issues, please begin by checking [Piazza](https://piazza.com/class/k5o7m9d4vq710p) for help and checking the posts under the `mingfx-setup` folder. If that does not help, leave a post of your own or attend office hours. If you are really stuck send an email: [csci4611@umn.edu](mailto:csci4611@umn.edu).  

It is extremely helpful to outline the steps you took in your Piazza post or in your email. This helps us reproduce the problem and more quickly find a solution.

## Initial setup for a new computer

#### 0) Prereq: A computer and C++ compiler

* CSE Labs: The machines in the labs should already be setup for this step.
* Windows: You need to have Visual Studio 2015 or later with the ["Desktop development with C++" workload](https://docs.microsoft.com/en-us/cpp/build/vscpp-step-0-installation?view=vs-2019) installed.
* OSX: You need to have Xcode installed AND you need to [install Xcode command line tools](https://www.embarcadero.com/starthere/xe5/mobdevsetup/ios/en/installing_the_commandline_tools.html)
* Linux: You will need g++ and OpenGL development libraries. If they are not already installed, run ```sudo apt-get install build-essential libgl1-mesa-dev```.

#### 1) Install Git and CMake version 3.9 or later on your machine

* CSE Labs: These already have a recent version of cmake installed.
* Windows and OSX: [Download/install the binaries](https://cmake.org/download) (**not** the source code)  This will install a new application in your Start menu for Windows or in your Applications folder on Mac.  You can run it as usual by double-clicking it, and you can always do this if you prefer.  However, you may prefer to install CMake so that you can run it from the command line as shown in class.  To do this, open CMake by double-clicking, then go to the "Tools" menu and select "How to Install for Command Line Use".  Then follow the instructions there.
* Linux: There are two ways:
    1. [Download/install the most recent Linux binaries](https://cmake.org/download). There is a shell script and a tar.gz that you can download. The script, when run, will extract the tar file (which it  contains! If you look at the file, you'll see a bunch of crazy characters that is the compressed binaries themselves). Or you can download and unpack the tar.gz yourself. The tar.gz available has cmake-gui in the bin/ directory. There are different ways to run the cmake-gui:
        1. Directly from the bin/ directory. It is simply an executable and can be run from the command line or from the file explorer.
        2. As a bash command (like how it is shown in the slides). To add to the level of options, there are two ways to accomplish this as well:
            1. Add the bin/ directory containing cmake-gui to your PATH environment variable. This is explained well in this article [How to Add a Directory to PATH in Linux](https://linuxize.com/post/how-to-add-directory-to-path-in-linux/).
            2. Create a symlink from the cmake-gui executable to your bin as such:
            ```
            $ sudo ln -s /path/to/bin/containing/cmake-gui /usr/local/bin/
            ```
    2. Run the following installation commands in order to let Linux set up your path so that both cmake and cmake-gui are added as bash commands.
    ```
    $ sudo apt install cmake
    $ sudo apt-get install cmake-qt-gui     # to get cmake-gui (this might also install cmake?)
    ```

#### 2) Clone your repository for this class.  *Put it inside a directory path on your computer that does not include any spaces!*   On Windows, we recommend using Git-bash rather than the built-in Windows Command Prompt; Git-bash gets installed on Windows when you install Git.  On OSX, you can use Terminal.  On Linux, use your favorite shell.   Then, type the following command.

	git clone https://github.umn.edu/umn-csci-4611-s20/repo-[x500].git

#### 3) Add remote server for our support-code

	cd repo-[x500]
	git remote add upstream https://github.umn.edu/umn-csci-4611-s20/shared-upstream.git

#### 4) Pull from shared-upstream into your branch

	git pull upstream support-code

  * If you get an error "fatal: refusing to merge unrelated histories" add ``` --allow-unrelated-histories ```

#### 5) Git add everything that was just merged from the upstream support-code branch into your own master branch, commit these new changes, and then push the result back to your own origin.

	git add -A
	git commit -m "merged in the latest support code"
	git push origin master
	
After the ```git commit``` command, you may get the warning "Your branch is based on 'origin/master', but the upstream is gone." This is okay and you can ignore it, since we push to origin/master explicitly.

#### 6) Configure

Please see the [course slides on building with CMake](https://canvas.umn.edu/courses/158203/files/10944841?module_item_id=3340126) but remember that you can only start ```cmake-gui``` from the command line if you installed the CMake Command Line Tools in Step 1.  If not, then just run CMake from the Windows menu or Applications folder on Mac.

For Configuring:
* Remember the very important step noted in the slides for changing your CMAKE_INSTALL_PREFIX to point to the root of your repo -- this is critical for installing MinGfx to the correct place.
* If you have previously installed the nanogui or nanovg libraries on your computer for use with another course, like CSci-3081W, or for some other reason, CMake will find it and will skip downloading, building, and installing that dependency of MinGfx.  But, some students have had trouble with this, likely because when they installed nanogui previously, it was sufficient to just install the binaries, but for MinGfx, we need to have the header files for the library too.  The way around this is to force CMake to "auto build" NanoGUI even if it finds it, and you can do this by making sure the box next to AUTOBUILD_NANOGUI is checked in CMake before you run configure for the second time.
* If you are on Linux and you run into this error about the RandR library: `The RandR library and headers were not found`, you can try running `sudo apt-get install xorg-dev libglu1-mesa-dev` which will install `xrandr-dev` which contains the correct files.

#### 7) Build, and install

For Building and Installing:
  * Windows:  In the Solution Explorer window, you should see that the ALL_BUILD project is highlighted by default.  Start by building this project.  If it succeeds, then within the Solution Explorer, right click on the project named INSTALL and select Set as Startup Project.  Then build this project.

  * Mac with Xcode:  Run/build the ALL_BUILD project by clicking the triangle in the top left.  If it succeeds, then click on the ALL_BUILD text to the right of the triangle and change the current project to the one named "install".  Then click the triangle again to build that.  A common error when Configuring with CMake on mac is: "CMake error no CMAKE_C_COMPILER could be found using Xcode". This means that CMake cannot find the default compiler for C/C++ used by XCode. This can be remedied by entering the following command in your terminal: ``` sudo xcode-select --reset ```
  
  * Unix Makefiles: You will not have access to the open project button in cmake-gui. Instead, you will have to ```cd``` into the build directory, and run make directly:
```
cd /path/to/repo-[x500]/dev/MinGfx/build
make install
```
  
#### 8) For Windows environments, before you can run any of our graphics programs, you need to add /path/to/repo-[x500]/bin to the Path Windows Environment Variable so that windows will find the nanogui.dll file there:
* Step 1 - CSE Labs: Type "Edit Environment Variables for your account" in the search at the bottom corner of your windows screen. Go to Step 3. 
* Step 1 - Your own machine: Go to Control Panel > System and Security > System, and click "Advanced system settings" on the left.
* Step 2: In the "System Properties" window, under the "Advanced" tab, click "Environment Variables..."
* Step 3: In "System variables" pane, click the "Path" variable and click the "Edit..." button.
* Step 4: In the "Edit environment variable" window, Click "New" and "Browse..." to set the path to the "bin" folder under your repo.
* Step 5: Click "OK" to save the changes.
You must also completely close all Visual Studio windows and then restart Visual Studio for it to register this change.


#### 9) Run example binaries

If you compiled MinGfx correctly, an executable called mingfx-test-gui-plus-opengl should have been created in dev/MinGfx/build/tests/gui_plus_opengl/. 
* Windows: You can start the exe in debugging mode from within Visual Studio by going to the Solution Explorer, right clicking on the project named mingfx-test-gui-plus-opengl, selecting Set as Startup Project, then click the Run button.
* Mac with Xcode: You can start the exe in debugging mode from within Xcode by clicking on the text to the right of the triangle button and selecting the project named mingfx-test-gui-plus-opengl.  Then, click the triangle button to run it.
* Unix Makefiles:  Just type the name of the program in your shell, depending what directory you are in, it will be something like ```./path/to/repo-[x500]/dev/MinGfx/build/tests/gui_plus_opengl/mingfx-test-gui-plus-opengl```.



#### Verify that you can run the example binaries in in this step. If you cannot run the example binaries, do not attempt to compile other code that has MinGfx as a dependency (e.g. AngryVectors, gfxtest).



## Update support code

#### 1) Get updates from shared-upstream

	cd /path/to/repo-[x500]
	git pull upstream support-code
	
After you have updated from shared-upstream, re-do the "For Building and Installing" part of section 7 above. You do not need to run cmake's configure or generate on MinGfx again. You already configured and generated for your machine, so you're good to go!

Please note that the support-code will change throughout the semester. Be sure to get in the habit of pulling from the support code repository!

#### 2) Exercise: Build and run the gfxtest code

  a. Open cmake-gui, and set the source to /path/to/repo-[x500]/dev/gfxtest and build to /path/to/repo-[x500]/dev/gfxtest/build. If cmake-gui was already open, close it, then open it again.  
  b. Press configure once, select your desired build system, and generate once. There is no need to change the install prefix or any other cmake variables.  
  c. Compile with chosen build system, e.g. Visual Studios, XCode, or gcc.  
  d. Modify the gfxtext code in some way  
  e. Build and run gfxtest again  
  
