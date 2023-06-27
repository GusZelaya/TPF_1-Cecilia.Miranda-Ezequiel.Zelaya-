/*
 * Funciones.h
 *
 *  Created on: 10 jun. 2023
 *      Author: lp1-2023
 */

#ifndef FUNCIONES_H_
#define FUNCIONES_H_
#include "Globales.h"
#include "IA.h"

//void GuardarNombre(GtkWidget *event_box, Gdklabel *event, gpointer data)
//funcion para copiar el contenido de un archivo dentro de una cadena
//
void CambiarVenVisitante(GtkWidget *event_box, GdkEventButton *event, gpointer data)
{
	gtk_widget_destroy (VentanaMvM);
	gtk_widget_show_all (VentanaBusquedaPartida);

}

void ComprobarArchConfig()
{
	FILE * a;
	char c;
	if((a=fopen(RepositorioCompartidoConfig,"r"))==NULL)//cambiar por el nombre del archivo de configuracion
	{
		gtk_label_set_text (GTK_LABEL(LabeldeControl),"ERROR AL SELECCIONAR EL ARCHIVO DE JUEGO \n CONFIGURACIONES DE PARTIDA NO EXISTE \n NECESARIO REINICIAR JUEGO");
		gtk_widget_show_all (VentanaJuego);
		return;
	}
	for (int cont=0;(c=fgetc(a))!=',';cont++)
	{
		Juego.username[cont]=c;
	}
	for (int cont=0;(c=fgetc(a))!=',';cont++)
	{
		if(c!='N' && c!='R')
		{
			gtk_label_set_text (GTK_LABEL(LabeldeControl),"ERROR AL SELECCIONAR EL ARCHIVO DE JUEGO \n CONFIGURACIONES DE PARTIDA COLOR DEL JUGADOR \n NECESARIO REINICIAR JUEGO");
			gtk_widget_show_all (VentanaJuego);
			return;
		}
		Juego.UserSide=c;
		if (Juego.UserSide=='N')
		{
			Juego.MachineSide='R';
		}else{
			Juego.MachineSide='N';
		}
	}

}

void guardar_texto()
{
    // Obtener el contenido del campo de entrada
	strncpy(Juego.username, gtk_entry_get_text(GTK_ENTRY(PlayerName)), 19);
	gtk_label_set_text(GTK_LABEL(NOMBREJUGADOR), Juego.username);
	return;
}

void guardar_nombre2()
{
	strncpy(Juego.machinename, gtk_entry_get_text(GTK_ENTRY(EntryVisitante)), 19);
	gtk_label_set_text(GTK_LABEL(NOMBREJUGADOR), Juego.machinename);
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
      return 2;
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
    if (coord[0]<0||coord[1]<0||coord[2]<0||coord[3]<0 || coord[0]>16||coord[1]>16||coord[2]>16||coord[3]>16)
    	    return false;
    else{
    	int puntMedioI = (coord[2]+coord[0])/2;
		int puntoMedioJ = (coord[3]+coord[1])/2;
		if(
			(tablero[puntMedioI][puntoMedioJ])!='-' &&
			tablero[coord[2]][coord[3]] == '-' &&
			(abs(coord[2]-coord[0])==2 ||abs(coord[2]-coord[0])==0) &&
			(abs(coord[3]-coord[1])==2||abs(coord[3]-coord[1])==0)
			)
		{
			return (true);
		}
		else
		{
			return (false);
		}
    }
}



int checkadyacente(coord pcActual,coord pcSiguiente){

    int coord[4] = {pcActual.x,pcActual.y,pcSiguiente.x,pcSiguiente.y};
    if (coord[0]<0||coord[1]<0||coord[2]<0||coord[3]<0 || coord[0]>16||coord[1]>16||coord[2]>16||coord[3]>16)
    	return false;

    bool isValid = false;
    int absDiffI = abs(coord[0]-coord[2]);
    int absDiffJ = abs(coord[1]-coord[3]);
    //No se puede seleccionar una pieza vacia
    if(tablero[coord[0]][coord[1]] == '-' ||( coord[0] == coord[2] && coord[1] == coord[3])){
        return false;
    }

    if(absDiffI <= 1 && absDiffJ <= 1){
        isValid = (tablero[coord[2]][coord[3]] == '-')? true: false;
    }
    return isValid;
}

