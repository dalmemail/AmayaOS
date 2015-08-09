/*
 * Copyright (C) 2010 Edward, 2015 Dan Rulos
 *      edward1738@gmail.com, amaya@amayaos.com
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdio.h>
#include "minesweeper.h"
#include "minesweeper_colors.h"

int random(int seeder)
{
	int random_n = (getTime()%10) + ((getTime()%100)*10);
	while (random_n > 8) {
		random_n = random_n / seeder;
	}
	return random_n;
}

#define COLUMNAS 9
#define FILAS 9
#define SIN_BOMBA -2
#define BOMBA -1
#define SIN_JUGAR -3

#define ESTADO_PERDEDOR 0
#define ESTADO_GANADOR  1
#define ESTADO_EN_JUEGO 2

#define VERSION "0.1.8"
#define BUILD 13

#define MAX_BOMBAS 40

int campo[FILAS][COLUMNAS];
bool jugadas[FILAS][COLUMNAS];
//Casilla jugada

int njugadas;
int estado;

/*
 * 
 */
void timecount(int starttime)
{
	unsigned int secondsplaying = timeplaying(starttime);
	printf(CYAN "Tiempo: %d:%d\n", (secondsplaying / 60), (secondsplaying % 60));
}

void iniciaArr(){
    int i,j;
    for( i = 0; i < FILAS; i++){
        for(j = 0; j < COLUMNAS; j++){
            campo[i][j] = SIN_BOMBA;
            jugadas[i][j] = false; //No se ha jugado en casilla
        }
    }
}

int agregaBombas(){
    int i,x,y;// contador de bombas
    char n_bombas[4];
    int nbombas = 0;
    do {
	printf(YELLOW "Numero de bombas: ");
	gets_s(n_bombas, 4);
	nbombas = atoi(n_bombas);
    } while(nbombas > MAX_BOMBAS);
    int seeder = 2;
    for (i = 1; i <= nbombas; i++) {
	x = random(seeder);
	y = random(i+seeder);
	if (campo[x][y] != BOMBA) {
		campo[x][y] = BOMBA;
	}
	else {
		i--;
	}
	seeder = seeder + (getTime()%10);
	if (seeder > 30) {
		seeder = 2;
	}
    }
    return nbombas;
}

void print(){
    int i,j;
    printf(WHITE "[x] 0  1  2  3  4  5  6  7  8\n");
    printf(WHITE "------------------------------\n");
    for( i = 0; i < FILAS; i++){
        printf("[%d]", i);
        for(j = 0; j < COLUMNAS; j++){
            if( jugadas[i][j] ){
                if( campo[i][j] == BOMBA){
                    printf(RED " * ", WHITE);
                }else{
                    printf(WHITE " %d ", campo[i][j]);
                }
            }else{
                printf(WHITE " - ");
            }
        }
        printf("\n");
    }
}

int contar2(int x, int y){
    int nbombas = 0;
    for(int i = x-1; i < x+2; i++){
        for(int j = y-1; j < y+2; j++){
            if( i >= 0 && i < FILAS && j >= 0 && j < COLUMNAS ){
                if( campo[i][j] == BOMBA){ //Existe bomba
                    nbombas++;
                }
            }
        }
    }
    return nbombas;
}

void establecerNumeros(){
    int i,j, numero;
    for( i = 0; i < FILAS; i++){
        for(j = 0; j < COLUMNAS; j++){
            if( campo[i][j] == SIN_BOMBA){ //no tiene bomba
                numero = contar2(i,j);
                campo[i][j] = numero;
            }
        }
    }
}

void printAll(){
    for(int i = 0; i < FILAS; i++){
        for(int j = 0; j < COLUMNAS; j++){
            if( campo[i][j] == BOMBA){
                printf(RED " * ", WHITE);
            }else{
                printf(WHITE " %d ", campo[i][j]);
            }
        }
        printf("\n");
    }
}

void jugada(int x, int y){
    if( x >= 0 && x < FILAS && y >= 0 && y < COLUMNAS ){
        jugadas[x][y] = true;
        if( campo[x][y] == BOMBA){
            estado = ESTADO_PERDEDOR;
        }
    }else{
        printf(WHITE "Imposible jugada\n");
        printf(WHITE "Pulse una tecla para continuar\n");
	getchar();
    }
}

int contarJugadas(){
    int numero = 0;
    for(int i = 0; i < FILAS; i++){
        for(int j = 0; j < COLUMNAS; j++){
            if ( jugadas[i][j]){
                numero++;
            }
        }
    }
    return numero;
}

void jugadaEnGrupo(int x, int y){
    if( x >= 0 && x < FILAS && y >= 0 && y < COLUMNAS ){
        jugadas[x][y] = true;
        if( campo[x][y] == BOMBA){
            estado = ESTADO_PERDEDOR;
        }else if( campo[x][y] == 0){//Cero bombas alrededor
            for(int i = x-1; i < x+2; i++){
                for(int j = y-1; j < y+2; j++){
                    if( i >= 0 && i < FILAS && j >= 0 && j < COLUMNAS ){
                        if( campo[i][j] == 0 && !jugadas[i][j]){ //Existe bomba
                            jugadaEnGrupo(i,j);
                        }else{
                            jugadas[i][j] = true;
                        }
                    }
                }
            }
        }
    }
}

int getMenu(){
    printf(WHITE "1. Jugar Buscaminas\n");
    printf(WHITE "2. Sobre el autor\n");
    printf(WHITE "3. Salir\n");
    printf(YELLOW "Opcion: ");
    int opt;
    opt = getnum();
    printf(BLUE "%d\n", opt);
    return opt;
}

void aboutMe(){
    printf(BLUE "By Edward -> edward1738@gmail.com\n");
    printf(BLUE "By AmayaOS-> amaya@amayaos.com\n");
    printf(GREEN "Version: %s Build: %d\n", VERSION, BUILD, WHITE);
}

void iniciarJuego(){

    int x,y;
    estado = ESTADO_EN_JUEGO;
    njugadas = 0;
    iniciaArr();

    int nbombas = agregaBombas();
    establecerNumeros();
    int starttime = getTime();

    while( estado == ESTADO_EN_JUEGO){ //estado en juego
        aboutMe();
	timecount(starttime);
        print();
        printf(WHITE "Fila: ");
        x = getnum();
        printf(WHITE "%d\nColumna: ", x);
        y = getnum();
	printf(WHITE "%d\n", y);
        jugadaEnGrupo(x,y);
        char str[] = {0x1b, 0x5b, 0x48, 0x1b, 0x5b, 0x4a, '\0'};
	printf("%s", str);
        njugadas = contarJugadas();
        if( njugadas == ( FILAS*COLUMNAS - nbombas) && estado != ESTADO_PERDEDOR){
            estado = ESTADO_GANADOR;
        }
    }

    if( estado == ESTADO_PERDEDOR){
        print();
        printf(RED "perdiste\n");
        printf(WHITE "Solucion: \n");
        printAll();
    }else{
        printf(GREEN "Ganaste !\n");
        printAll();
    }
}

int main(int argc, char** argv) {
    char str[] = {0x1b, 0x5b, 0x48, 0x1b, 0x5b, 0x4a, '\0'};
    printf("%s", str);
    int opt = 0;
    do{
        opt = getMenu();
        switch(opt){
            case 1:
		iniciarJuego();
		break;
            case 2:
		aboutMe();
		break;
        }
        printf("Pulse una tecla para continuar\n");
	getchar();
	printf("%s", str);
    }while( opt != 3);
    return 0;
}
