/*
 * Funciones.h
 *
 *  Created on: 10 jun. 2023
 *      Author: lp1-2023
 */

#ifndef FUNCIONES_H_
#define FUNCIONES_H_
#include "Globales.h"

//void GuardarNombre(GtkWidget *event_box, Gdklabel *event, gpointer data)
//funcion para copiar el contenido de un archivo dentro de una cadena

void guardar_texto()
{
    // Obtener el contenido del campo de entrada
	strncpy(Juego.username, gtk_entry_get_text(GTK_ENTRY(PlayerName)), 19);
	gtk_label_set_text(GTK_LABEL(NOMBREJUGADOR), Juego.username);
	return;
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

void CrearEstadisticas()
{
	StructEstadisticas GuardadoStats;
	char str[19];
	int cont=0;
	char c;
	while((Estadisticas=fopen(RutaEstadisticas,"r+"))==NULL) //se abre el archivo de estadisticas en modo lectura y escritura
	{
		printf("Error al abrir la carpeta de estadisticas para la lectura e ingreso \n");
		return;
	}
	do
	{
		for(;(c=fgetc(Estadisticas))!=':';cont++) //se leen los primeros caracteres de cada linea hasta : para determinar si el jugador ya est[a registrado
		{
			str[cont]=c;
		}
		if((strncmp(str,Juego.username,19))==0)//si encuentra un jugador registrado lo que hace es copiar los elementos que se encuentran luego de los : dentro de las variables
											//tipo struct que se crearon para almavenar los datos
		{
			fread(&GuardadoStats,sizeof(StructEstadisticas),1,Estadisticas);
			victoria==0?GuardadoStats.ganadas++:GuardadoStats.perdidas++;
			GuardadoStats.totales++;//se modifican los valroes de las variables dependiendo de si el jugador gana o pierde la partida
			victoria=1;
			fseek(Estadisticas,-sizeof(StructEstadisticas),SEEK_CUR);//se devuelve el puntero del archivo al lugar justo antes de los datos cargados anteriormente para modificarlos
			fwrite(&GuardadoStats, sizeof(StructEstadisticas), 1, Estadisticas);
			fclose(Estadisticas);
			return;
		}else{
			if (fseek(Estadisticas, 33, SEEK_CUR) != 0)
			{
				printf("Error al mover el puntero del archivo.\n");
			}
		}
		cont=0;
	}while(feof(Estadisticas)); //si no se encontro un jugador registrado se crea un registro del mismo justo al final del archivo
	char a[200];
	strcat(a,Juego.username);
	strcat(a,":");
	strcat(a,(const char*)&GuardadoStats);
	fseek(Estadisticas,0,SEEK_END);
	fprintf(Estadisticas,"%s",a);
	fclose(Estadisticas);
}

int coinFlip( int range){
  static int xd = 0;
  (xd == 0)? srand(time(NULL)):1;
  xd++;
  return rand()%(range+1);
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

int checkJugada(coord pcActual,coord pcSiguiente,int colorJugador){
    bool isValid = false;
    int coord[4] = {pcActual.x,pcActual.y,pcSiguiente.x,pcSiguiente.y};
    int absDiffI = abs(coord[0]-coord[2]);
    int absDiffJ = abs(coord[1]-coord[3]);
    //No se puede seleccionar una pieza vacia
   //dkvkfnvkdfnvjnvjndvjnsjvn
    if(tablero[coord[0]][coord[1]] == '-' && coord[0] == coord[2] && coord[1] == coord[3]){
        return false;
    }
    //
    if(absDiffI <= 1 && absDiffJ <= 1){
        isValid = (tablero[coord[2]][coord[3]] == '-')? true: false;
        tablero[coord[0]][coord[1]]='-';
        tablero[coord[2]][coord[3]]=colorJugador;
    }else{//es un salto
		static int cont=0;
		int victoria = 0;
		do
		{
			//si o si el primer salto pasa por aca
			if(((absDiffI == 2 && absDiffJ == 2) || (absDiffI == 0 && absDiffJ == 2) || (absDiffI == 2 && absDiffJ == 0)) && cont==0){
				isValid = (tablero[coord[2]][coord[3]] != '-')? false: isJumpable(tablero,coord);
				cont++;
				BanderaLugar[0]=coord[2];//guarda en un vector auxiliar la casilla a donde se movera la pieza
				BanderaLugar[1]=coord[3];//
				BanderaLugar[2]=cont;
				tablero[coord[0]][coord[1]] = '-';
				tablero[coord[2]][coord[3]] = (colorJugador = ROJO?'R':'N');
				victoria=(colorJugador = ROJO?victoriaRojo():victoriaNegro());
				imprimirTablero();
				if (victoria!=0)
				{
					CrearEstadisticas();
					gtk_widget_destroy(VentanaJuego);
					/*
					 * if victoria=1 gana el rojo
					 * 		ganador=nombre del jugador rojo
					 * 		abrir ventana de victoria
					 * 			avisar que el ganador es el rojo
					 * 	else
					 * 		ganador=nombre del jugador negro
					 * 		abrir ventand de victoria
					 * 			avisar que el ganador es el negro
					 *
					 */
				}
			}else{
				if((absDiffI == 2 && absDiffJ == 2) || (absDiffI == 0 && absDiffJ == 2) || (absDiffI == 2 && absDiffJ == 0)){
						if (BanderaLugar[0]==coord[0] && BanderaLugar[1]==coord[1])//solamente permite el segundo salto si la ficha seleccionada es la misma que se movio anteriormente
						{
							return isValid;
						}
						if(((absDiffI == 2 && absDiffJ == 2) || (absDiffI == 0 && absDiffJ == 2) || (absDiffI == 2 && absDiffJ == 0)) && cont==0){//desde aca hace el mismo proceso que cuando se mueve por primera vez
							isValid = (tablero[coord[2]][coord[3]] != '-')? false: isJumpable(tablero,coord);
							BanderaLugar[0]=coord[2];
							BanderaLugar[1]=coord[3];
							BanderaLugar[2]=cont;
							tablero[coord[0]][coord[1]] = '-';
							tablero[coord[2]][coord[3]] = (colorJugador = ROJO?'R':'N');
							victoria=(colorJugador = ROJO?victoriaRojo():victoriaNegro());
							imprimirTablero();
							if (victoria!=0)
							{
								CrearEstadisticas();
								gtk_widget_destroy(VentanaJuego);
								/*
								 * if victoria=1 gana el rojo
								 * 		ganador=nombre del jugador rojo
								 * 		abrir ventana de victoria
								 * 			avisar que el ganador es el rojo
								 * 	else
								 * 		ganador=nombre del jugador negro
								 * 		abrir ventand de victoria
								 * 			avisar que el ganador es el negro
								 *
								 */
							}
						}
				}
			}
		}while (isValid==true);
    }
    return isValid;
}

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
//
void SetTurn(GtkWidget *event_box, GdkEventButton *event, gpointer data)
{
	char bandera=0;
	if(data==(int)Loc)//Si selecciona Local
	{
		Juego.UserTurn='0';//Si inicia usuario retorna 0
		Juego.MachineTurn='1';//Si incia Maquina retorna 1
	}else if(data==(int)Mac){//Si selecciona que incia maquina
		Juego.UserTurn='1';//User 1
		Juego.MachineTurn='0';//maquina0
		do{
		  pcSiguiente.x = coinFlip(15);
		  pcSiguiente.y = coinFlip(15);
		  pcActual.x = coinFlip(15);
		  pcActual.y = coinFlip(15);
		  if(tablero[pcActual.x][pcActual.y] == Juego.MachineSide)
		  {
			  bandera =  checkJugada(pcActual,pcSiguiente,Juego.MachineTurn);
		  }
		}while(bandera==0);
	}else if(data==(int)Al){//Si selecciona aleaotorio
		srand(time(NULL));
		int ban=(rand()%2);
		if (ban==1)
		{
			Juego.UserTurn='1';
			Juego.MachineTurn='0';
			do{
			  pcSiguiente.x = coinFlip(15);
			  pcSiguiente.y = coinFlip(15);
			  pcActual.x = coinFlip(15);
			  pcActual.y = coinFlip(15);
			  if(tablero[pcActual.x][pcActual.y] == Juego.MachineSide)
			  {
				  bandera =  checkJugada(pcActual,pcSiguiente,Juego.MachineTurn);
			  }
			}while(bandera == 0);
		}else{
			Juego.UserTurn='0';
			Juego.MachineTurn='1';
		}
	}
}

char * nombres()
{
	static char str[700];
	//sprintf (str,FormatoEstadisticas,Juego.username,n);
	return(str);
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
		Juego.UserSide='N';
		printf("h");
		Juego.MachineSide='R';
	}
	else if(data==(int)rusia){
		Juego.UserSide='N';
		Juego.MachineSide='R';
		printf("3");
	}
	else if(data==(int)neutral){
		srand(time(NULL));
		int ban=(rand()%2);
		if (ban==1)
		{
			Juego.UserSide='R';
			Juego.MachineSide='N';
		}else{
			Juego.UserSide='N';
			Juego.MachineSide='R';
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
	    if ((a=fopen(RutaEstadisticas,"r"))==NULL)
	    {
	    	printf("error\n");
	    }else{
	    	for (cont=0;(c=fgetc(a))!=EOF;cont++){}
	    	printf("tamaño del archivo: %d \n",cont-1);
	    	gchar * str = copy_file_to_string(RutaEstadisticas);
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
		gtk_widget_show_all (VentanaSalir);
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

void ClickGrilla (GtkWidget *event_box, GdkEventButton *event, gpointer data)
{
	//falta agregar el boton de cambiar de turno cuando el
	char bandera=0;
	static int contador=0;
	i = (GUINT_FROM_LE(event->y) / 20); // 20 =20 px
	j = (GUINT_FROM_LE(event->x) / 20);
	if (contador==0)
	{
		if((Juego.UserSide)=='N')
		{
			if(tablero[i][j]=='N')
			{
				contador++;
				pcActual.x=i;
				pcActual.y=j;
				gtk_label_set_text(GTK_LABEL(LabeldeControl), " Ficha seleccionada\n elija a donde moverla");
				gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(GridJuego),j,i)),EspacioBlanco);
				imprimirTablero();
			}else{
				gtk_label_set_text(GTK_LABEL(LabeldeControl), ErrorFicha);
			}
		}
		if((Juego.UserSide)=='R')
		{
			if (tablero[i][j]=='R')
			{
				contador++;
				pcActual.x=i;
				pcActual.y=j;
				gtk_label_set_text(GTK_LABEL(LabeldeControl), " Ficha seleccianada\n elija a donde moverla");
				gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(GridJuego),j,i)),EspacioBlanco);
				imprimirTablero();
			}else{
				gtk_label_set_text(GTK_LABEL(LabeldeControl), ErrorFicha);
			}
		}
	}else if (contador==1){
		if((Juego.UserSide)=='N')
		{
			if(tablero[i][j]=='-')
			{
				pcSiguiente.x=i;
				pcSiguiente.y=j;
				if(checkJugada(pcActual,pcSiguiente,Juego.UserSide)==1)
				{
					gtk_label_set_text(GTK_LABEL(LabeldeControl), "movimiento valido");
					gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(GridJuego),j,i)),PuntoNegro);
					imprimirTablero();
				}else{
					gtk_label_set_text(GTK_LABEL(LabeldeControl), ErrorMovimiento);
					contador=0;
				}
			}else{
				gtk_label_set_text(GTK_LABEL(LabeldeControl), ErrorMovimiento);
				contador=0;
			}
		}
		if((Juego.UserSide)=='R')
		{
			if (tablero[i][j]=='-')
			{
				pcSiguiente.x=i;
				pcSiguiente.y=j;
				if(checkJugada(pcActual,pcSiguiente,Juego.UserSide)==1)
				{
					gtk_label_set_text(GTK_LABEL(LabeldeControl), "movimiento valido");
					gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(GridJuego),j,i)),PuntoNegro);
					imprimirTablero();
				}else{
					gtk_label_set_text(GTK_LABEL(LabeldeControl), ErrorMovimiento);
					contador=0;
				}
			}else{
				gtk_label_set_text(GTK_LABEL(LabeldeControl), ErrorMovimiento);
				contador=0;
			}
		}
	}
	do{
	  pcSiguiente.x = coinFlip(15);
	  pcSiguiente.y = coinFlip(15);
	  pcActual.x = coinFlip(15);
	  pcActual.y = coinFlip(15);
	  if(tablero[pcActual.x][pcActual.y] == Juego.MachineSide)
	  {
		  bandera =  checkJugada(pcActual,pcSiguiente,Juego.MachineSide);
	  	  imprimirTablero();
	  }
	}while(bandera == 0);
}

#endif /* FUNCIONES_H_ */
