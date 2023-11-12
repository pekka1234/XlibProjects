#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Declaring variables for display, screen, window and graphics
Display *dpy;
int screen;
Window w;
GC gc;


// colors used and current color
unsigned long black, white, red, blue, green;
unsigned long curcor;

unsigned long RGB(int r, int g, int b);


// Function used by drawing code
void draw(){
    XClearWindow(dpy, w);
}

// Setting up coordinates and colors
void colors(){
    black = RGB(0, 0, 0);
    white = RGB(255, 255, 255);
    red = RGB(255, 0, 0);
    blue = RGB(0, 0, 255);
    green = RGB(0, 255, 0);
}



// X server setup
void xsetup(){
    // Creating basic dispaly elements
    dpy = XOpenDisplay(0); 
    screen = DefaultScreen(dpy);

    // Creating window and setting properties
    w = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 0, 0, 500, 500, 5, black, white);
    XSetStandardProperties(dpy, w, "Suora Piirto", "Versio Super", None, NULL, 0, NULL);

    // Detects keyboard presses
    XSelectInput(dpy, w, ExposureMask | ButtonPressMask | KeyPressMask);

    // For drawing and general graphics
    gc = XCreateGC(dpy, w, 0, 0);
    XSetBackground(dpy, gc, white);
    XSetForeground(dpy, gc, black);

    XClearWindow(dpy, w);
    XMapRaised(dpy, w);
}


void userinput(){
    
    // Grayscale by adding XLineDraws
    for(int i = 0; i < 4; i++){
        // For evry color scale
        for(int j = 0; j < 1020; j++){

            // Changig color and putting correct scale line
            if(i == 0){
                XSetForeground(dpy, gc, RGB((int)(j / 4), (int)(j / 4), (int)(j / 4)));
            }else if(i == 1){
                XSetForeground(dpy, gc, RGB(255, (int)(j / 4), (int)(j / 4))); 
            }else if(i == 2){
                XSetForeground(dpy, gc, RGB((int)(j / 4), 255, (int)(j / 4))); 
            }else if(i == 3){
                XSetForeground(dpy, gc, RGB((int)(j / 4), (int)(j / 4), 255)); 
            }

            XDrawLine(dpy, w, gc, 0, j, 1800, j);

            fflush(stdout);
            XFlush(dpy);

        }

        sleep(5);
        XClearWindow(dpy, w);

    }
    
    
}


int main(){
    

    colors();
    xsetup();
    XFlush(dpy);
    sleep(5);
    userinput();

    sleep(1000);

    return 0;
}




// Color function
unsigned long RGB(int r, int g, int b){
    return b + (g<<8) + (r<<16);
}