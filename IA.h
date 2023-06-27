/*
 * IA.h
 *
 *  Created on: 22 jun. 2023
 *      Author: lp1-2023
 */

#ifndef IA_H_
#define IA_H_
#include "Globales.h"
#include "Funciones.h"


void tablerosPuntaje(int colorMaquina) {

    // Rellena el tablero con ceros//edit
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            TPuntajeMaquina[i][j] = 0;
        }
    }

//simepre sea para la pc
    int TPuntajeMaquinaColor0[16][16] = {//edit
            	    {120, 105, 90, 75, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            	    {105, 115, 100, 85, 70, 55, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            	    {90, 100, 110, 95, 80, 65, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            	    {75, 85, 95, 105, 90, 75, 60, 45, 0, 0, 0, 0, 0, 0, 0, 0},
            	    {65, 70, 80, 90, 100, 85, 70, 55, 40, 0, 0, 0, 0, 0, 0, 0},
            	    {0, 60, 65, 75, 85, 95, 80, 65, 50, 35, 0, 0, 0, 0, 0, 0},
            	    {0, 0, 55, 60, 70, 80, 90, 75, 60, 45, 30, 0, 0, 0, 0, 0},
            	    {0, 0, 0, 50, 55, 65, 75, 85, 70, 55, 40, 25, 0, 0, 0, 0},
            	    {0, 0, 0, 0, 45, 50, 60, 70, 80, 65, 50, 35, 20, 0, 0, 0},
            	    {0, 0, 0, 0, 0, 35, 40, 50, 60, 70, 55, 40, 25, 15, 0, 0},
            	    {0, 0, 0, 0, 0, 0, 30, 35, 45, 55, 65, 50, 35, 20, 10, 0},
            	    {0, 0, 0, 0, 0, 0, 0, 25, 30, 40, 50, 60, 45, 30, 15, 5},
            	    {0, 0, 0, 0, 0, 0, 0, 0, 20, 25, 35, 45, 55, 40, 25, 10},
            	    {0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 20, 30, 40, 50, 35, 20},
            	    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 15, 25, 35, 45, 30},
            	    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 10, 20, 30, 40}
            	};
//siempre sea para el usuario
    int TPuntajeMaquinaColor1[16][16] = {//edit
                    {40,  30,  20,  10,  5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
                    {30,  45,  35,  25,  15,  10,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
                    {20,  35,  50,  40,  30,  20,  15,  0,   0,   0,   0,   0,   0,   0,   0,   0},
                    {10,  25,  40,  55,  45,  35,  25,  20,  0,   0,   0,   0,   0,   0,   0,   0},
                    {5,   15,  30,  45,  60,  50,  40,  30,  25,  0,   0,   0,   0,   0,   0,   0},
                    {0,   10,  20,  35,  50,  65,  55,  45,  35,  30,  0,   0,   0,   0,   0,   0},
                    {0,   0,   15,  25,  40,  55,  70,  60,  50,  40,  35,  0,   0,   0,   0,   0},
                    {0,   0,   0,   20,  35,  50,  65,  80,  70,  60,  50,  45,  0,   0,   0,   0},
                    {0,   0,   0,   0,   25,  40,  55,  70,  85,  75,  65,  55,  50,  0,   0,   0},
                    {0,   0,   0,   0,   0,   30,  45,  60,  75,  90,  80,  70,  60,  55,  0,   0},
                    {0,   0,   0,   0,   0,   0,   35,  50,  65,  80,  95,  85,  75,  65,  60,  0},
                    {0,   0,   0,   0,   0,   0,   0,   40,  55,  70,  85,  100, 90,  80,  70,  65},
                    {0,   0,   0,   0,   0,   0,   0,   0,   45,  60,  75,  90,  105, 95,  85,  75},
                    {0,   0,   0,   0,   0,   0,   0,   0,   0,   50,  65,  80,  95,  110, 100, 90},
                    {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   55,  70,  85,  100, 115, 105},
                    {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   60,  75,   90, 105, 120}
                };

    switch (colorMaquina) {
        case 1:
            // Copia los valores al tablero principal
            for (int i = 0; i < 16; i++) {
                for (int j = 0; j < 16; j++) {
                    TPuntajeMaquina[i][j] = TPuntajeMaquinaColor0[i][j];
                    TPuntajeUsuario[i][j] = TPuntajeMaquinaColor1[i][j];
                }
            }
            break;

        case 0:
            // Copia los valores al tablero principal
            for (int i = 0; i < 16; i++) {
                for (int j = 0; j < 16; j++) {
                	TPuntajeMaquina[i][j] = TPuntajeMaquinaColor0[i][j];
                	TPuntajeUsuario[i][j] = TPuntajeMaquinaColor1[i][j];
                }
            }
            break;

    }
}

void generarAdyacentes(salto *jugada){
	coord aux;
	for(int diffx=-1;diffx<2;diffx++){
		for(int diffy=-1;diffy<2;diffy++){

			aux.x=jugada->actual.x+diffx;
			aux.y=jugada->actual.y+diffy;
			if(checkadyacente(jugada->actual,aux)==TRUE){
				if(TPuntajeMaquina[jugada->actual.x][jugada->actual.y]<TPuntajeMaquina[aux.x][aux.y]){
					jugada->ruta[jugada->contRuta].coord[jugada->ruta[jugada->contRuta].contRuta++]=jugada->actual;
					jugada->ruta[jugada->contRuta].coord[jugada->ruta[jugada->contRuta].contRuta++]=aux;
					jugada->contRuta++;
				}
			}
		}
	}
}

void generarSaltos(salto *jugada){
	coord auxInicio =jugada->actual;
	coord auxruta[8];
	char noJumpable=0;
	char banderaUwU =0;
	char primeraVezOwO =1;
	coord mejorCoord=auxInicio;
	do{
		noJumpable=0;
		auxruta[0].x=auxInicio.x -2;auxruta[0].y=auxInicio.y -2;
		auxruta[1].x=auxInicio.x -0;auxruta[1].y=auxInicio.y -2;
		auxruta[2].x=auxInicio.x -2;auxruta[2].y=auxInicio.y -0;

		auxruta[3].x=auxInicio.x +2;auxruta[3].y=auxInicio.y +2;
		auxruta[4].x=auxInicio.x +0;auxruta[4].y=auxInicio.y +2;
		auxruta[5].x=auxInicio.x +2;auxruta[5].y=auxInicio.y +0;

		auxruta[6].x=auxInicio.x -2;auxruta[6].y=auxInicio.y +2;
		auxruta[7].x=auxInicio.x +2;auxruta[7].y=auxInicio.y -2;


		int coordEsquizofrenicas[4];
		for(int i =0;i<8;i++){
			coordEsquizofrenicas[0]=auxInicio.x;
			coordEsquizofrenicas[1]=auxInicio.y;
			coordEsquizofrenicas[2]=auxruta[i].x;
			coordEsquizofrenicas[3]=auxruta[i].y;
			if(isJumpable(tablero,coordEsquizofrenicas)==TRUE){
				if(TPuntajeMaquina[mejorCoord.x][mejorCoord.y]<TPuntajeMaquina[auxruta[i].x][auxruta[i].y]){
					mejorCoord=auxruta[i];
				}else{
					noJumpable++;
				}
			}else{
				noJumpable++;
			}
		}

		if(noJumpable==8){
			break;
		}else{

			banderaUwU =1;
			if (primeraVezOwO==1){
				primeraVezOwO = 0;
				jugada->ruta[jugada->contRuta].coord[jugada->ruta[jugada->contRuta].contRuta++]=jugada->actual;
			}
		}

		jugada->ruta[jugada->contRuta].coord[jugada->ruta[jugada->contRuta].contRuta++]=mejorCoord;
		auxInicio=mejorCoord;

	}while(TRUE);
	if(banderaUwU==1){
		jugada->contRuta++;
	}
}

int predit_salto(char Tfalso[16][16],coord ficha,char turno){
	//colorMaquina
	coord auxInicio =ficha;
	coord auxFinal[8];
	char noJumpable=0;
	char banderaUwU =0;
	char primeraVezOwO =1;
	coord mejorCoord=auxInicio;
	int preditPuntos =0;
	do{
		noJumpable=0;
		auxFinal[0].x=auxInicio.x -2;auxFinal[0].y=auxInicio.y -2;
		auxFinal[1].x=auxInicio.x -0;auxFinal[1].y=auxInicio.y -2;
		auxFinal[2].x=auxInicio.x -2;auxFinal[2].y=auxInicio.y -0;

		auxFinal[3].x=auxInicio.x +2;auxFinal[3].y=auxInicio.y +2;
		auxFinal[4].x=auxInicio.x +0;auxFinal[4].y=auxInicio.y +2;
		auxFinal[5].x=auxInicio.x +2;auxFinal[5].y=auxInicio.y +0;

		auxFinal[6].x=auxInicio.x -2;auxFinal[6].y=auxInicio.y +2;
		auxFinal[7].x=auxInicio.x +2;auxFinal[7].y=auxInicio.y -2;


		int coordEsquizofrenicas[4];
		for(int i =0;i<8;i++){
			coordEsquizofrenicas[0]=auxInicio.x;
			coordEsquizofrenicas[1]=auxInicio.y;
			coordEsquizofrenicas[2]=auxFinal[i].x;
			coordEsquizofrenicas[3]=auxFinal[i].y;
			if(isJumpable(Tfalso,coordEsquizofrenicas)==TRUE){
				if(turno == PC){
					if(TPuntajeMaquina[mejorCoord.x][mejorCoord.y]<TPuntajeMaquina[auxFinal[i].x][auxFinal[i].y]){
						mejorCoord=auxFinal[i];
					}else{
						noJumpable++;
					}

				}else{
					if(TPuntajeUsuario[mejorCoord.x][mejorCoord.y]<TPuntajeUsuario[auxFinal[i].x][auxFinal[i].y]){
						mejorCoord=auxFinal[i];
					}else{
						noJumpable++;
					}
				}
			}else{
				noJumpable++;
			}
		}

		if(noJumpable==8){
			break;
		}else{

			banderaUwU =1;
			if (primeraVezOwO==1){
				primeraVezOwO = 0;
			}
		}
		preditPuntos +=ESCALAR_PREDIT;
		auxInicio=mejorCoord;


	}while(TRUE);
	if(banderaUwU==1){
		return preditPuntos;
	}
	return 0;
}

void generarPuntajes(salto* jugada){
	char auxChar = colorMaquina == BLANCO?'R':'N';
	coord aux;
	for (int ii=0;ii<jugada->contRuta;ii++){
		for(int i=0;i<16;i++){
			for (int j=0;j<16;j++){
				//ficha aliada
				if (jugada->ruta[ii].tableroFalso[i][j]==auxChar){
					jugada->puntaje[ii]+=TPuntajeMaquina[i][j];
					jugada->puntaje[ii]+=(jugada->ruta[ii].contRuta-1)*ESCALAR_SALTOS;

					aux.x=i;
					aux.y=j;
					jugada->puntaje[ii]+= predit_salto(jugada->ruta[ii].tableroFalso,aux, PC);
				}//Ficha mala >:C
				else if (jugada->ruta[ii].tableroFalso[i][j]!='-'){
					jugada->puntaje[ii]-=TPuntajeUsuario[i][j];
					aux.x=i;
					aux.y=j;
					jugada->puntaje[ii]-= predit_salto(jugada->ruta[ii].tableroFalso,aux,PERSONA);

				}
			}
		}
	}
}

void generarTablerosPrueba(salto *jugada){
	char auxChar = colorMaquina == BLANCO?'R':'N';
	for(int uwu=0;uwu<jugada->contRuta;uwu++){
		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 16; j++) {
				jugada->ruta[uwu].tableroFalso[i][j] = tablero[i][j];
			}
		}
	}
	for(int i = 0;i<jugada->contRuta;i++){
		jugada->ruta[i].tableroFalso
		[jugada->ruta[i].coord[0].x]
		[jugada->ruta[i].coord[0].y]
		 = '-';

		jugada->ruta[i].tableroFalso
		[jugada->ruta[i].coord[jugada->ruta[i].contRuta-1].x]
		[jugada->ruta[i].coord[jugada->ruta[i].contRuta-1].y]
		= auxChar;
	}
}

