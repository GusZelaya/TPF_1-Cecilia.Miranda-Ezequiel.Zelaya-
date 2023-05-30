#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <time.h>

//defines chetos
#define direccion "/home/lp1-2023/eclipse_workspace/Hoppiti_interfaz_tpf/src/interfazHoppitypurete.glade"
#define inicioabando1 0
#define inicioabando2 12
#define bandoajuego 1
#define bandoainicio 2
#define juegoabando 3
#define inicioastats 4
#define inicioaayuda 5
#define ayudaainicio 6
#define usa 88
#define rusia 99
#define neutral 00
#define pVm 1
#define mVm 0


//widgets de utilidad
GtkBuilder * builder;
gchar * filename;

struct config{
	gchar   UserSide;
	gchar 	MachineSide;
	gchar 	mod;
	gchar 	username[20];
};

typedef struct config datosJuego;
datosJuego Juego;

//widgets de las ventanas

//widgets de VentaAyuda
GtkWidget * VentanaAyuda;
GtkWidget * AyudaAtras;

//widgets de VentanaBando
GtkWidget * VentanaBando;
GtkWidget * america;
GtkWidget * usrr;
GtkWidget * Aleatorio;
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
GtkWidget * JuegoAtras;
GtkWidget * LabeldeControl;
GtkWidget * NOMBREJUGADOR;
GtkWidget * TURNO;
GtkWidget * PUNTOSPLAYER;
GtkWidget * PUNTOSMAQUINA;
GtkWidget * GrillaJuego;

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

void SetMode (int data)
{
	if(data==(int)pVm)
	{
		Juego.mod='P';
	}else{
		Juego.mod='M';
	}
}
//
void SetSide(GtkWidget event_box, GdkEventButton *event, gpointer data)
{
	if(data==(int)usa)
	{
		Juego.UserSide='n';
		Juego.MachineSide='b';
	}else if(data==(int)rusia){
		Juego.UserSide='b';
		Juego.MachineSide='n';
	}else if(data==(int)neutral){
		srand(time(NULL));
		int ban=(rand()%2);
		if (ban==1)
		{
			Juego.UserSide='b';
			Juego.MachineSide='n';
		}else{
			Juego.UserSide='n';
			Juego.MachineSide='b';
		}
	}
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
	case(inicioabando1):
	// Mostramos ventanas y escondemos otras
	    gtk_widget_hide (VentanaInicio);
		SetMode(pVm);
	    gtk_widget_show_all (VentanaBando);
	    break;
	case(inicioabando2):
		gtk_widget_hide (VentanaInicio);
		SetMode(mVm);
		gtk_widget_show_all (VentanaBando);
		break;
	case(bandoajuego):
		gtk_widget_hide (VentanaBando);
		guardar_texto();
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
	case(juegoabando):
		gtk_widget_hide (VentanaJuego);
		gtk_widget_show_all (VentanaBando);
	}
}

void guardar_texto()
{
    // Obtener el contenido del campo de entrada
	strncpy(Juego.username, gtk_entry_get_text(GTK_ENTRY(PlayerName)), 19);
	gtk_label_set_text(GTK_LABEL(NOMBREJUGADOR), Juego.username);
}

/*
habilitar los botones 
->imagen dentro del botón
-->si pieza =pieza correcta
--->habilitar movimiento
--->si Movimiento correcto
---->mover imagen a lugar nuevo 
---->vaciar imagen lugar viejo
--->si Movimiento incorrecto 
----->label control=mov incorrecto
----->nuevo mov 
----->do hasta correcto
-->si pieza incorrecta
--->do hasta pieza correcta

cada mov actualizar tablero
crear matriz tablero 
si atrás borrar tablero 
*/


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
	VentanaJuego  = GTK_WIDGET(gtk_builder_get_object(builder,"VentanaJuego"));
	VentanaStats = GTK_WIDGET(gtk_builder_get_object(builder,"VentanaStats"));

	//botones para ventana de inicio
	pvm  		= GTK_WIDGET(gtk_builder_get_object(builder, "pvm"));
	g_signal_connect (pvm,"button-press-event",G_CALLBACK(CambiarVen),inicioabando1);
	mvm         = GTK_WIDGET(gtk_builder_get_object (builder,"mvm"));
	g_signal_connect (mvm,"button-press-event",G_CALLBACK(CambiarVen),inicioabando2);
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

	//botones de configuracion
	america		= GTK_WIDGET(gtk_builder_get_object(builder,"america"));
	g_signal_connect (america,"button-press-event",G_CALLBACK(SetSide),usa);
	usrr		= GTK_WIDGET(gtk_builder_get_object(builder,"usrr"));
	g_signal_connect (usrr,"button-press-event",G_CALLBACK(SetSide),usrr);
	Aleatorio	= GTK_WIDGET(gtk_builder_get_object(builder,"Aleatorio"));
	g_signal_connect (usrr,"button-press-event",G_CALLBACK(SetSide),neutral);


	//label nombre del jugador
	PlayerName	= GTK_WIDGET(gtk_builder_get_object(builder,"PlayerName"));
	gtk_entry_set_max_length (GTK_ENTRY (PlayerName), 19);


	//ventana juego
	//botones
	JuegoAtras	= GTK_WIDGET(gtk_builder_get_object(builder,"JuegoAtras"));
	g_signal_connect (JuegoAtras,"button-press-event",G_CALLBACK(CambiarVen),juegoabando);

	//labels
	NOMBREJUGADOR= GTK_WIDGET(gtk_builder_get_object(builder,"NOMBREJUGADOR"));
	LabeldeControl= GTK_WIDGET(gtk_builder_get_object(builder,"LabeldeControl"));
	TURNO		= GTK_WIDGET(gtk_builder_get_object(builder,"TURNO"));

	//Grilla
	GrillaJuego = GTK_WIDGET(gtk_builder_get_object(builder,"GrillaJuego"));

	//ventana estadisticas
	ChooserStats= GTK_WIDGET(gtk_builder_get_object(builder, "ChooserStats"));
	BotonStats  = GTK_WIDGET(gtk_builder_get_object (builder,"BotonStats"));
	TextoStats	= GTK_WIDGET(gtk_builder_get_object(builder,"TextoStats"));

	//signals
	gtk_text_view_set_editable(GTK_TEXT_VIEW(TextoStats), FALSE);

	//señales
	g_signal_connect (ChooserStats, "file-set",G_CALLBACK(guardar),NULL);
	g_signal_connect (BotonStats, "button-press-event",G_CALLBACK(mostrar),NULL);


	gtk_widget_show_all (VentanaInicio);

	gtk_main();

    return 0;
 }
