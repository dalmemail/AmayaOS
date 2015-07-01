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
#include <time.h>
#include "minesweeper.h"
//#include "unistd.h"

#define COLUMNAS 9
#define FILAS 9
#define SIN_BOMBA -2
#define BOMBA -1
#define SIN_JUGAR -3

#define ESTADO_PERDEDOR 0
#define ESTADO_GANADOR  1
#define ESTADO_EN_JUEGO 2

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
    printf("Numero de bombas: ");
    int nbombas = getnum();
    printf("%d\n", nbombas);
    x = aleatorio(FILAS, 1);
    y = aleatorio(COLUMNAS, 2);
    for (i = 1; i <= nbombas; i++) {
	campo[x][y] = BOMBA;
	x = aleatorio(FILAS, i+1);
	y = aleatorio(FILAS, i+2);
    }
    return nbombas;
}

void print(){
    int i,j;
    printf("[x] 0  1  2  3  4  5  6  7  8\n");
    printf("------------------------------\n");
    for( i = 0; i < FILAS; i++){
        printf("[%d]", i);
        for(j = 0; j < COLUMNAS; j++){
            if( jugadas[i][j] ){
                if( campo[i][j] == BOMBA){
                    printf(" * ");
                }else{
                    printf(" %d ", campo[i][j]);
                }
            }else{
                printf(" - ");
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
                printf(" * ");
            }else{
                printf(" %d ", campo[i][j]);
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
        printf("Imposible jugada\n");
        printf("Pulse una tecla para continuar\n");
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
    printf("1. Jugar Buscaminas\n");
    printf("2. Sobre el autor\n");
    printf("3. Salir\n");
    printf("Opcion: ");
    int opt;
    opt = getnum();
    printf("%d\n", opt);
    return opt;
}

void aboutMe(){
    printf("By Edward -> edward1738@gmail.com\n");
    printf("By AmayaOS-> amaya@amayaos.com\n");
    printf("Version: 0.1.1 Build: 5\n");
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

    while( estado == ESTADO_EN_JUEGO){ //estado en juego
        aboutMe();
        print();
        printf("Fila: ");
        x = getnum();
        printf("%d\nColumna: ", x);
        y = getnum();
	printf("%d\n", y);
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
        printf("perdiste\n");
        printf("Solucion: \n");
        printAll();
    }else{
        printf("Ganaste !\n");
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
