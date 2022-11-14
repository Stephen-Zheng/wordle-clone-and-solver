#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// - 'x' goes in a slot if the corresponding letter in the guess does not appear
//   anywhere in the secret word
// - 'y' goes in a slot if the corresponding letter in the guess appears in the
//   secret word, but not in the corresponding slot
// - 'g' goes in a slot if the corresponding letter in the guess appears in the
//   corresponding slot in the secret word.

bool score_guess(char *secret, char *guess, char *result) {
  

  if(strcmp(secret, guess) == 0){
    return true;
  }

  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 5; j++){
      // print out secret word
        // printf("%c", secret[j]);
      if(secret[i] == guess[i]){
        result[i] = 'g';
      }
      else if(strchr(secret, guess[i]) != NULL){
          result[i] = 'y';
        }
      else {
        result[i] = 'x';
      }
    }
  }

  return false;
}

// Returns true if the specified guess is one of the strings in the vocabulary,
// and false otherwise. num_words is the length of the vocabulary.
bool valid_guess(char *guess, char **vocabulary, size_t num_words) {
  
  for(size_t i = 0; i < num_words; i++){
    if(strcmp(guess, *(vocabulary + i)) == 0){
    return true;
    }
  }
  return false;
}

// Returns an array of strings (so, char **), where each string contains a word
// from the specified file..
char **load_vocabulary(char *filename, size_t *num_words) {
  char **out = NULL;
  char **new_out = NULL;
  


  size_t more_mem = 512;

  out = (char **)malloc((more_mem)*sizeof(char *));
  *num_words = 0;

  FILE* infile;
  char buff[512];

  infile = fopen(filename, "r");

  while(fgets(buff, 512, infile) != NULL){
    out[*num_words] = strndup(buff, 5);
    //printf("%s", out[*num_words]);
    (*num_words) += 1;

    // if out is out of mem realloc more mem in blocks
    if((*num_words) == more_mem){
      more_mem = more_mem * 2;
      new_out = realloc(out, more_mem * sizeof(char *));
      if(new_out != NULL){
        out = new_out;
      }
    }
  }
  fclose(infile);
  return out;
}

// Free each of the strings in the vocabulary, as well as the pointer vocabulary
// itself (which points to an array of char *).
void free_vocabulary(char **vocabulary, size_t num_words) {
  // TODO(you): finish this function
  for(size_t i = 0; i < num_words; i++){
    free(vocabulary[i]);
  }
  free(vocabulary);
}


int main(void) {
  char **vocabulary;
  size_t num_words;
  int num_guesses = 0;

  srand(time(NULL));

  // load up the vocabulary and store the number of words in it.
  vocabulary = load_vocabulary("vocabulary.txt", &num_words);

  // Randomly select one of the words from the file 
  int word_index = rand() % num_words;
  char *secret = vocabulary[word_index];

  // input buffer -- we'll use this to get a guess from the user.
  char guess[80];

  // buffer for scoring each guess.
  char result[6] = {0};
  bool success = false;

  printf("time to guess a 5-letter word! (press ctrl-D to exit)\n");
  while (!success) {
    printf("guess: ");
    if (fgets(guess, 80, stdin) == NULL) {
      break;
    }
    // Whatever the user input, cut it off at 5 characters.
    guess[5] = '\0';

    if (!valid_guess(guess, vocabulary, num_words)) {
      printf("not a valid guess\n");
      continue;
    } else {
      num_guesses++;
    }
    success = score_guess(secret, guess, result);
    printf("%s\n", guess);
    printf("%s\n", result);
  }

  if (success) {
    printf("you win, in %d guesses!\n", num_guesses);
  }
  free_vocabulary(vocabulary, num_words);

  return 0;
}
