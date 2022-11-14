#include "search_util.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


// loops over the vocabulary (which contains num_words entries) and returns the number of words in which that particular letter
// occurs.
int score_letter(char letter, char **vocabulary, size_t num_words) {
  
  int letter_counter = 0;
  for(size_t i = 0; i < num_words; i++){
    for(size_t j = 0; j < 5; j++){
      if(vocabulary[i] != NULL){
        if(strchr(&vocabulary[i][j], letter) != NULL){
          letter_counter += 1;
          break;
        }
      }
    }
  }
  return letter_counter;
}



int score_word(char *word, int *letter_scores) {

 
  int sum_score = 0;
  char letter;
  // for(each unique letter in the word)
  for(int i = 0; i < 26; i++){
    letter = ('a' + i);
    if(strchr(word, letter)){
      sum_score += letter_scores[i];
    }
  }
  return sum_score;

}


char *get_guess(char **vocabulary, size_t num_words) {
  int letter_scores[26];

  for (int i = 0; i < 26; i++) {
    letter_scores[i] = score_letter('a' + i, vocabulary, num_words);
  }

  char *best_guess = NULL;
  int best_score = 0;
  int score = 0;
  for (size_t i = 0; i < num_words; i++) {
    if (vocabulary[i] == NULL) {
      continue;
    }
    score = score_word(vocabulary[i], letter_scores);
    if (score > best_score) {
      best_guess = vocabulary[i];
      best_score = score;
    }
  }
  return best_guess ? strdup(best_guess) : NULL;
}


size_t filter_vocabulary_gray(char letter, char **vocabulary, size_t num_words) {

  
  int free_counter = 0;
  for(size_t i = 0; i < num_words; i++){
    if(vocabulary[i] != NULL){
      if(strchr(vocabulary[i], letter) != NULL){
        free_counter += 1;
        free(vocabulary[i]);
        vocabulary[i] = NULL;
      }
    }
  }
  return free_counter;
}


size_t filter_vocabulary_yellow(char letter, int position, char **vocabulary, size_t num_words) {

  
  int free_counter = 0;
  char letter_pos;
  for(size_t i = 0; i < num_words; i++){
    if(vocabulary[i] != NULL){
      letter_pos = vocabulary[i][position];
      if((letter_pos == letter || strchr(vocabulary[i], letter) == NULL)){
        free_counter += 1;
        free(vocabulary[i]);
        vocabulary[i] = NULL;
      }
    }
  }
  return free_counter;
}



size_t filter_vocabulary_green(char letter, int position, char **vocabulary, size_t num_words) {

  // TODO(you): implement this function!
  int free_counter = 0;
  char letter_pos;
  for(size_t i = 0; i < num_words; i++){
    if(vocabulary[i] != NULL){
      letter_pos = vocabulary[i][position];
      if(letter != letter_pos){
        free_counter += 1;
        free(vocabulary[i]);
        vocabulary[i] = NULL;
      }
    }
  }
  return free_counter;
}


void free_vocabulary(char **vocabulary, size_t num_words) {
  for (size_t i = 0; i < num_words; i++) {
    free(vocabulary[i]);
  }
  free(vocabulary);
}
