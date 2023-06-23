#include "Globales.h"
#include "Funciones.h"
#include "IA.h"

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
		VentanaBusquedaPartida	= GTK_WIDGET(gtk_builder_get_object(builder,"VentanaBusquedaPartida"));
		VentanaVisitante	= GTK_WIDGET(gtk_builder_get_object(builder,"VentanaVisitante"));
		VentanaMvM	= GTK_WIDGET(gtk_builder_get_object(builder,"VentanaMvM"));


	//botones para ventana de inicio
		pvm  		= GTK_WIDGET(gtk_builder_get_object(builder, "pvm"));
		g_signal_connect (pvm,"button-press-event",G_CALLBACK(CambiarVen),inicioabando1);
		mvm         = GTK_WIDGET(gtk_builder_get_object (builder,"mvm"));
		g_signal_connect (mvm,"button-press-event",G_CALLBACK(CambiarVen),inicioabando2);
		stats       = GTK_WIDGET(gtk_builder_get_object (builder,"stats"));
		g_signal_connect (stats,"button-press-event",G_CALLBACK(CambiarVen),inicioabando2);
		SALIR       = GTK_WIDGET(gtk_builder_get_object (builder,"SALIR"));
		g_signal_connect (SALIR,"button-press-event",G_CALLBACK(CambiarVen),salir);
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
		JuegoEnter  = GTK_WIDGET(gtk_builder_get_object(builder,"JuegoEnter"));
		g_signal_connect (JuegoEnter,"button-press-event",G_CALLBACK(BotonEnter),bandoainicio);
		HELPJUEGO	= GTK_WIDGET(gtk_builder_get_object(builder,"HELPJUEGO"));
		g_signal_connect (HELPJUEGO,"button-press-event",G_CALLBACK(CambiarVen),HELPJUEGO);
		//Edit Ayuda durante el juego
		Juegoayuda = GTK_WIDGET(gtk_builder_get_object (builder,"Juegoayuda"));
		g_signal_connect (Juegoayuda,"button-press-event",G_CALLBACK(CambiarVen),JuegoAyuda);
		//labels
		NOMBREJUGADOR = GTK_WIDGET(gtk_builder_get_object(builder,"NOMBREJUGADOR"));
		LabeldeControl= GTK_WIDGET(gtk_builder_get_object(builder,"LabeldeControl"));
		NOMBREJUGADOR2= GTK_WIDGET(gtk_builder_get_object(builder,"NOMBREJUGADOR2"));
		JuegoLabelTurno= GTK_WIDGET(gtk_builder_get_object(builder,"JuegoLabelTurno"));
		TURNO 		= GTK_WIDGET(gtk_builder_get_object(builder,"TURNO"));
		//Grilla
		EventBox	= GTK_WIDGET(gtk_builder_get_object(builder,"EventBox"));
		g_signal_connect (EventBox,"button-press-event",G_CALLBACK(ClickGrilla),NULL);
		GridJuego	= GTK_WIDGET(gtk_builder_get_object(builder,"GridJuego"));
