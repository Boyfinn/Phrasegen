#ifndef GUI_H
#define GUI_H

#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <ctype.h>
#include <time.h>

//TODO: DO a macro builder thingy or something for these
GtkWidget   *pWindow;
GtkWidget   *pOutputField;
GtkBuilder  *pBuilder;

unsigned int uSeed;

void on_newpass_click ();
void on_newseed_click ();
void on_dict_set();

#endif
