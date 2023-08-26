#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ATTEMPTS 6
#define MAX_WORDS 5
#define MAX_WORD_LENGTH 10

char *wordList[MAX_WORDS] = {
    "apple",
    "banana",
    "cherry",
    "grape",
    "orange"
};

void displayHangman(int attempts) {
    printf("  ____\n");
    printf(" |    %s\n", attempts > 0 ? "O" : "");
    printf(" |   %s%s%s\n", attempts > 2 ? "/" : " ", attempts > 1 ? "|" : "", attempts > 3 ? "\\" : "");
    printf(" |    %s\n", attempts > 4 ? "/" : "");
    printf(" |   %s\n", attempts > 5 ? "/" : "");
    printf("_|_\n");
}

int main() {
    srand(time(NULL));
    
    char *wordToGuess = wordList[rand() % MAX_WORDS];
    int wordLength = strlen(wordToGuess);
    char guessedWord[MAX_WORD_LENGTH];
    int correctGuesses = 0;
    int attempts = 0;

    for (int i = 0; i < wordLength; i++) {
        guessedWord[i] = '_';
    }
    guessedWord[wordLength] = '\0';

    printf("Welcome to Hangman!\n");

    while (correctGuesses < wordLength && attempts < MAX_ATTEMPTS) {
        printf("\nWord: %s\n", guessedWord);
        displayHangman(attempts);

        char guess;
        printf("Guess a letter: ");
        scanf(" %c", &guess);

        int found = 0;
        for (int i = 0; i < wordLength; i++) {
            if (wordToGuess[i] == guess && guessedWord[i] == '_') {
                guessedWord[i] = guess;
                correctGuesses++;
                found = 1;
            }
        }

        if (!found) {
            attempts++;
            printf("Incorrect guess!\n");
        }
    }

    if (correctGuesses == wordLength) {
        printf("\nCongratulations! You guessed the word: %s\n", wordToGuess);
    } else {
        printf("\nSorry, you're out of attempts. The word was: %s\n", wordToGuess);
        displayHangman(attempts);
    }

    return 0;
}
