#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

//defines chetos
#define direccion "/home/lp1-2023/eclipse_workspace/Hoppiti_interfaz_tpf/Debug/interfazHoppity.glade"
#define inicioabando 0
#define bandoajuego 1
#define bandoainicio 2
#define juegoabando 3
#define inicioastats 4
#define inicioaayuda 5
#define ayudaainicio 6


//widgets de utilidad
GtkBuilder * builder;
gchar * filename;

//widgets de las ventanas

//widgets de VentaAyuda
GtkWidget * VentanaAyuda;
GtkWidget * AyudaAtras;

//widgets de VentanaBando
GtkWidget * VentanaBando;
GtkWidget * america;
GtkWidget * usrr;
GtkWidget * aleatrorio;
GtkWidget * BandoAtras;
GtkWidget * PlayerName;
GtkWidget * Empezar;

//widgets de VentanaInicio
GtkWidget * VentanaInicio;
GtkWidget * pvm;
GtkWidget * mvm;
GtkWidget * stats;
GtkWidget * InicioAyuda;

//widgets de VentaJuego
GtkWidget * VentanaJuego;
GtkWidget * JuegoOpciones;
GtkWidget * JuegoAyuda;
GtkWidget * JuegoAtras;
GtkWidget * LabeldeControl;
GtkWidget * NOMBREJUGADOR;
GtkWidget * TURNO;
GtkWidget * PUNTOSPLAYER;
GtkWidget * PUNTOSMAQUINA;


//widgets de VentanaStats
GtkWidget * VentanaStats;
GtkWidget * ChooserStats;
GtkWidget * BotonStats;
GtkWidget * TextoStats;

//void GuardarNombre(GtkWidget *event_box, Gdklabel *event, gpointer data)
//funcion para copiar el contenido de un archivo dentro de una cadena
char* copy_file_to_string(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "No se pudo abrir el archivo: %s\n", filename);
        return NULL;
    }

    // Obtener el tamaño del archivo
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    // Crear una cadena del tamaño adecuado
    char* str = (char*)malloc((file_size + 1) * sizeof(char));
    if (str == NULL) {
        fprintf(stderr, "No se pudo asignar memoria para la cadena\n");
        fclose(file);
        return NULL;
    }

    // Leer los caracteres del archivo y copiarlos en la cadena
    size_t read_size = fread(str, sizeof(char), file_size, file);
    if (read_size != file_size) {
        fprintf(stderr, "No se pudo leer completamente el archivo\n");
        fclose(file);
        free(str);
        return NULL;
    }

    // Agregar el terminador de cadena al final
    str[file_size] = '\0';

    fclose(file);
    return str;
}

void guardar(GtkFileChooserButton *button, gpointer user_data)
{
    GtkFileChooser *file_chooser = GTK_FILE_CHOOSER(button);
    // Obtener la dirección del archivo seleccionado
    filename = gtk_file_chooser_get_filename(file_chooser);
    //vuelve a la pantalla anterior
    g_print("archivo: %s \n",filename);
}
//funcion para confirmar que quiere abrir el archivo seleccionado
void mostrar(GtkWidget event_box, GdkEventButton *event, gpointer data)
{
	   int c,cont;
	    FILE *a;
	    if ((a=fopen(filename,"r"))==NULL)
	    {
	    	printf("error\n");
	    }else{
	    	for (cont=0;(c=fgetc(a))!=EOF;cont++){}
	    	cont-=1;
	    	printf("tamaño del archivo: %d \n",cont);
	    	char* str = copy_file_to_string(filename);
	    	    if (str != NULL) {
	    	        printf("Contenido del archivo:\n%s\n", str);

	    	        GtkTextBuffer* buffer = gtk_text_view_get_buffer(TextoStats);
	    	        GtkTextIter end_iter;
					gtk_text_buffer_get_end_iter(buffer, &end_iter);
					gtk_text_buffer_insert(buffer, &end_iter, str, -1);
	    	        free(str);
	    	    }
	    }
}

