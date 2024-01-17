#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define SIZE 4  // Tamanio del tablero

struct fecha{
    int dia;
    int mes;
    int anio;
};
struct jugador{
    char alias[10];
    long documento;
    char nombre[20];
    char apellido[30];
    char localidad[30];
    bool activo;
    fecha nacimiento;
};
struct jugadores{
	jugador arr_jugadores[10];
	int tope;
};
struct partida{
    fecha fecha_partida;
    jugador jugador_partida;
    bool abortada;
    int puntaje_partida;
};

struct partidas{
    partida arr_partida[50];
	int tope;
};
 
bool comparar(char nom1[10], char nom2[10]) {
    int i = 0;
    while (i < 10 && nom1[i] != '\0' && nom2[i] != '\0' && nom1[i] == nom2[i]) {
        i++;
    }
    if (nom1[i] == '\0' && nom2[i] == '\0') {
        return true;
    } else {
        return false;
    }
}

void alta_usuario(jugadores &jugador) {
    
    printf("Ingrese el alias: \n");
    scanf("%s", jugador.arr_jugadores[jugador.tope].alias);
    
    // Verificar si el alias ya existe
    for (int i = 0; i < jugador.tope; i++) {
        if (comparar(jugador.arr_jugadores[i].alias, jugador.arr_jugadores[jugador.tope].alias) == true) {
            printf("El alias ya existe.\n");
            return;
        }
    }
    printf("Ingrese documento: \n");
    scanf("%ld", &jugador.arr_jugadores[jugador.tope].documento);
    printf("Ingrese apellido: \n");
    scanf("%s", jugador.arr_jugadores[jugador.tope].apellido);
    printf("Ingrese localidad: \n");
    scanf("%s", jugador.arr_jugadores[jugador.tope].localidad);
    printf("Ingrese fecha de nacimiento: \n");
    scanf("%d %d %d", &jugador.arr_jugadores[jugador.tope].nacimiento.dia, &jugador.arr_jugadores[jugador.tope].nacimiento.mes, &jugador.arr_jugadores[jugador.tope].nacimiento.anio);
    jugador.arr_jugadores[jugador.tope].activo = true;
    jugador.tope++;
}


void baja_usuario(jugadores &jugador) {
    printf("Ingrese el alias: \n");
    char jugador_bajar[10];
    scanf("%s", jugador_bajar);
    
    for (int i = 0; i < jugador.tope; i++) {
        if (comparar(jugador.arr_jugadores[i].alias, jugador_bajar)) {
            if (jugador.arr_jugadores[i].activo == true) {
                jugador.arr_jugadores[i].activo = false;
                printf("El usuario con alias %s ha sido dado de baja.\n", jugador_bajar);
                return;
            } else {
                jugador.arr_jugadores[i].activo = true;
                printf("El usuario con alias %s esta activo nuevamente.\n", jugador_bajar);
                return;
            }
        }
    }
    
    printf("No se encontro ningun usuario con el alias %s.\n", jugador_bajar);
    
}
void modificar_usuario(jugadores &jugador) {
    printf("Ingrese el alias del usuario que desea modificar: \n");
    char alias_modificar[10];
    scanf("%s", alias_modificar);
    
    for (int i = 0; i < jugador.tope; i++) {
        if (comparar(jugador.arr_jugadores[i].alias, alias_modificar)) { 
            if (jugador.arr_jugadores[i].activo == true) {
                printf("Datos actuales:\n");
                printf("Alias: %s\n", jugador.arr_jugadores[i].alias);
                printf("Documento: %ld\n", jugador.arr_jugadores[i].documento);
                printf("Apellido: %s\n", jugador.arr_jugadores[i].apellido);
                printf("Localidad: %s\n", jugador.arr_jugadores[i].localidad);
                printf("Fecha de nacimiento: %d/%d/%d\n", jugador.arr_jugadores[i].nacimiento.dia, jugador.arr_jugadores[i].nacimiento.mes, jugador.arr_jugadores[i].nacimiento.anio);
                
                printf("Ingrese la nueva localidad: \n");
                scanf("%s", jugador.arr_jugadores[i].localidad);
                
                printf("El usuario con alias %s ha sido modificado.\n", alias_modificar);
                return;
            } else {
                printf("El usuario con alias %s esta inactivo. No se puede modificar.\n", alias_modificar);
                return;
            }
        }
    }
    
    printf("No se encontro ningun usuario con el alias %s.\n", alias_modificar);
}
int menor( char nom1[10], char nom2[10]){
	int i = 0;
	int result = 0;
	while((nom1[i] != '\0') && (nom2[i] != '\0') && (result == 0)){
		if(nom1[i] < nom2[i]){
			result = -1;
		}else if(nom1[i] > nom2[i]){
			result = 1;
		     }else{
		   	   i++;
		   	}

	}
	return result;	
}
void Ordenado_por_Alias(jugadores &players){
    int i = 0;
    int j = 0;
    jugador temp;
    for (i = 0; i < players.tope - 1; i++) {
        for (j = 0; j < players.tope - 1; j++) {
            if (menor(players.arr_jugadores[j].alias,players.arr_jugadores[j+1].alias) == 1){
                temp = players.arr_jugadores[j];
                players.arr_jugadores[j] = players.arr_jugadores[j+1];
                players.arr_jugadores[j+1] = temp;
            }
        }
    }
}