//
	//ventana estadisticas
		ChooserStats= GTK_WIDGET(gtk_builder_get_object(builder, "ChooserStats"));
		BotonStats  = GTK_WIDGET(gtk_builder_get_object (builder,"BotonStats"));
		TextoStats	= GTK_WIDGET(gtk_builder_get_object(builder,"TextoStats"));
		gtk_text_view_set_editable(GTK_TEXT_VIEW(TextoStats), FALSE);
		//señales
		g_signal_connect (ChooserStats, "file-set",G_CALLBACK(guardar),NULL);
		g_signal_connect (BotonStats, "button-press-event",G_CALLBACK(CambiarVen),statsainicio);

	//VentanaBusquedaPartida
		BotonBusquedaPartida = GTK_WIDGET(gtk_builder_get_object (builder,"BotonBusquedaPartida"));
		g_signal_connect (BotonBusquedaPartida, "file-set",G_CALLBACK(BuscarPartida),NULL);
		BotonOkBusquedaPartida = GTK_WIDGET(gtk_builder_get_object (builder,"BotonOkBusquedaPartida"));
		g_signal_connect (BotonOkBusquedaPartida,"button-press-event",G_CALLBACK(CambiarVen),repoavisitante);

	//VentanaVisitante
		EntryVisitante = GTK_WIDGET(gtk_builder_get_object (builder,"EntryVisitante"));

	//VentanaMvM
		MvMLocal	= GTK_WIDGET(gtk_builder_get_object(builder,"MvMLocal"));
		g_signal_connect (MvMLocal,"button-press-event",G_CALLBACK(CambiarVen),selecrepo);
		MvMVisitante= GTK_WIDGET(gtk_builder_get_object(builder,"MvMVisitante"));
		g_signal_connect (MvMVisitante,"button-press-event",G_CALLBACK(CambiarVenVisitante),selecrepo);

	//VentanaVictoria
		VentanaVictoria =  GTK_WIDGET(gtk_builder_get_object(builder,"VentanaVictoria"));
		g_signal_connect (MENU,"button-press-event",G_CALLBACK(CambiarVen),MEN);
		LabelVictoria = GTK_WIDGET(gtk_builder_get_object(builder,"LabelVictoria"));

	//imganes

		//Inicio
		gtk_button_set_image(GTK_BUTTON(pvm), gtk_image_new_from_file("src/utilidades/Inicio/PLAYERVSPC.png"));
		gtk_button_set_image(GTK_BUTTON(mvm), gtk_image_new_from_file("src/utilidades/Inicio/PCVSPC.png"));
		gtk_button_set_image(GTK_BUTTON(stats), gtk_image_new_from_file("src/utilidades/Inicio/STATS.png"));
		gtk_button_set_image(GTK_BUTTON(InicioAyuda), gtk_image_new_from_file("src/utilidades/Inicio/HELPINICIO.png"));
		gtk_button_set_image(GTK_BUTTON(SALIR), gtk_image_new_from_file("src/utilidades/Inicio/SALIR.png"));
		HOPPITY  = GTK_WIDGET(gtk_builder_get_object(builder,"HOPPITY"));
		gtk_image_set_from_file(GTK_IMAGE(HOPPITY), "src/utilidades/Inicio/HOPPITY.png");
		COLDWAR  = GTK_WIDGET(gtk_builder_get_object(builder,"COLDWAR"));
		gtk_image_set_from_file(GTK_IMAGE(COLDWAR), "src/utilidades/Inicio/COLDWAR.png");
		FONDOINICIO  = GTK_WIDGET(gtk_builder_get_object(builder,"FONDOINICIO"));
		gtk_image_set_from_file(GTK_IMAGE(FONDOINICIO), "src/utilidades/Inicio/FONDOINICIO.png");

		sal  = GTK_WIDGET(gtk_builder_get_object(builder,"sal"));
		gtk_image_set_from_file(GTK_IMAGE(sal), "src/utilidades/sal.png");

		//ventana bando
		gtk_button_set_image(GTK_BUTTON(BandoAtras), gtk_image_new_from_file("src/utilidades/Bando/BACKBANDO.png"));
		gtk_button_set_image(GTK_BUTTON(AleatorioF), gtk_image_new_from_file("src/utilidades/Bando/RANDOM.png"));
		gtk_button_set_image(GTK_BUTTON(Aleatorio), gtk_image_new_from_file("src/utilidades/Bando/RANDOM.png"));
		gtk_button_set_image(GTK_BUTTON(Empezar), gtk_image_new_from_file("src/utilidades/Bando/START.png"));
		gtk_button_set_image(GTK_BUTTON(america), gtk_image_new_from_file("src/utilidades/Bando/USA.png"));
		gtk_button_set_image(GTK_BUTTON(usrr), gtk_image_new_from_file("src/utilidades/Bando/URRS.png"));
		gtk_button_set_image(GTK_BUTTON(Maquina), gtk_image_new_from_file("src/utilidades/Bando/PC.png"));
		gtk_button_set_image(GTK_BUTTON(Local), gtk_image_new_from_file("src/utilidades/Bando/PLAYER.png"));
		FONDOBANDO  = GTK_WIDGET(gtk_builder_get_object(builder,"FONDOBANDO"));
		gtk_image_set_from_file(GTK_IMAGE(FONDOBANDO), "src/utilidades/Bando/FONDOBANDO.png");
		CHOSESIDE  = GTK_WIDGET(gtk_builder_get_object(builder,"CHOSESIDE"));
		gtk_image_set_from_file(GTK_IMAGE(CHOSESIDE), "src/utilidades/Bando/CHOSESIDE.png");
		INICIO  = GTK_WIDGET(gtk_builder_get_object(builder,"INICIO"));
		gtk_image_set_from_file(GTK_IMAGE(INICIO), "src/utilidades/Bando/WHOSTARS.png");
		PLAYERNAME  = GTK_WIDGET(gtk_builder_get_object(builder,"PLAYERNAME"));
		gtk_image_set_from_file(GTK_IMAGE(PLAYERNAME), "src/utilidades/Bando/PLAYERNAME.png");
//
		//ventana CreacionPartida
		BotonCreacionPartida = GTK_WIDGET(gtk_builder_get_object(builder,"BotonCreacionPartida"));
		g_signal_connect (BotonCreacionPartida, "file-set",G_CALLBACK(guardar),NULL);
		BotonOKCreaciondePartida = GTK_WIDGET(gtk_builder_get_object(builder,"BotonOKCreaciondePartida"));
		g_signal_connect (BotonOkBusquedaPartida,"button-press-event",G_CALLBACK(funcionEspecial),repoavisitante);

		BotonBusquedaPartida = GTK_WIDGET(gtk_builder_get_object (builder,"BotonBusquedaPartida"));
		g_signal_connect (BotonBusquedaPartida, "file-set",G_CALLBACK(BuscarPartida),NULL);
		BotonOkBusquedaPartida = GTK_WIDGET(gtk_builder_get_object (builder,"BotonOkBusquedaPartida"));
		g_signal_connect (BotonOkBusquedaPartida,"button-press-event",G_CALLBACK(CambiarVen),repoavisitante);

		//ventana juego
		gtk_button_set_image(GTK_BUTTON(JuegoAtras), gtk_image_new_from_file("src/utilidades/Juego/BACKJUEGO.png"));
		gtk_button_set_image(GTK_BUTTON(Juegoayuda), gtk_image_new_from_file("src/utilidades/Juego/HELPJUEGO.png"));

		TABLERO  = GTK_WIDGET(gtk_builder_get_object(builder,"TABLERO"));
		gtk_image_set_from_file(GTK_IMAGE(TABLERO), "src/utilidades/Juego/Tablero.png");

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
