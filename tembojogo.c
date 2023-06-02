#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

//defines chetos
#define direccion "/home/lp1-2023/eclipse_workspace/Tembojogo/src/interfazHoppitypurete.glade"
#define inicioabando1 0
#define inicioabando2 12
#define bandoajuego 1
#define bandoainicio 2
#define juegoabando 3
#define inicioastats 4
#define inicioaayuda 5
#define ayudaainicio 6
#define neutral 00
#define rusia 88
#define usa 99
#define pVm 1
#define mVm 0
#define PuntoNegro "/home/lp1-2023/eclipse_workspace/Tembojogo/src/utilizades/PuntoNegro.png"
#define PuntoRojo "/home/lp1-2023/eclipse_workspace/Tembojogo/src/utilizades/PuntoRojo.png"
#define ErrorFicha  "Selecciona una ficha de tu equipo"
#define ErrorMovimiento "Movimiento seleccionado inválido"
#define PERSONA 1
#define PC 0
#define NEGRO 0
#define ROJO 1
#define JuegoAyuda 7
#define Loc 44
#define Mac 55
#define Al 66
#define si 11
#define no 22

//
//widgets de utilidad
GtkBuilder * builder;
gchar * filename;
gint i,j;

char tablero [16][16];
struct config{
	gchar   UserSide;
	gchar 	MachineSide;
	gchar 	mod;
	gchar 	username[20];
	gint	turno;
	gchar   UserTurn;
	gchar   MachineTurn;
};

typedef struct config datosJuego;
datosJuego Juego;

typedef struct coord{
  int x;
  int y;
}coord;
coord pcActual;
coord pcSiguiente;

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
GtkWidget * Local;
GtkWidget * Maquina;
GtkWidget * AleatorioF;

//widgets de VentanaInicio
GtkWidget * VentanaInicio;
GtkWidget * pvm;
GtkWidget * mvm;
GtkWidget * stats;
GtkWidget * InicioAyuda;

//widgets de salir
GtkWidget * sii;//Edit
GtkWidget * noo;//Edit

//widgets de VentaJuego
GtkWidget * VentanaJuego;
GtkWidget * JuegoAtras;
GtkWidget * LabeldeControl;
GtkWidget * NOMBREJUGADOR;
GtkWidget * TURNO;
GtkWidget * PUNTOSPLAYER;
GtkWidget * PUNTOSMAQUINA;
GtkWidget * GridJuego;
GtkWidget * EventBox;
GtkWidget * VentanaSalir;
GtkWidget * Juegoayuda;

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

void cleanBuffer()
{
    char c;
    while ((c = getchar()) != '\n');
}

void tableroInicial(){
    int i,j;
    for(i = 0;i<16;i++ ){
        for(j=0;j<16;j++){
            tablero[i][j] = '-';
            // está en el medio
            if((i==0 && j<5)|| (i==1 && j<5) || (i==2 && j<4) || (i==3 && j<3) || (i==4 && j<2) ){ //Posiciona las fichas Negras
        tablero[i][j] = 'R';
      }
      if((i==11 && j>13) || (i==12 && j>12) || (i==13 && j>11) || (i==14 && j>10) || (i==15 && j>10) ){ //Posiciona las fichas Blancas
        tablero[i][j] = 'N';
      }
    }
  }
}

