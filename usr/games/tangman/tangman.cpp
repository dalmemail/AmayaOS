/*
 * Copyright (C) 2016 Dan Rulos
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

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>

int wordcount(char *file_content);
char *read_file(char *path);
int get_size(char *path);
unsigned int random_number(int max);
void clean_screen();
void print_hangman(char *playing_word, char *guessed);

#define PLAYING 0
#define WIN 1
#define LOST 2

void tangman(char *word_database_path)
{
	char *data = read_file(word_database_path);
	int n_words = wordcount(data);
	char **word_database = new char *[n_words];
	char *word;
	int status = PLAYING;
	char c;
	if (n_words > 0) {
		word_database[0] = &data[0];
		for (int i = 1, x = 0; data[x] != '\0'; x++) {
			if (data[x] == '\n'|| data[x] == ' '|| data[x] == '\t') {
				data[x] = '\0';
				if (i < n_words) {
					word_database[i] = &data[x+1];
				}
				i++;
			}
		}
		word = &word_database[random_number(n_words)][0];
		int word_len = strlen(word);
		char playing_word[word_len];
		for (int i = 0; i < word_len; i++) {
			playing_word[i] = '-';
		}
		playing_word[word_len] = '\0';
		clean_screen();
		int letters_discovered = 0;
		int letters_failed = 0;
		char guessed[10];
		guessed[0] = '\0';
		int repeat_letter = 0;
		while (status == PLAYING) {
			repeat_letter = 0;
			print_hangman(playing_word, guessed);
			c = getchar();
			for (int i = 0; i < word_len; i++) {
				if (c == word[i]) {
					if (word[i] != playing_word[i]) {
						playing_word[i] = word[i];
						letters_discovered++;
					}
					repeat_letter++;
				}
			}
			if (repeat_letter == 0) {
				int i;
				for (i = 0; guessed[i] != '\0'; i++) {
					if (c == guessed[i]) {
						repeat_letter++;
					}
				}
				if (repeat_letter == 0) {
					letters_failed++;
					guessed[i] = c;
					guessed[i+1] = '\0';
				}
			}
			if (letters_discovered == word_len) {
				print_hangman(playing_word, guessed);
				printf("You got it!\n");
				printf("Another word? [Y/n]\n");
				do {
					c = getchar();
				} while (c != 'y' && c != 'n');
				if (c == 'y') {
					tangman(word_database_path);
				}
				status = WIN;
			}
			if (letters_failed == 7) {
				print_hangman(playing_word, guessed);
				printf("Sorry, the word was \"%s\"\n", word);
				printf("Another word? [Y/n]\n");
				do {
					c = getchar();
				} while (c != 'y' && c != 'n');
				if (c == 'y') {
					tangman(word_database_path);
				}
				status = LOST;
			}
		}
	}
	delete data;
	delete word_database;
}

int wordcount(char *file_content)
{
	int n_words = 0;
	for (int i = 0; file_content[i] != '\0'; i++) {
		if (file_content[i] == ' '|| file_content[i] == '\n'|| file_content[i] == '\t') {
			n_words++;
		}
	}
	return n_words;
}

unsigned int random_number(int max)
{
	srandom(time(NULL));
	return random() % max;
}

char *read_file(char *path)
{
	int file_size = get_size(path);
	char *data = new char [file_size];
	int fd = open(path, O_RDONLY);
	read(fd, data, file_size);
	close(fd);
	/* Devolvemos el contenido del fichero */
	return data;
}

int get_size(char *path)
{
	struct stat st;
	int ssize;
	if ((stat(path, &st)) < 0) {
		ssize = -1;
	}
	else {
		ssize = st.st_size;
	}
	return ssize;
}

void clean_screen()
{
	char str[] = {0x1b, 0x5b, 0x48, 0x1b, 0x5b, 0x4a, '\0'};
	printf("%s", str);
}

void print_hangman(char *playing_word, char *guessed)
{
	char output[1024];
	int n_fails = strlen(guessed);
	strcpy(output, "\033[1;1H\n");
	strcat(output, "     ______\n");
	strcat(output, "     |    |\n");
	strcat(output, "     |    ");
	if (n_fails > 0) {
		strcat(output, "O");
	}
	strcat(output, "\n     |   ");
	if (n_fails > 1 && n_fails < 5) {
		strcat(output, " |");
	}
	if (n_fails == 5) {
		strcat(output, "/|");
	}
	if (n_fails > 5) {
		strcat(output, "/|\\");
	}
	strcat(output, "\n     |    ");
	if (n_fails > 2) {
		strcat(output, "|");
	}
	strcat(output, "\n     |   ");
	if (n_fails > 3) {
		strcat(output, "/");
	}
	if (n_fails > 6) {
		strcat(output, " \\");
	}
	strcat(output, "\n   __|_____\n");
	strcat(output, "   |      |___\n");
	strcat(output, "   |_________|\n\n");
	strcat(output, "Word: ");
	strcat(output, playing_word);
	strcat(output, "\nGuessed: ");
	strcat(output, guessed);
	printf("%s\n", output);
}
