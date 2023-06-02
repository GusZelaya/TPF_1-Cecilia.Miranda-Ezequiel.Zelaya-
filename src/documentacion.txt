# TPF_1-Cecilia.Miranda-Ezequiel.Zelaya-
struct config: Configuracion que ingresa el usuario en la partida.

typedef struct config datosJuego: Carga los datos del juego.

typedef struct coord: COnfigura las coordenadas de la ficha del usuario.

char* copy_file_to_string(const char* filename):Copia contenido del archivo dentro de una cadena. 
-Obtine el tamaño del archivo
-Crea una cadena del tamaño adecuado
-Lee los caracteres del archivo y copia en la cadena
-Agrega el terminador de cadena al final

void cleanBuffer:Funcion que limpia el buffer.

void tableroInicial():Imprime en tablero en la terminar para chequeo.

void SetTurn(GtkWidget event_box, GdkEventButton *event, gpointer data): Setea el turno.
-Si se selecciona Local
-Si se selecciona Maquina
-Random si se selecciona aleatorio

void SetMode (int data):Selecciona el modo de juego Persona vs Maquina.

void SetSide(GtkWidget *event_box, GdkEventButton *event, gpointer data):Selecciona el bando que juega.
-Si el usuario juega con Negro
-Si el usuario juega con Rojas
-Si se determina aleatoriamente 

void guardar(GtkFileChooserButton *button, gpointer user_data):Imprime el archivo seleccionado en el GTKText.

void CambiarVen (GtkWidget *event_box, GdkEventButton *event, gpointer data):Funcion de inciar juego en caso de Jugador vs Maquina.

void guardar_texto():Obtiene el contenido del campo de entrada (Nombre del jugador).

void ClickGrilla (GtkWidget *event_box, GdkEventButton *event, gpointer data):Funcion utilizada para identifica la coordenada clickea dentro del tablero.

void imprimirTablero():Imprime el tablero para control.

int victoriaRojo():Condicion de victoria Rojo.

int victoriaNegro():Condicion de victoria Negro.

int checkJugada(coord pcActual,coord pcSiguiente,int turno,int colorJugador):Funcion que verifica las jugadas.
-No se puede seleccionar casillas vacias 
-Si quiere mover la pieza a una casilla adyacente
-Si quiere realizar un salto
 -Si realiza un segundo salto

int isJumpable(char tablero[16][16],int coord[4]):Funcion de condicion de salto.

int coinFlip( int range):Seleccion de movimiento aleatorio para la maquina.

int main (int argc, char *argv[]):Iniciador de juego.
-Asignacion de widges para ventanas
-Asignacion de widges para botones
-Asignacion de widges para labels
-Asignacion de callbacks
-Asignacion de get signals


 

 

