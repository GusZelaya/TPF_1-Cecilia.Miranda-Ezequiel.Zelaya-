#include "Globales.h"
#include "Funciones.h"

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
	//utilidad
	tableroInicial();
	imprimirTablero();
	//asignación de ventanas
	VentanaInicio = GTK_WIDGET(gtk_builder_get_object(builder,"VentanaInicio"));
	VentanaAyuda  = GTK_WIDGET(gtk_builder_get_object(builder,"VentanaAyuda"));
	VentanaBando  = GTK_WIDGET(gtk_builder_get_object(builder,"VentanaBando"));
	VentanaJuego  = GTK_WIDGET(gtk_builder_get_object(builder,"VentanaJuego"));
	VentanaStats  = GTK_WIDGET(gtk_builder_get_object(builder,"VentanaStats"));
	VentanaSalir  = GTK_WIDGET(gtk_builder_get_object(builder,"VentanaSalir"));

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
	g_signal_connect (usrr,"button-press-event",G_CALLBACK(SetSide),rusia);
	Aleatorio	= GTK_WIDGET(gtk_builder_get_object(builder,"Aleatorio"));
	g_signal_connect (Aleatorio,"button-press-event",G_CALLBACK(SetSide),neutral);
	//Edit botones de seleccion de jugador
	Local= GTK_WIDGET(gtk_builder_get_object(builder,"Local"));
	g_signal_connect (Local,"button-press-event",G_CALLBACK(SetTurn),Loc);
	Maquina= GTK_WIDGET(gtk_builder_get_object(builder,"Maquina"));
	g_signal_connect (Maquina,"button-press-event",G_CALLBACK(SetTurn),Mac);
	AleatorioF 	= GTK_WIDGET(gtk_builder_get_object(builder,"AleatorioF"));
	g_signal_connect (AleatorioF,"button-press-event",G_CALLBACK(SetTurn),Al);


	//label nombre del jugador
	PlayerName	= GTK_WIDGET(gtk_builder_get_object(builder,"PlayerName"));
	gtk_entry_set_max_length (GTK_ENTRY (PlayerName), 19);

	//ventana salir
		//Edit botones para ventana de juego
		sii  		= GTK_WIDGET(gtk_builder_get_object(builder, "si"));
		g_signal_connect (sii,"button-press-event",G_CALLBACK(CambiarVen),si);
		//botones para ventana de inicio
		noo  		= GTK_WIDGET(gtk_builder_get_object(builder, "no"));
		g_signal_connect (noo,"button-press-event",G_CALLBACK(CambiarVen),no);

	//ventana juego
	//botones
	JuegoAtras	= GTK_WIDGET(gtk_builder_get_object(builder,"JuegoAtras"));
	g_signal_connect (JuegoAtras,"button-press-event",G_CALLBACK(CambiarVen),juegoabando);
	//Edit Ayuda durante el juego
	Juegoayuda = GTK_WIDGET(gtk_builder_get_object (builder,"Juegoayuda"));
	g_signal_connect (Juegoayuda,"button-press-event",G_CALLBACK(CambiarVen),JuegoAyuda);

	//labels
	NOMBREJUGADOR= GTK_WIDGET(gtk_builder_get_object(builder,"NOMBREJUGADOR"));
	LabeldeControl= GTK_WIDGET(gtk_builder_get_object(builder,"LabeldeControl"));
	TURNO		= GTK_WIDGET(gtk_builder_get_object(builder,"TURNO"));

	//Grilla
	EventBox	= GTK_WIDGET(gtk_builder_get_object(builder,"EventBox"));
	g_signal_connect (EventBox,"button-press-event",G_CALLBACK(ClickGrilla),NULL);
	GridJuego	= GTK_WIDGET(gtk_builder_get_object(builder,"GridJuego"));

	//ventana estadisticas
	ChooserStats= GTK_WIDGET(gtk_builder_get_object(builder, "ChooserStats"));
	BotonStats  = GTK_WIDGET(gtk_builder_get_object (builder,"BotonStats"));
	TextoStats	= GTK_WIDGET(gtk_builder_get_object(builder,"TextoStats"));

	//signals
	gtk_text_view_set_editable(GTK_TEXT_VIEW(TextoStats), FALSE);

	//señales
	g_signal_connect (ChooserStats, "file-set",G_CALLBACK(guardar),NULL);
	g_signal_connect (BotonStats, "button-press-event",G_CALLBACK(mostrar),NULL);

	if ((Estadisticas=fopen(RutaEstadisticas,"r"))==NULL)
	{
		Estadisticas=fopen(RutaEstadisticas,"w");
		fwrite(EncabezadoEstadiscas,1,strlen(EncabezadoEstadiscas),Estadisticas);
		fclose(Estadisticas);
	}
	gtk_widget_show_all (VentanaInicio);

	gtk_main();

    return 0;
 }
