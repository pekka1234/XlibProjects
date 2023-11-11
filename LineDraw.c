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


// colors used and current color
unsigned long black, white, red, blue, green;
unsigned long curcor;

unsigned long RGB(int r, int g, int b);


// Function used by drawing code
void draw(){
    XClearWindow(dpy, w);
}

// x and y coordinates of the screen
struct coord {
    int x, y;
} dot;

// Setting up coordinates and colors
void colors(){
    dot.x = 100;
    dot.y = 100;

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
    // i is for drawing lines by one designated point to another (otherwise it would be one continous line), thicc is pen widht, curcor current color
    int i = 1;
    int thicc = 1;
    curcor = black;

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

        // Keyboard controls
        if(event.type == KeyPress && XLookupString(&event.xkey, text, 255, &key, 0) == 1){
            if(text[0] == 'r'){
                curcor = red;
            }else if (text[0] == 'b'){
                curcor = blue;
            }else if (text[0] == 'g'){
                curcor = green;
            }else if(text[0] == 'x'){
                curcor = black;
            }else if(text[0] == '+'){
                thicc += 1;
            }else if(text[0] == '-'){
                thicc -= 1;
            }
            
            // i is minused so the ryhtm doesn't mess uo
            i -= 1;
        }

        // When mouseclick
        if(event.type == ButtonPress){
            int x = event.xbutton.x, y = event.xbutton.y;

            if(i % 2 == 0){
                // Using XDrawLine as many times as thicc wants
                XSetForeground(dpy, gc, curcor);
                for(int j = 0; j < thicc; j++){
                    XDrawLine(dpy, w, gc, dot.x, dot.y, x, y);
                    XDrawLine(dpy, w, gc, dot.x - j, dot.y - j, x - j, y - j);
                }
            }

            // Setting coordinates for next line draw
            dot.x = x;
            dot.y = y;
        }

        i += 1;
        
    }
}


int main(){
    printf("Controls:\nr: red\ng: green\nb: blue\nx: black\n\n+: Thiccer line\n-: Smaller line\n");

    colors();
    xsetup();
    userinput();

    return 0;
}




// Color function
unsigned long RGB(int r, int g, int b){
    return b + (g<<8) + (r<<16);
}