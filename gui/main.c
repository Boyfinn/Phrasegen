#include "gtk/gtk.h"
#include "gui.h"

int main(int argc, char* argv[]) {
    gtk_init(&argc, &argv);
    pBuilder = gtk_builder_new_from_file(GUILAYOUT);
    pWindow = GTK_WIDGET(gtk_builder_get_object(pBuilder, "frm_main"));
    g_signal_connect(pWindow, "destroy", G_CALLBACK(gtk_main_quit),NULL);
    gtk_builder_connect_signals(pBuilder, NULL);

    //Ptr inits
    //TODO: make a macro handler thingy for all of these?
    //props
    pCapital =  GTK_WIDGET(gtk_builder_get_object(pBuilder,"com_settings_capital"));
    pDelim =    GTK_WIDGET(gtk_builder_get_object(pBuilder,"com_settings_delimiter"));
    pDict =     GTK_WIDGET(gtk_builder_get_object(pBuilder,"btn_settings_dictionary"));
    pSeed =     GTK_WIDGET(gtk_builder_get_object(pBuilder,"btn_settings_seed"));
    pWords =    GTK_WIDGET(gtk_builder_get_object(pBuilder,"spn_settings_wordcount"));

    pOutputField = GTK_WIDGET(gtk_builder_get_object(pBuilder,"ent_password_field"));
    gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(pDict), DEFAULTDICTIONARY);

    //for now
    uSeed = time(NULL);
    gtk_widget_show(pWindow);

    gtk_main();
    return 0;
}

void on_formRealized() {
    on_propChanged();
}

void on_copyClipboard() {
    //TODO: implement please
    GtkClipboard* clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
    gtk_clipboard_set_text(clipboard, gtk_entry_get_text(GTK_ENTRY(pOutputField)),-1);
    //printf("Todo...\n");
}

void on_propChanged() {
    cCapital =  gtk_combo_box_get_active(GTK_COMBO_BOX(pCapital));     //cCapital is an unsigned char
    cDelim =    pDelims[gtk_combo_box_get_active(GTK_COMBO_BOX(pDelim))];
    sDict =     getDictPath(sDict);
    cWords =    gtk_spin_button_get_value(GTK_SPIN_BUTTON(pWords));

    buildArgs();            //This refreshes the output when anything changes
}

void on_newSeed() {   //It's a REAL shame this needs to be handled separately.
    uSeed = time(NULL);
    on_propChanged();
}

void buildArgs() {
    //Ensure everything has a default value before building PLEASE
    //debug stuff
    /*if(!sDict)
        sDict = DEFAULTDICTIONARY;*/    //already fixed in entry
    /*
    printf("----ARGS----\n");
    printf("cCapital: %i\n", cCapital);
    printf("cDelim:   %s\n", cDelim);
    printf("sDict:    %s\n", sDict);
    printf("uSeed:    %u\n", uSeed);
    printf("cWords:   %i\n", cWords);
    */
    //special cases:
    GPtrArray *argv = g_ptr_array_new_with_free_func(g_free);   //Didn't know this existed'
    g_ptr_array_add(argv, g_strdup("phrasegen"));

for (int i = 0; paramArgs[i].pFlag != NULL; i++) {
    g_ptr_array_add(argv, g_strdup(paramArgs[i].pFlag));
    switch (paramArgs[i].type) {

            case ARG_UINT:{
                g_ptr_array_add(argv, g_strdup_printf("%u",   *(unsigned int  *)paramArgs[i].pValue));
                break;
            }
            case ARG_UCHR:{
                g_ptr_array_add(argv, g_strdup_printf("%hhu", *(unsigned char *)paramArgs[i].pValue));
                break;
            }
            case ARG_STRN:{
                g_ptr_array_add(argv, g_strdup(*(char **)paramArgs[i].pValue));
                break;
            }
        }
    }

    g_ptr_array_add(argv, NULL);
    genPassword((gchar **)argv->pdata);
    g_ptr_array_free(argv, TRUE);   //TODO: Maybe handle after... idk
}

void genPassword(gchar **argv) {
    /*
    for (int i = 0; argv[i] != NULL; i++)
    printf("argv[%d]: %s\n", i, argv[i]);
    */
    gchar * output =        NULL;
    gchar * error =         NULL;
    gint    exitStatus =    0;

    //TODO: handle error with popup or something
    g_spawn_sync(NULL, argv, NULL, G_SPAWN_DEFAULT, NULL, NULL, &output, &error, &exitStatus, NULL);
    g_strchomp(output);
    gtk_entry_set_text(GTK_ENTRY(pOutputField),output);
}

char* getDictPath(char *oldDict) {
    if (oldDict)
        g_free(oldDict);
    return gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(pDict));
}