void listar_usuarios(jugadores jugador){
	printf("Los jugadores activos son: \n");
	int i=0;
	Ordenado_por_Alias(jugador);
	while (i < jugador.tope){
	   
	  if (jugador.arr_jugadores[i].activo==true){
	  	printf("\nAlias : %s",jugador.arr_jugadores[i].alias);
	  	printf("\ndocumento: %ld",jugador.arr_jugadores[i].documento);
	  	printf("\nApellido: %s",jugador.arr_jugadores[i].apellido);
	  	printf("\nLocalidad: %s",jugador.arr_jugadores[i].localidad);
	  	printf("\nFecha de nacimiento: %d %d %d",jugador.arr_jugadores[i].nacimiento.dia,
		jugador.arr_jugadores[i].nacimiento.mes,jugador.arr_jugadores[i].nacimiento.anio);
	    }
		i++;  
	} 
    
}

int tablero[SIZE][SIZE] = {0};  // Inicializar todas las celdas en 0
int puntaje = 0;                // Variable para almacenar el puntaje
bool gano = false;
void print_tablero() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d\t", tablero[i][j]);   // Imprimir el valor de cada celda
        }
        printf("\n");
    }
}

void aniadir_random() {
    int x, y;
    do {
        x = rand() % SIZE;                  // Generar una fila aleatoria
        y = rand() % SIZE;                  // Generar una columna aleatoria
    } while (tablero[x][y] != 0);           // Repetir si la celda no está vacía

         tablero[x][y] = (rand() % 2 + 1) * 2;    // Generar un número aleatorio (2 o 4) con mayor probabilidad de ser 2
        
}

bool buscar2048(int tablero[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (tablero[i][j] == 2048 ) {
                return true; 
            }
        }
    }
    return false; 
}

bool poder_mover() {
    if (buscar2048(tablero)) {
        gano = true;
        print_tablero(); 
        printf("Puntaje final: %d\n", puntaje);
        printf("Ganaste!\n");
        return false;
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (tablero[i][j] == 0) {
                return true;
            }
            if (i < SIZE - 1 && tablero[i][j] == tablero[i + 1][j]) {
                return true;
            }
            if (j < SIZE - 1 && tablero[i][j] == tablero[i][j + 1]) {
                return true;
            }
        }
    }
    return false;
}
bool puede_mover_izq() {  	//i filas, j columnas
    for (int i = 0; i < SIZE; i++) {
        for (int j = 1; j < SIZE; j++) {
            if (tablero[i][j] == tablero[i][j - 1] && tablero[i][j - 1] != 0 ) {
                return true;
            }
            if (tablero[i][j - 1] == 0  &&  tablero[i][j] != 0)
            {
                return true;
            }
            
        }
    }
    return false;
}
void mover_izq() {
    for (int i = 0; i < SIZE; i++) {
        int k = 0;
        for (int j = 1; j < SIZE; j++) {
            if (tablero[i][j] != 0) {
                if (tablero[i][k] == 0) {
                    tablero[i][k] = tablero[i][j];
                    tablero[i][j] = 0;
                } else if (tablero[i][k] == tablero[i][j]) {
                    tablero[i][k] *= 2;
                    puntaje += tablero[i][k];  // Incrementar el puntaje al combinar números
                    tablero[i][j] = 0;
                    k++;
                } else {
                    k++;
                    tablero[i][k] = tablero[i][j];
                    if (j != k) {
                        tablero[i][j] = 0;
                    }
                }
            }
        }
    }
}

bool puede_mover_der() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE - 1; j++) {
            if (tablero[i][j] == tablero[i][j + 1] && tablero[i][j + 1] != 0  ) {
                return true;
            }
            if ( tablero[i][j + 1] == 0 &&  tablero[i][j] != 0)
            {
                return true;
            }
            
        }
    }
    return false;
}
void mover_der() {
    for (int i = 0; i < SIZE; i++) {
        int k = SIZE - 1;
        for (int j = SIZE - 2; j >= 0; j--) {
            if (tablero[i][j] != 0) {
                if (tablero[i][k] == 0) {
                    tablero[i][k] = tablero[i][j];
                    tablero[i][j] = 0;
                } else if (tablero[i][k] == tablero[i][j]) {
                    tablero[i][k] *= 2;
                    puntaje += tablero[i][k];  
                    tablero[i][j] = 0;
                    k--;
                } else {
                    k--;
                    tablero[i][k] = tablero[i][j];
                    if (j != k) {
                        tablero[i][j] = 0;
                    }
                }
            }
        }
    }
}