int checkSalto (coord pcActual, coord pcSiguiente){
	int coord[4] = {pcActual.x,pcActual.y,pcSiguiente.x,pcSiguiente.y};
	bool isValid = false;
	int absDiffI = abs(coord[0]-coord[2]);
	int absDiffJ = abs(coord[1]-coord[3]);
	//No se puede seleccionar una pieza vacia
	if(tablero[coord[0]][coord[1]] == '-' && coord[0] == coord[2] && coord[1] == coord[3]){
	    return false;
	}
	if((absDiffI == 2 && absDiffJ == 2) || (absDiffI == 0 && absDiffJ == 2) || (absDiffI == 2 && absDiffJ == 0) ){
		isValid = (tablero[coord[2]][coord[3]] != '-')? false: isJumpable(tablero,coord);
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
	if(data==(int)Loc)//Si selecciona Local
	{
		Juego.UserTurn=0;//Si inicia usuario retorna 0
		Juego.MachineTurn=1;//Si incia Maquina retorna 1
	}else if(data==(int)Mac){//Si selecciona que incia maquina
		Juego.UserTurn=1;//User 1
		Juego.MachineTurn=0;//maquina0
	}else if(data==(int)Al){//Si selecciona aleaotorio
		srand(time(NULL));
		int ban=(rand()%2);
		if (ban==1)
		{
			Juego.UserTurn=1;
			Juego.MachineTurn=0;
		}else{
			Juego.UserTurn=0;
			Juego.MachineTurn=1;
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

void SetSide(GtkWidget *event_box, GdkEventButton *event, gpointer data)
{
	if((int)data==((int)usa))
	{
		Juego.UserSide='N';
		colorJugador=NEGRO;
		printf("h");
		Juego.MachineSide='R';
		colorMaquina=BLANCO;
		printf("MEODIO\n");
	}
	else if((int)data==(int)rusia){
		Juego.UserSide='R';
		colorJugador=BLANCO;
		Juego.MachineSide='N';
		colorMaquina=NEGRO;
		printf("FDSAMIKIMEADSINOFNASIOSFNOIIOSFNOIAS");
	}
	else if((int)data==(int)neutral){
		srand(time(NULL));
		int ban=(rand()%2);
		if (ban==1)
		{
			Juego.UserSide='R';
			colorJugador=BLANCO;
			Juego.MachineSide='N';
			colorMaquina=NEGRO;
			printf("MEODIO2");
		}else{
			Juego.UserSide='N';
			colorJugador=NEGRO;
			Juego.MachineSide='R';
			colorMaquina=BLANCO;
			printf("MEODIO3");
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

void BuscarPartida(GtkFileChooserButton *button, gpointer user_data)
{
    GtkFileChooser *file_chooser = GTK_FILE_CHOOSER(button);
    // Obtener la dirección del archivo seleccionado
    RepositorioCompartidoConfig = gtk_file_chooser_get_filename(file_chooser);
    //vuelve a la pantalla anterior
    g_print("repositorio compartido: %s \n",RepositorioCompartidoConfig);
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
	primeritaVez = 1;
	LOCURA.locuraLongitud=0;
	switch((int)data)
	{
	case(salir):
		gtk_widget_destroy (VentanaInicio);
		break;

	case(inicioabando1):
	// Mostramos ventanas y escondemos otras
	    gtk_widget_hide (VentanaInicio);
		SetMode(pVm);
	    gtk_widget_show_all (VentanaBando);
	    break;
	case(inicioabando2):
		gtk_widget_destroy (VentanaInicio);
		SetMode(mVm);
		gtk_widget_show_all (VentanaMvM);
		break;
	case(bandoajuego):
		gtk_widget_hide (VentanaBando);
		guardar_texto();
		gtk_label_set_text(GTK_LABEL(TURNO),(Juego.UserTurn)==0?"TURNO P":"TURNO M");
		turnoActual=(Juego.UserTurn)==0?'P':'M';
		tablerosPuntaje(colorMaquina);
		relacionHoppityTablero();
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
	case(ayudajuego):
		gtk_widget_hide (VentanaAyuda);
		gtk_widget_show_all (VentanaJuego);
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
	case(selecrepo):
		gtk_widget_destroy(VentanaMvM);
		gtk_widget_show_all(VentanaBusquedaPartida);
		break;
	case(repoavisitante):
		gtk_widget_destroy(VentanaBusquedaPartida);
		ComprobarArchConfig();
		gtk_widget_show_all (VentanaVisitante);
		break;
	case(statsainicio):
		gtk_widget_destroy(VentanaStats);
		gtk_widget_show_all(VentanaInicio);
		break;
	}
}

int checkJugada()
{
	if((checkadyacente(LOCURA.locuraGuardar[0],LOCURA.locuraGuardar[1]))==1 && LOCURA.locuraLongitud==2)
	{
		tablero[LOCURA.locuraGuardar[0].x][LOCURA.locuraGuardar[0].y]=Juego.UserSide;
		if(Juego.UserSide=='N')
		{
			gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(GridJuego),LOCURA.locuraGuardar[1].y,LOCURA.locuraGuardar[1].x)),PuntoNegro);
		}else{
			gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(GridJuego),LOCURA.locuraGuardar[1].y,LOCURA.locuraGuardar[1].x)),PuntoRojo);
		}
		return 1;
	}
	else if((isJumpableModificado())==1)
	{
		tablero[LOCURA.locuraGuardar[0].x][LOCURA.locuraGuardar[0].y]=Juego.UserSide;
		if(Juego.UserSide=='N')
		{
			gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(GridJuego),LOCURA.locuraGuardar[LOCURA.locuraLongitud-1].y,LOCURA.locuraGuardar[LOCURA.locuraLongitud-1].x)),PuntoNegro);
		}else{
			gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(GridJuego),LOCURA.locuraGuardar[LOCURA.locuraLongitud-1].y,LOCURA.locuraGuardar[LOCURA.locuraLongitud-1].x)),PuntoRojo);
		}
		return 0;
	}
	return 666;
}

