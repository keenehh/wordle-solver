#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 7

int score_letter(char letter, char **vocabulary, size_t num) { //checks the amount of time a single letter has occured
	int score = 0;
	for (size_t i = 0; i < num; i++) {
		if (vocabulary[i] != NULL) {
			for (int j = 0; j < 5; j++) {
				if (vocabulary[i][j] == letter) {
					score += 1;	
					break; //break since we arent counting duplicate letters in a word
				}
			}
		}
	}
	return score;
}

bool letter_occured(char word, char *array) { //helper for checking if the letter has occured
	for (int i = 0; i < 5; i++) {
		if (word == array[i]) {
			return true;
		}
	}
	return false;
}

int score_word(char *word, int *letter_scores) { //adds the total score of the word from each letter
	int score = 0;
	char checked[5] = {0};
	for (int i = 0; i < 5; i++) {
		if (letter_occured(word[i], checked) != true) {
			checked[i] += word[i];
			score += letter_scores[word[i] - 'a'];	//letter scores contains the value of each letter
		}
	}
	return score;
}


bool score_guess(char *answer, char *guess, char *result) { //returns true when the guess matches the answer else false
	for (int i = 0; i < 5; i++) {	//resets the results
		result[i] = 0;
	}

	if (strncmp(guess, answer, 5) == 0) { //checks if the guess is the result
		for (int i = 0; i < 5; i ++) {
			result[i] = 'g';
		}
		return true;
	}

	for (int i = 0; i < 5; i++) {	    //checks if the guess contains any of the letters from the secret word
		for (int j = 0; j < 5; j++) {
			if (guess[i] == answer[j]) {
				result[i] = 'y';
			}
		}
	}

	for (int i = 0; i < 5; i++) {
		if (guess[i] == answer[i]) {
			result[i] = 'g';
		}
	}
	return false;			
}

char *get_score(char **vocabulary, size_t num) { //cite: Professor Alex Rudnick
	int letter_scores[26];

	for (int i = 0; i < 26; i++) {
		letter_scores[i] = score_letter('a' + i, vocabulary, num); //score each letter
	}
	
	char *best_guess = NULL;
	int best_score = 0;
	int score = 0;

	for (size_t i = 0; i < num; i++) {
		if (vocabulary[i] == NULL) { //the word has been removed so skip it
			continue;
		}
		score = score_word(vocabulary[i], letter_scores);
		if (score > best_score) {
			best_guess = vocabulary[i];	//set the output to be that word
			best_score = score;		//change the best score
		}
	}
	return best_guess ? strdup(best_guess) : NULL;
}

size_t filter_gray(char letter, char **vocabulary, size_t num) {		//this will filter out all of the words that contain the gray letter
	size_t filtered = 0;
 	for (size_t i = 0; i < num; i++) {		
    		if (vocabulary[i] != NULL) {			//checks if the word is NULL.
      			for (int j = 0; j < 5; j++) {
        			if (vocabulary[i][j] == letter) {
          				free(vocabulary[i]);
          				vocabulary[i] = NULL;
          				filtered += 1;
          				break;
        			}
      			}
    		}
  	}	
  	return filtered;
}

size_t filter_yellow(char letter, char **vocabulary, size_t num) { //this will filter out all of the words that contain the yellow letter in the certain spot
	size_t filtered = 0;
	for (size_t i = 0; i < num; i++) {
		char *p;
		if (vocabulary[i] != NULL) {
			p = strchr(vocabulary[i], letter);
			if (vocabulary[i][position] == letter) {
				free(vocabulary[i]);
				vocabulary[i] = NULL;
				filtered += 1;
			}
			if (p == NULL) {
				free(vocabulary[i]);
				vocabulary[i] = NULL;
				filtered += 1;
			}
		}
	}
	return filtered;
}

size_t filter_green(char letter, int position, char **vocabulary, size_t num_words) { //this will filter out all of the words that dont contain the green letter in certain spot
	size_t filtered = 0;
	for (size_t i = 0; i < num_words; i++) {
		if (vocabulary[i] != NULL) {
			if (vocabulary[i][position] != letter) {
				free(vocabulary[i]);
				vocabulary[i] = NULL;
				filtered += 1;
			}
		}
	}
	return filtered;
}

void free_vocabulary(char **vocabulary, size_t num) {
	for (size_t i = 0; i < num_words; i++) {
		free(vocabulary[i]);
	}
	free(vocabulary);
}

