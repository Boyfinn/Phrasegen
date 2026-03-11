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
    pGrid = GTK_WIDGET(gtk_builder_get_object(pBuilder,"grd_main"));
    pNewPass = GTK_WIDGET(gtk_builder_get_object(pBuilder,"btn_test"));
    pNewSeed = GTK_WIDGET(gtk_builder_get_object(pBuilder,"btn_newseed"));
    pOutputField = GTK_WIDGET(gtk_builder_get_object(pBuilder,"ent_password"));

    //for now
    uSeed = time(NULL);
    gtk_widget_show(pWindow);

    gtk_main();

    printf("Test.\n");
    return 0;
}

void on_newpass_click (){
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

void on_newseed_click ()
{
    //for now, again...
    uSeed = time(NULL);
}