int checkFicha()
{
	if((Juego.UserSide)=='N')
	{
		if(tablero[pcActual.x][pcActual.y]=='N')
		{
			gtk_label_set_text(GTK_LABEL(LabeldeControl), " Ficha seleccionada\n elija a donde moverla");
			gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(GridJuego),j,i)),EspacioBlanco);
			return 1;
		}else{
			gtk_label_set_text(GTK_LABEL(LabeldeControl), ErrorFicha);
		}
	}
	if((Juego.UserSide)=='R')
	{
		if (tablero[i][j]=='R')
		{
//			contador++;
			pcActual.x=i;
			pcActual.y=j;
			gtk_label_set_text(GTK_LABEL(LabeldeControl), " Ficha seleccianada\n elija a donde moverla");
			gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(GridJuego),j,i)),EspacioBlanco);
			return 1;
		}else{
			gtk_label_set_text(GTK_LABEL(LabeldeControl), ErrorFicha);
		}
	}
	return 99;
}

int isJumpableModificado()
{
	int coord[4];
	int result;
	for(int i =1;i<LOCURA.locuraLongitud;i++){

		coord[0]=LOCURA.locuraGuardar[i-1].x;
		coord[1]=LOCURA.locuraGuardar[i-1].y;
		coord[2]=LOCURA.locuraGuardar[i].x;
		coord[3]=LOCURA.locuraGuardar[i].y;


		result=isJumpable(tablero,coord);
		if(result == FALSE){
			return FALSE;
		}

	}
	return TRUE;
}

int validar()
{
	if(checkFicha()==1 && checkJugada()==1)
		return 1;
	else{
		gtk_label_set_text(GTK_LABEL(LabeldeControl), "Movimiento invalido, seleccione un movimientos valido");
		return 0;
	}

}

void ClickGrilla (GtkWidget *event_box, GdkEventButton *event, gpointer data)
{
	i = (GUINT_FROM_LE(event->y)/54); // 54 pixeles por cuadrito del tablero
	j = (GUINT_FROM_LE(event->x)/54);
	pcActual.x=i-1;
	pcActual.y=j;

	LOCURA.locuraGuardar[LOCURA.locuraLongitud++]=pcActual;
}


void verificarVictoria(){

	if(victoriaRojo() == 2){
		gtk_label_set_text(GTK_LABEL(LabelVictoria), "Gano USA y perdio URSS\npero siempre gana el amor");
		gtk_widget_destroy (VentanaJuego);
		gtk_widget_destroy(VentanaInicio);
		gtk_widget_show (VentanaVictoria);
		gtk_widget_destroy (VentanaJuego);
		gtk_widget_destroy(VentanaInicio);

	}else if(victoriaNegro() == 1){
		gtk_label_set_text(GTK_LABEL(LabelVictoria), "Gano URSS y perdio USA\npero siempre gana el amor");
		gtk_widget_destroy (VentanaJuego);
		gtk_widget_destroy(VentanaInicio);
		gtk_widget_show (VentanaVictoria);
		gtk_widget_destroy (VentanaJuego);
		gtk_widget_hide(VentanaInicio);
	}
}

