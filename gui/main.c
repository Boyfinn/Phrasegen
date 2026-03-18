#include "gtk/gtk.h"
#include "gui.h"

int main(int argc, char* argv[])
{
    gtk_init(&argc, &argv);
    pBuilder = gtk_builder_new_from_file("gtkForm.glade");
    pWindow = GTK_WIDGET(gtk_builder_get_object(pBuilder, "frm_main"));
    g_signal_connect(pWindow, "destroy", G_CALLBACK(gtk_main_quit),NULL);
    gtk_builder_connect_signals(pBuilder, NULL);

    //Ptr inits
    //TODO: make a macro handler thingy for all of these?
    //props
    pCapital = GTK_WIDGET(gtk_builder_get_object(pBuilder,"com_settings_capital"));
    pDelim = GTK_WIDGET(gtk_builder_get_object(pBuilder,"com_settings_delimiter"));
    pDict = GTK_WIDGET(gtk_builder_get_object(pBuilder,"btn_settings_dictionary"));
    pSeed = GTK_WIDGET(gtk_builder_get_object(pBuilder,"btn_settings_seed"));
    pWords = GTK_WIDGET(gtk_builder_get_object(pBuilder,"spn_settings_wordcount"));

    pOutputField = GTK_WIDGET(gtk_builder_get_object(pBuilder,"ent_password_field"));

    //for now
    uSeed = time(NULL);
    gtk_widget_show(pWindow);

    gtk_main();

    printf("Test.\n");
    return 0;
}

void on_propChanged()
{
    cCapital =  (unsigned char)gtk_combo_box_get_active(GTK_COMBO_BOX(pCapital));       //cCapital is an unsigned char
    cDelim =    (unsigned char)gtk_combo_box_get_active(GTK_COMBO_BOX(pDelim));         //same for this
    sDict =     getDictPath(sDict);                                                     //char pointer
    cWords =    gtk_spin_button_get_value(GTK_SPIN_BUTTON(pWords));                     //again, unsigned char, since range is clamped to 3-16

    printf("changed.\n");   //debug stuff
    buildArgs();            //This refreshes the output when anything changes
}

void on_newSeed()   //It's a REAL shame this needs to be handled separately.
{
    uSeed = time(NULL);
    on_propChanged();
}

void buildArgs()
{
    //Build command with args...
}

char* getDictPath(char *oldDict)
{
    if (oldDict)
        g_free(oldDict);
    return gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(pDict));
}



/*
void on_form_init(){
    on_refresh_click();
}

void on_refresh_click (){
    //gchar *argSeed = g_strdup_printf("-s %u",seed);
    //TODO: arg builder func?
    gchar *argv[] = { "comtool", "-s", g_strdup_printf("%u", uSeed), NULL };
    gchar *output;
    gchar *error;
    gint exitStatus;

    //TODO: throw error popup depending on exit status
    g_spawn_sync(NULL, argv, NULL, G_SPAWN_DEFAULT, NULL, NULL, &output, &error, &exitStatus, NULL);
    g_strchomp(output);
    gtk_entry_set_text(GTK_ENTRY(pOutputField),output);
    //printf("Click.\n");
}

void on_set_case(){
    //TODO
    on_refresh_click();
}

void on_set_delim(){
    //TODO
    on_refresh_click();
}

void on_set_dict(){
    //TODO
    on_refresh_click();
}

void on_set_seed (){
    //for now, again...
    uSeed = time(NULL);
    on_refresh_click();
}

void on_set_count (){
    //TODO
    on_refresh_click();
}
*/