bool puede_mover_arriba() {
    for (int j = 0; j < SIZE; j++) {
        for (int i = 1; i < SIZE; i++) {
            if (tablero[i][j] == tablero[i - 1][j] && tablero[i - 1][j] !=0 ) {
                return true;
            }
            if ( tablero[i - 1][j] == 0 && tablero[i][j] !=0)
            {
                return true;
            }
            
        }
    }
    return false;
}

void mover_arriba() {
    for (int j = 0; j < SIZE; j++) {
        int k = 0;
        for (int i = 1; i < SIZE; i++) {
            if (tablero[i][j] != 0) {
                if (tablero[k][j] == 0) {
                    tablero[k][j] = tablero[i][j];
                    tablero[i][j] = 0;
                } else if (tablero[k][j] == tablero[i][j]) {
                    tablero[k][j] *= 2;
                    puntaje += tablero[k][j];  
                    tablero[i][j] = 0;
                    k++;
                } else {
                    k++;
                    tablero[k][j] = tablero[i][j];
                    if (i != k) {
                        tablero[i][j] = 0;
                    }
                }
            }
        }
    }
}

bool puede_mover_abajo() {
   for (int j = 0; j < SIZE; j++) {
        for (int i = 0; i < SIZE - 1; i++) {
            if (tablero[i][j] == tablero[i + 1][j] && tablero[i + 1][j] !=0 ) {
                return true;
            }
            if ( tablero[i + 1][j] == 0 && tablero[i][j] !=0)
            {
                return true;
            }
            
        }
    }
    return false; 
}

void mover_abajo() {
    for (int j = 0; j < SIZE; j++) {
        int k = SIZE - 1;
        for (int i = SIZE - 2; i >= 0; i--) {
            if (tablero[i][j] != 0) {
                if (tablero[k][j] == 0) {
                    tablero[k][j] = tablero[i][j];
                    tablero[i][j] = 0;
                } else if (tablero[k][j] == tablero[i][j]) {
                    tablero[k][j] *= 2;
                    puntaje += tablero[k][j];  
                    tablero[i][j] = 0;
                    k--;
                } else {
                    k--;
                    tablero[k][j] = tablero[i][j];
                    if (i != k) {
                        tablero[i][j] = 0;
                    }
                }
            }
        }
    }
}
bool jugar_de_nuevo() {
    char respuesta;
    printf("Deseas jugar de nuevo? (Y/n): ");
    scanf(" %c", &respuesta);

    if (respuesta == 'y' || respuesta == 'Y') {
        return true;
    } else if (respuesta == 'n' || respuesta == 'N') {
        return false;
    } else {
        printf("Respuesta invalida. Por favor, intenta de nuevo.\n");
        return jugar_de_nuevo();
    }
}

void reiniciar_juego() {
    puntaje = 0;
    gano = false;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            tablero[i][j] = 0;
        }
    }
}

partida crear_partida(jugador jugador) {
    partida partida_nueva;
    partida_nueva.jugador_partida = jugador;

    partida_nueva.fecha_partida; 
    partida_nueva.abortada = false;
    
    return partida_nueva;
}

void listar_partidas_jugadas(partidas partidas) {
    printf("Listado de todas las partidas jugadas:\n");
    for (int i = 0; i < partidas.tope; i++) {
        time_t now;
        time(&now);
        printf("Fecha y hora:%s\n", ctime(&now));
        printf("Alias del jugador: %s\n", partidas.arr_partida[i].jugador_partida.alias);
        printf("Resultado: %s\n", partidas.arr_partida[i].abortada ? "No Lograda" : "Lograda");
        printf("\n");
    }
}

void partidas_por_usuario(partidas partidas, jugadores &jugador) {
    bool encontrado = false;
    char us[10];
    printf("Listado de partidas del usuario, ingrese el alias:\n");
    scanf("%s", us);
    for (int i = 0; i < partidas.tope; i++) {
        if (comparar(partidas.arr_partida[i].jugador_partida.alias, us)) {
            time_t now;
            time(&now);
            printf("Fecha y hora: %s", ctime(&now));
            printf("Resultado: %s\n", partidas.arr_partida[i].abortada ? "No Lograda" : "Lograda");
            printf("\n");
            
            encontrado = true;
        }
    }
    
    if (!encontrado) {
        printf("No se encontraron partidas para el usuario %s.\n", us);
    }
}

