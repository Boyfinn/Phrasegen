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

const char *pDelims[] = {"NONE", "_", "-", " "};

typedef enum {
    ARG_UINT,
    ARG_UCHR,
    ARG_STRN
} arg_type;

typedef struct {
    const gchar *pFlag;
    arg_type    type;
    void        *pValue;
} Arg;


//Prop vars TODO: avoid namespace pollution by wrapping into a struct maybe?
unsigned char   cCapital;
const char      *cDelim;
char            *sDict;
unsigned int    uSeed;
unsigned char   cWords;

Arg paramArgs[] = {
    {"-u",ARG_UCHR,     &cCapital},
    {"-s",ARG_UINT,     &uSeed},
    {"-a",ARG_STRN,     &sDict},
    {"-d",ARG_STRN,     &cDelim},
    {"-n",ARG_UCHR,     &cWords},
    { NULL }
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