void SetTurn(GtkWidget event_box, GdkEventButton *event, gpointer data)
{
	if(data==(int)Loc)//Si selecciona Local
	{
		Juego.UserTurn='0';//Si inicia usuario retorna 0
		Juego.MachineTurn='1';//Si incia Maquina retorna 1
	}else if(data==(int)Mac){//Si selecciona que incia maquina
		Juego.UserTurn='1';//User 1
		Juego.MachineTurn='0';//maquina0
	}else if(data==(int)Al){//Si selecciona aleaotorio
		srand(time(NULL));
		int ban=(rand()%2);
		if (ban==1)
		{
			Juego.UserTurn='1';
			Juego.MachineTurn='0';
		}else{
			Juego.UserTurn='0';
			Juego.MachineTurn='1';
		}
	}
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
void SetSide(GtkWidget *event_box, GdkEventButton *event, gpointer data)
{
	if(data==((int)usa))
	{
		Juego.UserSide='n';
		printf("h");
		Juego.MachineSide='r';
	}
	else if(data==(int)rusia){
		Juego.UserSide='r';
		Juego.MachineSide='n';
		printf("3");
	}
	else if(data==(int)neutral){
		srand(time(NULL));
		int ban=(rand()%2);
		if (ban==1)
		{
			Juego.UserSide='r';
			Juego.MachineSide='n';
		}else{
			Juego.UserSide='n';
			Juego.MachineSide='r';
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
void mostrar(GtkWidget *event_box, GdkEventButton *event, gpointer data)
{
	   int c,cont;
	    FILE *a;
	    if ((a=fopen(filename,"r"))==NULL)
	    {
	    	printf("error\n");
	    }else{
	    	for (cont=0;(c=fgetc(a))!=EOF;cont++){}
	    	printf("tamaño del archivo: %d \n",cont-1);
	    	gchar * str = copy_file_to_string(filename);
	    	    if (str != NULL)
	    	    {
	    	        printf("Contenido del archivo:\n%s\n", str);
	    	        GtkTextBuffer * buffer = gtk_text_view_get_buffer(TextoStats);
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
	case(JuegoAyuda):
			gtk_widget_show_all (VentanaAyuda);
			break;
	case(ayudaainicio):
		gtk_widget_hide (VentanaAyuda);
		gtk_widget_show_all (VentanaInicio);
		break;
	case(juegoabando):
		gtk_widget_hide (VentanaJuego);
		gtk_widget_show_all (VentanaBando);
		break;
	case(si):
			gtk_widget_destroy(VentanaJuego);
			gtk_widget_destroy(VentanaSalir);
			gtk_widget_show_all (VentanaInicio);
			break;
		//EditJuego ayuda case no
		case(no):
			gtk_widget_hide (VentanaSalir);
			gtk_widget_show_all (VentanaJuego);
			break;
	}
}

void guardar_texto()
{
    // Obtener el contenido del campo de entrada
	strncpy(Juego.username, gtk_entry_get_text(GTK_ENTRY(PlayerName)), 19);
	gtk_label_set_text(GTK_LABEL(NOMBREJUGADOR), Juego.username);
	return;
}

void ClickGrilla (GtkWidget *event_box, GdkEventButton *event, gpointer data)
{
	static int contador=0;
	i = (GUINT_FROM_LE(event->y) / 20); // 20 =20 px
	j = (GUINT_FROM_LE(event->x) / 20);
	if (contador==0)
	{
		if((Juego.UserSide)=='n')
		{
			if(tablero[i][j]=='N')
			{
				contador++;
				pcActual.x=i;
				pcActual.y=j;
				gtk_label_set_text(GTK_LABEL(LabeldeControl), " Ficha seleccionada\n elija a donde moverla");
				//gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(GridJuego),j,i)),PuntoNegro);
			}else{
				gtk_label_set_text(GTK_LABEL(LabeldeControl), ErrorFicha);
			}
		}
		if((Juego.UserSide)=='r')
		{
			if (tablero[i][j]=='R')
			{
				contador++;
				pcActual.x=i;
				pcActual.y=j;
				gtk_label_set_text(GTK_LABEL(LabeldeControl), " Ficha seleccianada\n elija a donde moverla");
				//gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(GridJuego),j,i)),PuntoRojo);
			}else{
				gtk_label_set_text(GTK_LABEL(LabeldeControl), ErrorFicha);
			}
		}
	}else if (contador==1){
		if((Juego.UserSide)=='n')
		{
			if(tablero[i][j]=='-')
			{
				pcSiguiente.x=i;
				pcSiguiente.y=j;
				gtk_label_set_text(GTK_LABEL(LabeldeControl), "movimiento valido");
				gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(GridJuego),j,i)),PuntoNegro);

			}else{
				gtk_label_set_text(GTK_LABEL(LabeldeControl), ErrorMovimiento);
				contador--;
			}
		}
		if((Juego.UserSide)=='r')
		{
			if (tablero[i][j]=='-')
			{
				pcSiguiente.x=i;
				pcSiguiente.y=j;
				gtk_label_set_text(GTK_LABEL(LabeldeControl), "movimiento valido");
				gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(GridJuego),j,i)),PuntoRojo);
			}else{
				gtk_label_set_text(GTK_LABEL(LabeldeControl), ErrorMovimiento);
				contador--;
			}
		}
	}
}


void imprimirTablero(){
    //Imprime tablero
    int i,j;
    printf("Tablero:\n");
    printf("\t ");
    for(i=0;i<16;i++){
        printf("\t %d",i);
    }
    printf("\n");
    for(i=0;i<16;i++){
        printf("\t %d",i);
        for(j=0;j<16;j++){
            printf("\t %c", tablero[i][j]);
        }
        printf("\n");
    }
}

int victoriaRojo()
{
  int cont=0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3 - i; j++) {
            if (tablero[i][j]== 'R'){
                cont+=1;
            }
        }
    }
  if (tablero[1][4]=='R')
  {
    cont+=1;
  }
  if (tablero[2][3]=='R')
  {
    cont+=1;
  }
  if (tablero[3][2]=='R')
  {
    cont+=1;
  }
  if (tablero[4][1]=='R')
  {
    cont+=1;
  }
    if (cont==19)
    {
      return 1;
    }
    return 0;
}

int victoriaNegro()
{
  int cont=0;
  for (int i=11;i<16;i++)
  {
    for(int j=15;j>11;j--)
    {
      if (tablero[i][j])
      {
        cont+=1;
      }
    }
  }
  if (tablero[11][14]=='N')
  {
    cont+=1;
  }
  if (tablero[12][13]=='N')
  {
    cont+=1;
  }
  if (tablero[13][12]=='N')
  {
    cont+=1;
  }
  if (tablero[14][11]=='N')
  {
    cont+=1;
  }
  if (cont==19)
  {
    return 1;
  }
  return 0;
}

