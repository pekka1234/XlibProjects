#include <X11/Xlib.h>
#include <unistd.h>   // So we got the profile for 10 seconds

#define NIL (0)       // A name for the void pointer

void graphic(int color1, int color2){
    Display *dpy = XOpenDisplay(NIL);
    // Create the window

    Window w = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 0, 0, 500, 500, 0, color1, color2);

    // "Map" the window (that is, make it appear on the screen)

    XMapWindow(dpy, w);

    // Create a "Graphics Context"

    GC gc = XCreateGC(dpy, w, 0, NIL);

    // Send the "DrawLine" request to the server

    XFlush(dpy);

    // Wait for 10 seconds
}


int main(){
    for(int i = 0; i < 100; i++){
        graphic(200 - i * 2, i * 2);
        sleep(1);
    }
}