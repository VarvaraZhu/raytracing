/* 
	Remember to compile try:
		1) gcc hi.c -o hi -lX11
		2) gcc hi.c -I /usr/include/X11 -L /usr/X11/lib -lX11
		3) gcc hi.c -I /where/ever -L /who/knows/where -l X11

	Brian Hammond 2/9/96.    Feel free to do with this as you will!
*/

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

#include <stdio.h>
#include <stdlib.h>

#include "retr.h"

/* here are our X variables */

/* here are our X routines declared! */
void init_x(Display * dis, int screen, Window win, GC gc);
void close_x(Display * dis, int screen, Window win, GC gc);
void redraw(Display * dis, int screen, Window win, GC gc);

main () {
    Display *dis;
    int screen;
    Window win;
    GC gc;

	init_x(dis, screen, win, gc);
    Draw_Scene(dis, win, gc);
    close_x(dis, screen, win, gc);
}

void init_x(Display * dis, int screen, Window win, GC gc) {
/* get the colors black and white (see section for details) */        
	unsigned long black,white;

	dis = XOpenDisplay((char *)0);
   	screen = DefaultScreen(dis);
	black = BlackPixel(dis,screen),
	white = WhitePixel(dis, screen);
   	win = XCreateSimpleWindow(dis,DefaultRootWindow(dis), 0, 0, 	
		640, 640, 5, black, white);
	XSetStandardProperties(dis, win, "Howdy", "Hi", None, NULL, 0, NULL);
	XSelectInput(dis, win, ExposureMask|ButtonPressMask|KeyPressMask);
        gc=XCreateGC(dis, win, 0,0);        
	XSetBackground(dis, gc, white);
	XSetForeground(dis, gc, black);
	XClearWindow(dis, win);
	XMapRaised(dis, win);
};

void close_x(Display * dis, int screen, Window win, GC gc) {
	XFreeGC(dis, gc);
	XDestroyWindow(dis,win);
	XCloseDisplay(dis);	
	exit(1);				
};

void redraw(Display * dis, int screen, Window win, GC gc) {
	XClearWindow(dis, win);
};