void elegirMejorPuntaje(salto *jugada,char color){
	int mejorPunt=-999999;
	int mejorI =0;
	for(int i=0;i<jugada->contRuta;i++){
		if(jugada->puntaje[i]>mejorPunt){
			mejorPunt=jugada->puntaje[i];
			mejorI=i;
		}
	}
	for(int i=0;i<16;i++){
		for(int j=0;j<16;j++){
			tablero[i][j]=jugada->ruta[mejorI].tableroFalso[i][j];
		}
	}
	printf("Jugada Ejecutada:");
	for(int i=0;i<jugada->ruta[mejorI].contRuta;i++){
		printf("[%d;%d]%c\n",jugada->ruta[mejorI].coord[i].x,jugada->ruta[mejorI].coord[i].y,i<jugada->ruta[mejorI].contRuta-1?',':'\n');
		if (color=='R')
		{
			gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(GridJuego),jugada->ruta[mejorI].coord[i].x,pcSiguiente.x)),PuntoRojo);
		}else if(color=='N'){
			gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(GridJuego),jugada->ruta[mejorI].coord[i].x,pcSiguiente.x)),PuntoNegro);
		}
	}
}

void jugadaPc()
{
	salto jugada;
	jugada.contRuta = 0;
	for(int i=0;i<N;i++){
		jugada.puntaje[i]=0;
		jugada.ruta[i].contRuta=0;
	}
	char auxChar = colorMaquina == BLANCO?'R':'N';
	for(int x = 0;x<16;x++){
		for(int y = 0;y<16;y++){
			if(tablero[x][y]==auxChar){
				jugada.actual.x=x;
				jugada.actual.y=y;
				generarAdyacentes(&jugada);
				generarSaltos(&jugada);
			}
		}
	}
	generarTablerosPrueba(&jugada);
	generarPuntajes(&jugada);
	elegirMejorPuntaje(&jugada,auxChar);
}



#endif /* IA_H_ */
