#pragma once

#include <stdio.h>
#include <stdlib.h>

int score_letter(char letter, char **vocabulary, size_t num);

int score_word(char *word, int *letter_scores);

bool score_guess(char *answer, char *guess, char *result);

char *get_score(char **vocabulary, size_t num);

size_t filter_gray(char letter, char **vocabulary, size_t num);

size_t filter_yellow(char letter, int positon, char **vocabulary, size_t num);

size_t filter_green(char letter, int position, char **vocabulary, size_t num);

char **load_vocabulary(char *filename, size_t *num);

void free_vocab(char **vocabulary, size_t num);


