# wordle-clone-and-solver

Clone and solver of popular word search game wordle.

Clone

reads and parses through given .txt file

When a valid guess is entered it will have corresponding "x" (letter is not in the secret word), "y" (letter is in the secret word but not in the right place), or "g" (letter is in the word and in the correct spot). This should be wordle written in c without the colored letters played in the terminal.<br>


Solver 

The solver will work in two different ways -- either the secret word may be known to the user and specified to the program , or the solver can iteratively suggest guesses to the user, so as to search for solutions to a live problem

generate a score based on how possible and close a guess is to what the secret word is and check for the ocurance of "gray, yellow, and green" letters to narrow down our given dictionary set by vocabulary.txt.
