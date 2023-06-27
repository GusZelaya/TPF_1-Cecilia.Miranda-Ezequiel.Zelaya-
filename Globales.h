/*
 * Globales.h
 *
 *  Created on: 10 jun. 2023
 *      Author: lp1-2023
 */

#ifndef GLOBALES_H_
#define GLOBALES_H_

//librerias
#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

//defines chetos

#define direccion "src/UwU.glade"
#define PuntoNegro "src/utilidades/Juego/PuntoNegro.png"
#define PuntoRojo "src/utilidades/Juego/PuntoRojo.png"
#define EspacioBlanco "src/utilidades/Juego/EspacioBlanco.png"
#define RutaEstadisticas "src/Estadisticas"
#define RutaEstadisticas2 "src/Estadisticasfake"
#define salir 96
#define inicioabando1 0
#define inicioabando2 12
#define bandoajuego 1
#define bandoainicio 2
#define juegoabando 3
#define inicioastats 4
#define inicioaayuda 5
#define ayudaainicio 6
#define ayudajuego 222
#define repoabando 7
#define selecrepo 8
#define repoavisitante 9
#define neutral 00
#define rusia 88
#define usa 99
#define pVm 1
#define mVm 0
#define ErrorFicha  "Selecciona una ficha de tu equipo"
#define ErrorMovimiento "Movimiento seleccionado inválido"
#define FormatoEstadisticas "_%s/%d/%d/%d"//nombre, jugadas, ganadas, perdidas
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
#define BLANCO 1
#define PERSONA 1
#define PC 0
#define N 500
#define M 100
#define statsainicio 10
#define MEN 55

#define ESCALAR_SALTOS 100
#define ESCALAR_PREDIT 50

//utilidad//
GtkBuilder * builder;
gchar * filename;
gchar * RepositorioCompartidoConfig;
gchar	EncabezadoEstadiscas[]={"                                    Estadisticas"};
gchar	StrControlEstadisticas[70];

gint 	i,j;
FILE  *	archivoConfiguracion=NULL;
FILE  * archivoJugadas=NULL;
FILE  * Estadisticas=NULL;
gint	victoria=1;
char 	turnoActual;
int		colorMaquina;
int		colorJugador;
int		BanderaLugar[3]={0,0,0};
char	CadGuardadoStats[100];
char primeritaVez;
char tablero [16][16];
int TPuntajeMaquina[16][16];
int TPuntajeUsuario[16][16];

struct config{
	gchar   UserSide;
	gchar 	MachineSide;
	gchar 	mod;
	gchar 	username[20];
	gchar	machinename[20];
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

typedef struct aaa{
	coord locuraGuardar[100];
	unsigned int locuraLongitud;
}aaa;

aaa LOCURA;

typedef struct estadisticasJugador
{
	int ganadas;
	int perdidas;
	int totales;
	char name[19];
}StructEstadisticas;



StructEstadisticas GuardadoStats;

typedef struct string{
	char* array;
	unsigned int charsTotales;
	unsigned int charsUsados;
}string;

typedef struct siguiente{
	coord coord[M];
	char tableroFalso[16][16];
	int contRuta;

}siguiente;

typedef struct jugada{
	coord actual;
	siguiente ruta[N];
	int puntaje[N];
	int contRuta;

}salto;


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
GtkWidget * SALIR;

//widgets de salir
GtkWidget * sii;//Edit
GtkWidget * noo;//Edit

//widgets de VentaJuego
GtkWidget * VentanaJuego;
GtkWidget * JuegoAtras;
GtkWidget * LabeldeControl;
GtkWidget * NOMBREJUGADOR;
GtkWidget * NOMBREJUGADOR2;
GtkWidget * PUNTOSPLAYER;
GtkWidget * PUNTOSMAQUINA;
GtkWidget * GridJuego;
GtkWidget * EventBox;
GtkWidget * VentanaSalir;
GtkWidget * Juegoayuda;
GtkWidget * JuegoLabelTurno;
GtkWidget * JuegoEnter;
GtkWidget * TURNO;

//widgets de ventanajuegomaquina
GtkWidget * VentanaJuegoMaquina;
GtkWidget * JuegoAtras1;
GtkWidget * LabeldeControl1;
GtkWidget * NOMBREJUGADOR1;
GtkWidget * NOMBREJUGADOR21;
GtkWidget * PUNTOSPLAYER1;
GtkWidget * PUNTOSMAQUINA1;
GtkWidget * GridJuego1;
GtkWidget * EventBox1;
GtkWidget * VentanaSalir1;
GtkWidget * Juegoayuda1;
GtkWidget * JuegoLabelTurno1;
GtkWidget * JuegoEnter1;
GtkWidget * TURNO1;
GtkWidget * TABLERO1;


//widgets de VentanaStats
GtkWidget * VentanaStats;
GtkWidget * ChooserStats;
GtkWidget * BotonStats;
GtkWidget * TextoStats;

//widgets de VentanaBusquedaPartida
GtkWidget * VentanaBusquedaPartida;
GtkWidget * BotonBusquedaPartida;
GtkWidget * BotonOkBusquedaPartida;

//widgets de VentanaVisitante
GtkWidget * VentanaVisitante;
GtkWidget * EntryVisitante;
GtkWidget * BotonOkVisitante;

//widgets de VentanaMvM
GtkWidget * VentanaMvM;
GtkWidget * MvMLocal;
GtkWidget * MvMVisitante;

//widgets de VentanaVictoria
GtkWidget * VentanaVictoria;
GtkWidget * MENU;
GtkWidget * LabelVictoria;



//widgets imagenes

//Victoria

GtkWidget * FONDOVICTORIA;
GtkWidget * BACKWIN;


//inicio
GtkWidget * PLAYERVSPC;
GtkWidget * PCVSPC;
GtkWidget * STATS;
GtkWidget * HELPINICIO;
GtkWidget * HOPPITY;
GtkWidget * COLDWAR;
GtkWidget * FONDOINICIO;
GtkWidget * sal;

//Bando
GtkWidget * FONDOBANDO;
GtkWidget * BACKBANDO;
GtkWidget * RANDOM1;
GtkWidget * RANDOM2;
GtkWidget * START;
GtkWidget * USA;
GtkWidget * URRS;
GtkWidget * PCJUEGO;
GtkWidget * PLAYER;
GtkWidget * PLAYERNAME;
GtkWidget * CHOSESIDE;
GtkWidget * INICIO;

//Juego
GtkWidget * BACKJUEGO;
GtkWidget * HELPJUEGO;
GtkWidget * PLAYER1;
GtkWidget * PLAYER2;
GtkWidget * TABLERO;
GtkWidget * FICHAUSA;
GtkWidget * FICHAURRS;

//salir
GtkWidget * SI;
GtkWidget * NO;
GtkWidget * SEGURO;

//victoria
GtkWidget * VentanaVictoria;
GtkWidget * BACKWIN;


#endif /* GLOBALES_H_ */