int checkJugada(coord pcActual,coord pcSiguiente,int turno,int colorJugador){
    int coord[4] = {pcActual.x,pcActual.y,pcSiguiente.x,pcSiguiente.y};
    bool isValid = false;
    int absDiffI = abs(coord[0]-coord[2]);
    int absDiffJ = abs(coord[1]-coord[3]);
    //No se puede seleccionar una pieza vacia
    if(tablero[coord[0]][coord[1]] == '-' && coord[0] == coord[2] && coord[1] == coord[3]){
        return false;
    }
    if(absDiffI <= 1 && absDiffJ <= 1){
        isValid = (tablero[coord[2]][coord[3]] == '-')? true: false;
    }else{//es un salto
        if (turno==PERSONA){
            int cont=0;
            int salto;
            int victoria = 0;
            do
            {
                //si o si el primer salto pasa por aca
                if(((absDiffI == 2 && absDiffJ == 2) || (absDiffI == 0 && absDiffJ == 2) || (absDiffI == 2 && absDiffJ == 0)) && cont==0){
                    isValid = (tablero[coord[2]][coord[3]] != '-')? false: isJumpable(tablero,coord);
                    cont++;
                    pcActual=pcSiguiente;
                    tablero[coord[0]][coord[1]] = '-';
                    tablero[coord[2]][coord[3]] = (colorJugador = ROJO?'B':'N');
        			victoria=(colorJugador = ROJO?victoriaRojo():victoriaNegro());
        			imprimirTablero();
        			if (victoria!=0)
                    {
                       // printf("VICTORIA DE %s", nombre);
                     //   break;
                    }
                }else{
                    if((absDiffI == 2 && absDiffJ == 2) || (absDiffI == 0 && absDiffJ == 2) || (absDiffI == 2 && absDiffJ == 0)){
                        printf("Desea realizar otro salto? 1 --> Si, 2 --> No:\n");
                        cleanBuffer();
                        scanf ("%d",&salto);
                        cleanBuffer();
                        if (salto==1)//si desea realizar otro salto
                        {
                        //entre a la funcion de condicion de salto
                            //elegirCoord("Elija el proximo salto",&pcSiguiente);
                            int coord[4] = {pcActual.x,pcActual.y,pcSiguiente.x,pcSiguiente.y};
//                            int absDiffI = abs(coord[0]-coord[2]);
//                            int absDiffJ = abs(coord[1]-coord[3]);
                            isValid = (tablero[coord[2]][coord[3]] != '-')? false: isJumpable(tablero,coord);
                            pcActual=pcSiguiente;
                            tablero[coord[0]][coord[1]] = '-';
                			tablero[coord[2]][coord[3]] = (colorJugador = ROJO?'B':'N');
                			victoria=(colorJugador = ROJO?victoriaRojo():victoriaNegro());
                			imprimirTablero();
                			if (victoria!=0)
                			{
                			//  printf("VICTORIA DE %s", nombre);
                			//  break;
                				//
                			}
                        }
                        if (salto == 2)
                        {
                        	return 1;
                        	isValid = false;
                        }else{
                            printf("Valor invalido. Intenta nuevamente.\n");
                        }
                    }else{
                        isValid = false;
                    }
                }
            }while (isValid==true);
        }else{//es un salto
            if((absDiffI == 2 && absDiffJ == 2) || (absDiffI == 0 && absDiffJ == 2) || (absDiffI == 2 && absDiffJ == 0) ){
            isValid = (tablero[coord[2]][coord[3]] != '-')? false: isJumpable(tablero,coord);
            }
        }
    }
    return isValid;
}

int isJumpable(char tablero[16][16],int coord[4]){
    bool isValid = false;
    int diffI = (coord[2]-coord[0])/2;
    int diffJ = (coord[3]-coord[1])/2;
    int midPosicI = coord[0] + diffI, midPosicJ = coord[1] + diffJ;
    //-midPosic es la coordenada de la pieza a la que se quiere saltar
    isValid = (tablero[midPosicI][midPosicJ] == '-')? false: true;
    isValid = (diffI == 0 && diffJ == 0)? false: isValid;
    return isValid;
}

int coinFlip( int range){
  static int xd = 0;
  (xd == 0)? srand(time(NULL)):1;
  xd++;
  return rand()%(range+1);
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
	//utilidad
	tableroInicial();
	imprimirTablero();
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
//

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
	Local= GTK_WIDGET(gtk_builder_get_object(builder,"america"));
	g_signal_connect (Local,"button-press-event",G_CALLBACK(SetSide),Loc);
	Maquina= GTK_WIDGET(gtk_builder_get_object(builder,"usrr"));
	g_signal_connect (Maquina,"button-press-event",G_CALLBACK(SetSide),Mac);
	AleatorioF= GTK_WIDGET(gtk_builder_get_object(builder,"Aleatorio"));
	g_signal_connect (AleatorioF,"button-press-event",G_CALLBACK(SetSide),Al);


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


	gtk_widget_show_all (VentanaInicio);

	gtk_main();

    return 0;
 }
