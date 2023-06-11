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
#define direccion "/home/lp1-2023/eclipse_workspace/Tembojogo/src/interfazHoppitypurete.glade"
#define PuntoNegro "/home/lp1-2023/eclipse_workspace/Tembojogo/src/utilizades/PuntoNegro.png"
#define PuntoRojo "/home/lp1-2023/eclipse_workspace/Tembojogo/src/utilizades/PuntoRojo.png"
#define EspacioBlanco "/home/lp1-2023/eclipse_workspace/Tembojogo/src/utilizades/EspacioBlanco.jpeg"
#define RutaEstadisticas "/home/lp1-2023/eclipse_workspace/Tembojogo/src/Estadisticas"
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

//utilidad
GtkBuilder * builder;
gchar * filename;
gchar	EncabezadoEstadiscas[]={"                                    Estadisticas"};
gchar	StrControlEstadisticas[70];
gint 	i,j;
FILE  * Estadisticas;
gint	victoria=1;
int		BanderaLugar[3]={0,0,0};
char	CadGuardadoStats[100];

char tablero [16][16];

struct config{
	gchar   UserSide;
	gchar 	MachineSide;
	gchar 	mod;
	gchar 	username[20];
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

typedef struct estadisticasJugador
{
	int ganadas;
	int perdidas;
	int totales;
}StructEstadisticas;

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



#endif /* GLOBALES_H_ */