//funcion que inicia el juego en Jugador vs maquina
void CambiarVen (GtkWidget *event_box, GdkEventButton *event, gpointer data)
{
	switch((int)data)
	{
	case(inicioabando):
	// Mostramos ventanas y escondemos otras
	    gtk_widget_hide (VentanaInicio);
	    gtk_widget_show_all (VentanaBando);
	    break;
	case(bandoajuego):
		gtk_widget_hide (VentanaBando);
		gtk_widget_show_all (VentanaJuego);
		break;
	case(bandoainicio):
		gtk_widget_hide (VentanaBando);
		gtk_widget_show_all (VentanaInicio);
		break;
	case(inicioastats):
		gtk_widget_hide (VentanaInicio);
		gtk_widget_show_all (VentanaStats);
		break;
	case(inicioaayuda):
		gtk_widget_hide (VentanaInicio);
		gtk_widget_show_all (VentanaAyuda);
		break;
	case(ayudaainicio):
		gtk_widget_hide (VentanaAyuda);
		gtk_widget_show_all (VentanaInicio);
		break;
	}
}


int main (int argc, char *argv[])
 {
	guint ret;
	GError *error = NULL;

	gtk_init (&argc, &argv);

	builder = gtk_builder_new();
	ret = gtk_builder_add_from_file(builder, direccion, &error);
	if (ret == 0)
		{
			g_print("Error en la función gtk_builder_add_from_file:\n%s", error->message);
			return 1;
		}

	//asignación de ventanas
	VentanaInicio = GTK_WIDGET(gtk_builder_get_object(builder,"VentanaInicio"));
	VentanaAyuda  = GTK_WIDGET(gtk_builder_get_object(builder,"VentanaAyuda"));
	VentanaBando  = GTK_WIDGET(gtk_builder_get_object(builder,"VentanaBando"));
	VentanaJuego  = GTK_WIDGET(gtk_builder_get_object(builder,"VentaJuego"));
	VentanaStats = GTK_WIDGET(gtk_builder_get_object(builder,"VentanaStats"));

	//botones para ventana de inicio
	pvm  		= GTK_WIDGET(gtk_builder_get_object(builder, "pvm"));
	g_signal_connect (pvm,"button-press-event",G_CALLBACK(CambiarVen),inicioabando);
	mvm         = GTK_WIDGET(gtk_builder_get_object (builder,"mvm"));
	g_signal_connect (mvm,"button-press-event",G_CALLBACK(CambiarVen),inicioabando);
	stats       = GTK_WIDGET(gtk_builder_get_object (builder,"stats"));
	g_signal_connect (stats,"button-press-event",G_CALLBACK(CambiarVen),inicioastats);
	InicioAyuda = GTK_WIDGET(gtk_builder_get_object (builder,"InicioAyuda"));
	g_signal_connect (InicioAyuda,"button-press-event",G_CALLBACK(CambiarVen),inicioaayuda);

	//botones de ventana ayuda
	AyudaAtras  = GTK_WIDGET (gtk_builder_get_object(builder,"AyudaAtras"));
	g_signal_connect (AyudaAtras,"button-press-event",G_CALLBACK(CambiarVen),ayudaainicio);

	//botones de ventana bando
	//botones de acceso
	BandoAtras  = GTK_WIDGET(gtk_builder_get_object(builder,"BandoAtras"));
	g_signal_connect (BandoAtras,"button-press-event",G_CALLBACK(CambiarVen),bandoainicio);
	Empezar     = GTK_WIDGET(gtk_builder_get_object(builder,"Empezar"));
	g_signal_connect (Empezar,"button-press-event",G_CALLBACK(CambiarVen),bandoajuego);
	//label nombre del jugador
	PlayerName	= GTL_WIDGET(gtk_builder_get_object(builder,"PlayerName"));
	g_signal_connect (PlayerName,"insert-text",G_CALLBACK(GuardarNombre),NULL);




	ChooserStats= GTK_WIDGET(gtk_builder_get_object(builder, "ChooserStats"));
	BotonStats  = GTK_WIDGET(gtk_builder_get_object (builder,"BotonStats"));
	TextoStats	= GTK_WIDGET(gtk_builder_get_object(builder,"TextoStats"));

	//utilidades
	gtk_text_view_set_editable(GTK_TEXT_VIEW(TextoStats), FALSE);

	//signals
	gtk_text_view_set_editable(GTK_TEXT_VIEW(TextoStats), FALSE);

	//señales
	g_signal_connect (ChooserStats, "file-set",G_CALLBACK(guardar),NULL);
	g_signal_connect (BotonStats, "button-press-event",G_CALLBACK(mostrar),NULL);


	gtk_widget_show_all (VentanaInicio);

	gtk_main();

    return 0;
 }
