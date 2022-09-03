#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


#include "solver.h"

int main(int argc, char **argv) {
	char **vocabulary;
	size_t num;
	int num_guesses = 0;
	char *answer = NULL;
	char *guess = NULL;

	char result[10] = {0};
	bool success = false;
	size_t filtered;

	vocabulary = load_vocabulary("vocabulary.txt", &num);

	if (argc == 2) {
		answer = argv[1];
	}

	do {
		free(guess);
		guess = get_score(vocabulary, num);
	       	if (guess == NULL) {
			printf("No more words left.\n");
			break;
		}
		num_guesses += 1;
		printf("Guess #%d: %s\n", num_guesses, guess);

		if (answer != NULL) {
			success = score_guess(answer, guess, result);
		}
		else {
			bool success2 = false;
		
			while (!success2) {
				printf("Please enter the resut as 5 characters (g,y,x): ");
				fgets(result, 10, stdin);
				result[5] = '\0';
				success2 = true;
				for (int i = 0; i < 5; i++) {
					if (result[i] != 'g' && result[i] != 'y' && result[i] != 'x') {
						success2 = false;
					}
				}
			}
			success = (strncmp(result, "ggggg", 5) == 0);
		}

		if (!success) {
			for (int i = 0; i < 5; i++) {
				if (result[i] == 'x') {
					char letter = guess[i];
					bool gray = false;
					for (int j = 0; j < 5; j++) {
						char other_letter = guess[j];
						if ((j != i) && (other_letter == letter) && (result[i] != 'x')) {
							gray = true;
						}
					}
					if (!gray) {
						printf("Filtering with gray letter: %c\n", guess[i]);
						filtered = filter_gray(guess[i], vocabulary, num);
						printf("Removed %lu words.\n", filtered);
					}
				}
				else if (result[i] == 'y') {
					printf("Filtering with yellow letter: %c\n", guess[i]);
					filtered = filter_yellow(guess[i], i, vocabulary, num);
					printf("Removed %lu words.\n", filtered);
				}
				else if (result[i] == 'g') {
					printf("Filtering with green letter: %c\n", guess[i]);
					filtered = filter_green(guess[i], i, vocabulary, num);
					printf("Removed %lu words.\n", filtered);
				}
			}
		}
	}
	while (!success); 
		if (success) {
			printf("Correct! Got it in %d guesses!\n", num_guesses);
		}
		else {
			printf("No more words left.\n");
		}
		free(guess);
		free_vocabulary(vocabulary, num);
		
		return 0;
	}