void juego_2048(partida partida_actual, jugador jugador, partidas &partidas) {
    srand(time(NULL));

    aniadir_random();
    aniadir_random();

    printf("Bienvenido al juego 2048!\n");
    printf("Presiona las teclas w, a, s, d para mover los numeros.\n");

    bool continuar_juego = true; // Variable para controlar la salida del bucle
    
    while (poder_mover() && continuar_juego) {
        print_tablero();
        printf("Puntaje: %d\n", puntaje);
        char c;
        scanf(" %c", &c);  // Leer un único carácter (ignorando el carácter de nueva línea)
        if (c == 'a' || c == 'A') {
            if (puede_mover_izq()) {
                mover_izq();
                aniadir_random();  // Agregar solo un número aleatorio después del movimiento
            }
        } else if (c == 'd' || c == 'D') {
            if (puede_mover_der()) {
                mover_der();
                aniadir_random();
            }
        } else if (c == 'w' || c == 'W') {
            if (puede_mover_arriba()) {
                mover_arriba();
                aniadir_random();
            }
        } else if (c == 's' || c == 'S') {
            if (puede_mover_abajo()) {
                mover_abajo();
                aniadir_random();
            }
        } else if (c == 'z' || c == 'Z') {
            printf("Partida Abortada.\n");
            partida_actual.abortada = true;
            partida_actual.puntaje_partida = puntaje;
            partidas.arr_partida[partidas.tope] = partida_actual;
            partidas.tope = partidas.tope + 1;
            continuar_juego = false; // Salir del bucle
        } else {
            printf("Letra invalida: ingrese alguna de las letras (A, a, D, d, S, s, W, w)\n");
        }
    }

    if (continuar_juego) {
        partidas.arr_partida[partidas.tope] = partida_actual;
        partidas.tope = partidas.tope + 1;
        partida_actual.puntaje_partida = puntaje;

        if (!gano) {
            printf("Game over!\n");
        }

        if (jugar_de_nuevo()) {
            reiniciar_juego();
            partida partida_nueva = crear_partida(jugador);
            juego_2048(partida_nueva, jugador, partidas);
        }
    }
  
}

void jugar(jugadores jugadores, partidas &partidas) {
    char alias[10];
    bool encontrado = false;
    printf("Ingrese el Alias del jugador para comenzar el juego: ");
    jugador jugador; //jugador con el alias que se ingresa
    do {
        scanf("%s", alias);
       
        int i = 0;
        while (i < jugadores.tope){
            int j = 0;
            int match = 1;
        
            while (jugadores.arr_jugadores[i].alias[j] != '\0' || alias[j] != '\0') {
                if (jugadores.arr_jugadores[i].alias[j] != alias[j]) {
                    match = 0;
                   
                }
                
                j++;
            }
            
            if (match == 1) {
                encontrado = true;
                jugador = jugadores.arr_jugadores[i];    
                if (!jugadores.arr_jugadores[i].activo) {
                    printf("El jugador esta inactivo.\n");
                    encontrado = false; // Restablecer encontrado a falso para permitir un nuevo intento
                }
               
            }
            
            i++;
        }
        
        if (!encontrado) {
            printf("Alias incorrecto. Intentelo nuevamente: ");
        }
    } while (!encontrado);
   
    time_t now;
    time(&now);

    partida partida_nueva = crear_partida(jugador);

    printf("Hoy es %s", ctime(&now));
    printf("Ingrese 'z' para Abortar la partida.");
    
    juego_2048(partida_nueva, jugador, partidas);
    reiniciar_juego();
}

int menu(){

	printf("Ingrese alguna de las siguientes opciones: \n");
	printf("\n");
	printf("11 - Alta de usuario \n");
	printf("12 - Baja de usuario \n");
	printf("13 - Modificacion de usuario \n");
	printf("\n");
	printf("2 - Jugar \n");
	printf("\n");
	printf("31 - Listado de usuario \n");
	printf("32 - Listado de partidas jugadas \n");
	printf("33 - Listado de partidas por Usuario \n");
	printf("\n");
	printf("4 - SALIR \n");
	
	int opcion;
	scanf("%d",&opcion);
    return opcion;

}

int main() {
	
	jugadores jugadores; // num de jugadores
	jugadores.tope = 0;    // Inicializo el tope a cero    
    partidas partidas;   // num de partidas
    partidas.tope = 0;  
    
	 int opcion = menu(); 
	 
	 while (opcion != 4){
	 	 switch(opcion){
	 	    case 11: alta_usuario(jugadores);
	 	        break;
            case 12: baja_usuario(jugadores);
                break;
            case 13: modificar_usuario(jugadores);
                break;
            case 2: jugar(jugadores, partidas);
                break;
		    case 31: listar_usuarios(jugadores);     
                break; 
            case 32:  listar_partidas_jugadas(partidas);
                break; 
            case 33:  partidas_por_usuario(partidas, jugadores); 
                break; 
	 }
	 opcion = menu();
	 }
  
    return 0;
}
 