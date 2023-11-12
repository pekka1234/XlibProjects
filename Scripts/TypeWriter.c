#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <stdio.h>
#include <stdlib.h>


// Declaring variables for display, screen, window and graphics
Display *dpy;
int screen;
Window w;
GC gc;


unsigned long RGB(int r, int g, int b);


// Function used by drawing code
void draw(){
    XClearWindow(dpy, w);
}

unsigned long black, white;

void colors(){
    black = RGB(0, 0, 0);
    white = RGB(255, 255, 255);
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
    // i is for drawing lines by one designated point to another (otherwise it would be one continous line), thicc is pen widht, curcor current color
    int x = 100;
    int y = 100;

    int i = 0;

    while(1){
        
        // Declaring Xevent and variables
        XEvent event;
        char text[255];
        KeySym key;

        XNextEvent(dpy, &event);


        // Step required for drawing
        if(event.type == Expose && event.xexpose.count == 0){
            draw();
        }

        // Writing
        if(event.type == KeyPress && XLookupString(&event.xkey, text, 255, &key, 0) == 1){

            XSetForeground(dpy, gc, black);


            
            if(i != 200){
                // Char to string
                char str1[2] = {text[0], '\0'};
                char str2[5] = "";
                strcpy(str2,str1);

                printf(": %s", str2);
                printf("g");
                printf("\n");

                

                XDrawString(dpy, w, gc, x, y, str2, strlen(text));

                x += 8;

            }else{
                y += 15;
                x = 100;
                i = 0;
            }

            i += 1;
            
        }
        
    }
}


int main(){
    colors();
    xsetup();
    userinput();

    return 0;
}




// Color function
unsigned long RGB(int r, int g, int b){
    return b + (g<<8) + (r<<16);
}