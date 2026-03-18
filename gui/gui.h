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

#define DEFAULTDICTIONARY "words_alpha.txt"

const char *pDelims[] = {"", "_", "-"};

typedef struct {
    const gchar *pFlag;
    const gchar *pFormat;
    void        *pValue;
} Arg;


//Prop vars TODO: avoid namespace pollution by wrapping into a struct maybe?
const char      *cCapital;
const char      *cDelim;
char            *sDict;
unsigned int    uSeed;
unsigned char   cWords;

Arg paramArgs[] = {
    {"-s", "%u",    &uSeed},
    {"-a", "%s",    &sDict},
    {"-d", "%s",    &cDelim},
    {"-n", "%hhu",  &cWords},
    { NULL , NULL, NULL}
};

//TODO: DO a macro builder thingy or something for these
GtkWidget       *pWindow;
GtkWidget       *pOutputField;
GtkBuilder      *pBuilder;

//Prop widgets
GtkWidget       *pCapital;
GtkWidget       *pDelim;
GtkWidget       *pDict;
GtkWidget       *pSeed;
GtkWidget       *pWords;

//GTK events
void on_propChanged();
void on_newSeed();  //I hate how this needs to be handled separately

//Funcs&methods
void buildArgs();
void genPassword(gchar **argv);
char* getDictPath(char *oldDict);

#endif
