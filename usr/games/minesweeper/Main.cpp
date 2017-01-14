/*
 * Copyright (C) 2010 Edward Cacho Casas, 2015, 2016, 2017 Daniel Martín
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
#include "minesweeper_colors.h"

#define COLUMNS 9
#define ROWS 9
#define NOT_MINE -2
#define MINE -1

#define LOSER 0
#define WINNER  1
#define PLAYING 2
#define END_OF_GAME 3

#define VERSION "0.2.1.1"

#define MINES_MAX 40

#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define EXIT 'q'
#define SELECT '\n'

int mines_array[ROWS][COLUMNS];
bool moves[ROWS][COLUMNS];

int move;
int state;

void clean_screen()
{
	char str[] = {0x1b, 0x5b, 0x48, 0x1b, 0x5b, 0x4a, '\0'};
	printf("%s", str);
}

void addMines(int mines){
    int i,x,y;// contador de bombas
    int seeder = time(NULL);
    for (i = 1; i <= mines; i++) {
	x = (random(seeder) % 9);
	seeder += ((seeder % 1000)+1);
	y = (random(seeder) % 9);
	seeder += ((seeder % 1000)+1);
	if (mines_array[x][y] != MINE) {
		mines_array[x][y] = MINE;
	}
	else {
		i--;
	}
    }
}

void print(int x, int y){
    int i,j;
    printf(WHITE "[x] 0  1  2  3  4  5  6  7  8\n");
    printf(WHITE "------------------------------\n");
    for( i = 0; i < ROWS; i++){
        printf("[%d]", i);
        for(j = 0; j < COLUMNS; j++){
            if( moves[i][j] ){
                if( mines_array[i][j] == MINE){
			if (i != y || j != x) {
				printf(RED " * ", WHITE);
			}
			else {
				printf(RED "<*>", WHITE);
			}
                }else{
			if (i != y || j != x) {
				printf(WHITE " %d ", mines_array[i][j]);
			}
			else {
				printf(WHITE "<%d>", mines_array[i][j]);
			}
                }
            }else {
		if (i != y || j != x) {
			printf(WHITE " - ");
		}
		else {
			printf(WHITE "<->");
		}
            }
        }
        printf("\n");
    }
}

int countNumber(int x, int y){
    int mines = 0;
    for(int i = x-1; i < x+2; i++){
        for(int j = y-1; j < y+2; j++){
            if( i >= 0 && i < ROWS && j >= 0 && j < COLUMNS ){
                if( mines_array[i][j] == MINE){ //Existe bomba
                    mines++;
                }
            }
        }
    }
    return mines;
}

void putBrickNumbers(){
    int i,j, number;
    for( i = 0; i < ROWS; i++){
        for(j = 0; j < COLUMNS; j++){
            if( mines_array[i][j] == NOT_MINE){ //no tiene bomba
                number = countNumber(i,j);
                mines_array[i][j] = number;
            }
        }
    }
}

void printAll(){
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLUMNS; j++){
            if( mines_array[i][j] == MINE){
                printf(RED " * ", WHITE);
            }else{
                printf(WHITE " %d ", mines_array[i][j]);
            }
        }
        printf("\n");
    }
}

void jugada(int x, int y){
    if( x >= 0 && x < ROWS && y >= 0 && y < COLUMNS ){
        moves[x][y] = true;
        if( mines_array[x][y] == MINE){
            state = LOSER;
        }
    }else{
        printf(WHITE "Imposible jugada\n");
        printf(WHITE "Pulse una tecla para continuar\n");
	getchar();
    }
}

int MoveCounter(){
    int number = 0;
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLUMNS; j++){
            if ( moves[i][j]){
                number++;
            }
        }
    }
    return number;
}

void MakeMove(int x, int y){
    if( x >= 0 && x < ROWS && y >= 0 && y < COLUMNS ){
        moves[x][y] = true;
        if( mines_array[x][y] == MINE){
            state = LOSER;
        }else if( mines_array[x][y] == 0){//Cero bombas alrededor
            for(int i = x-1; i < x+2; i++){
                for(int j = y-1; j < y+2; j++){
                    if( i >= 0 && i < ROWS && j >= 0 && j < COLUMNS ){
                        if( mines_array[i][j] == 0 && !moves[i][j]){ //Existe bomba
                            MakeMove(i,j);
                        }else{
                            moves[i][j] = true;
                        }
                    }
                }
            }
        }
    }
}

void MinesWeeper(int mines){

	int x = 0;
	int y = 0;
	state = PLAYING;
	move = 0;
	for(int i = 0; i < ROWS; i++){
		for(int j = 0; j < COLUMNS; j++){
			mines_array[i][j] = NOT_MINE;
			moves[i][j] = false; //No se ha jugado en casilla
		}
	}

	addMines(mines);
	putBrickNumbers();
	char key;

    while( state == PLAYING){
	printf("\033[1;1H");
        print(x,y);
	key = getchar();
	if (key == UP && y > 0) {
		y--;
	}
	else if (key == DOWN && y < 8) {
		y++;
	}
	else if (key == LEFT && x > 0) {
		x--;
	}
	else if (key == RIGHT && x < 8) {
		x++;
	}
	else if (key == EXIT) {
		state = END_OF_GAME;
	}
	else if (key == SELECT) {
		MakeMove(y,x);
		move = MoveCounter();
		if( move == ( ROWS*COLUMNS - mines) && state != LOSER){
		    state = WINNER;
		}
	}
    }

	clean_screen();
	if( state == LOSER){
		print(x,y);
		printf(RED "perdiste\n");
		printf(WHITE "Solucion: \n");
		printAll();
	}
	else if (state == WINNER) {
		printf(GREEN "Ganaste !\n");
		printAll();
	}
}

int main(int argc, char** argv)
{
	int mines;
	int ret = 0;
	if (argc == 2 && (strcmp(argv[1], "--version")) == 0) {
		printf("Version: %s\n", VERSION);
	}
	else if (argc == 3 && ((strcmp(argv[1], "-m")) == 0 || (strcmp(argv[1], "--mines")) == 0)) {
		mines = atoi(argv[2]);
		if (mines > MINES_MAX) {
			printf("numero_de_minas debe ser inferior o igual que %d\n", MINES_MAX);
			ret = 1;
		}
		else if (mines < 0) {
			printf("numero_de_minas debe ser igual o superior a cero\n");
			ret = 1;
		}
		else {
			clean_screen();
			MinesWeeper(mines);
		}
	}
	else {
		printf("Uso: %s -m numero_de_minas\n", argv[0]);
	}
	return ret;
}
