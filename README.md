# XlibProjects

## Description of scripts


### 100windows

Example about halfway trought

![Screenshot from 2023-11-11 10-42-18](https://github.com/pekka1234/XlibProjects/assets/62663286/e60bc892-c9c6-4384-a0d1-9d034a811807)

Opens up total of 100 windows by one window every second. Every windows has diferent background color.


### LineDraw

Example drawing (an optical illusion: you can see the thing two ways (opening to diferent sides))

![Screenshot from 2023-11-10 20-40-30](https://github.com/pekka1234/XlibProjects/assets/62663286/cf45d1cb-b5a8-404d-9019-2a319e9a63e0)

Program that you can draw staright lines from diferent angles with diferent colors and thiccneses.

## Running script

### Compiling

The scripts are desinged to run on the x11 display server.

First install the libraries:
```
sudo apt install libx11-dev
```

Modify the command to suit your package manager

When compiling with gcc, use these extra flags
```
gcc -O2 -o executable SCRIPTNAME.c -L /usr/X11R6/lib -lX11
```

### Executables

If compiling doesn't work you can try to run the executables from Precompiled executables folder.

