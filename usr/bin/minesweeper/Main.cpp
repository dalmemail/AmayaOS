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
#include <files.h>
#include "minesweeper.h"
#include "minesweeper_colors.h"

/* genera un numero aleatorio menor de max utilizando un seeder */
int random(int max, int seeder)
{
	if (seeder > 10) {
		seeder = seeder / 2;
	}
	if (seeder < 1) {
		seeder = getTime() % 10;
	}
	int n = getTime();
	for (int i=0; i < seeder; i++) {
		n = n / 10;
	}
	n = n % 10;
	if (n >= max) {
		n--;
	}

	return n;
}

#define COLUMNAS 9
#define FILAS 9
#define SIN_BOMBA -2
#define BOMBA -1
#define SIN_JUGAR -3

#define ESTADO_PERDEDOR 0
#define ESTADO_GANADOR  1
#define ESTADO_EN_JUEGO 2

#define VERSION "0.1.5"
#define BUILD 9

int campo[FILAS][COLUMNAS];
bool jugadas[FILAS][COLUMNAS];
//Casilla jugada

int njugadas;
int estado;

float version = 0.1;
int build = 4;

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

int agregaBombas(/*int nbombas*/){
    int i,x,y;// contador de bombas
    printf(YELLOW "Numero de bombas: ");
    int nbombas = getnum();
    int seeder = 0;
    printf(RED "%d\n", nbombas);
    x = random(FILAS, 1);
    y = random(COLUMNAS, 2);
    for (i = 1; i <= nbombas; i++) {
	campo[x][y] = BOMBA;
	x = random(FILAS, i+1+seeder);
	y = random(FILAS, i+4+seeder);
	for (int x2 = 0, p = 0; x2 < 9; x2++) {
		for (int y2 = 0; y2 < 9; y2++) {
			if (campo[x2][y2] == BOMBA) {
				p++;
			}
		}
		if (p < i && x2 == 8) {
			seeder++;
			i--;
		}
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
    /*int nbombas = -1;
    while( nbombas < 0 || nbombas > 70 ){
        printf("Numero de bombas: ");
	nbombas = getnum();
	printf("%d\n", nbombas);
    }*/

    int x,y;
    estado = ESTADO_EN_JUEGO;
    njugadas = 0;
    iniciaArr();

    //PID es un identificador de procesos, cada vez
    // que un nuevo proceso se ejectua se le asigna un PID
    // diferente - Se necesita libreria - unistd.h
    //srand( getpid() );
    //srand ( time(NULL) );
    //agregaBombas( nbombas );
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
        if( njugadas == ( FILAS*COLUMNAS - nbombas) ){
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