void relacionHoppityTablero(){

	for(int i=0;i<16;i++){
		for(int j=0;j<16;j++){
			if(Juego.UserSide=='R'){
				if(tablero[i][j]=='R')
					gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(GridJuego),j,i+1)), PuntoRojo);
				else if (tablero[i][j]=='N')
					gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(GridJuego),j,i+1)), PuntoNegro);
				else
					gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(GridJuego),j,i+1)),EspacioBlanco);
			}else{
				if(tablero[i][j]=='R')
					gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(GridJuego),j,i+1)), PuntoNegro);
				else if (tablero[i][j]=='N')
					gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(GridJuego),j,i+1)), PuntoRojo);
				else
					gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(GridJuego),j,i+1)),EspacioBlanco);
			}

		}
	}
	for(int i=0;i<16;i++){
			gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(GridJuego),i,0)),EspacioBlanco);
		}
	verificarVictoria();
}


void limpiarLocura(){
	for(int i=0;i<100;i++){
		LOCURA.locuraGuardar[i].x=0;
		LOCURA.locuraGuardar[i].y=0;
	}
	LOCURA.locuraLongitud=0;
}


void meOdio(){

	tablero[LOCURA.locuraGuardar[0].x][LOCURA.locuraGuardar[0].y] = '-';
	tablero[LOCURA.locuraGuardar[LOCURA.locuraLongitud-1].x][LOCURA.locuraGuardar[LOCURA.locuraLongitud-1].y] = (colorJugador = BLANCO?'R':'N');
	victoria=(colorJugador = BLANCO?victoriaRojo():victoriaNegro());

	imprimirTablero();
	turnoActual='M';
}




void BotonEnter(GtkFileChooserButton *button, gpointer user_data)
{

	if(turnoActual == 'P'){
		if(LOCURA.locuraLongitud<=1){
			limpiarLocura();
			relacionHoppityTablero();
			gtk_label_set_text(GTK_LABEL(LabeldeControl), ErrorMovimiento);
			gtk_label_set_text(GTK_LABEL(TURNO),(turnoActual=='P')?"TURNO P":"TURNO M");
			victoria=(colorMaquina = BLANCO?victoriaRojo():victoriaNegro());
			return;
		}
		if(checkadyacente(LOCURA.locuraGuardar[0],LOCURA.locuraGuardar[1]) && LOCURA.locuraLongitud==2){

			meOdio();
			limpiarLocura();
			relacionHoppityTablero();
			gtk_label_set_text(GTK_LABEL(LabeldeControl), "Presione enter para que juegue la maquina");
			gtk_label_set_text(GTK_LABEL(TURNO),(turnoActual=='P')?"TURNO P":"TURNO M");
			victoria=(colorMaquina = BLANCO?victoriaRojo():victoriaNegro());
			return;
		}else{
			for(int i=1;i<LOCURA.locuraLongitud;i++){
				if(checkSalto(LOCURA.locuraGuardar[i-1],LOCURA.locuraGuardar[i])==0){
					limpiarLocura();
					relacionHoppityTablero();
					gtk_label_set_text(GTK_LABEL(LabeldeControl), ErrorMovimiento);
					gtk_label_set_text(GTK_LABEL(TURNO),(turnoActual=='P')?"TURNO P":"TURNO M");
					victoria=(colorMaquina = BLANCO?victoriaRojo():victoriaNegro());
					return;
				}
			}
			meOdio();
			limpiarLocura();
			relacionHoppityTablero();
			gtk_label_set_text(GTK_LABEL(TURNO),(turnoActual=='P')?"TURNO P":"TURNO M");
			victoria=(colorMaquina = BLANCO?victoriaRojo():victoriaNegro());
		}
	}else{
		if(Juego.UserSide == 'N' && primeritaVez==1){
			primeritaVez=0;
			colorMaquina = !colorMaquina;
		}
		printf("Juega la maquina con el color %s\n",colorJugador == NEGRO?"Blanco":"Negro");
		jugadaPc();
		victoria=(colorMaquina = BLANCO?victoriaRojo():victoriaNegro());
		imprimirTablero();
		relacionHoppityTablero();
		limpiarLocura();
		gtk_label_set_text(GTK_LABEL(LabeldeControl), "Seleccione una ficha");
		turnoActual='P';
		gtk_label_set_text(GTK_LABEL(TURNO),(turnoActual=='P')?"TURNO P":"TURNO M");
		victoria=(colorMaquina = BLANCO?victoriaRojo():victoriaNegro());
	}



}

#endif /* FUNCIONES_H_ */
