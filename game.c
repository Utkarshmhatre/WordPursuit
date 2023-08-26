#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ATTEMPTS 6
#define MAX_WORDS 5
#define MAX_CUSTOM_WORDS 10
#define MAX_WORD_LENGTH 10
#define MAX_CUSTOM_WORD_LENGTH 20

char *wordList[MAX_WORDS] = {
    "apple",
    "banana",
    "cherry",
    "grape",
    "orange"
};

void displayWordPursuit(int attempts, int gameOver) {
    const char *hangmanFigures[] = {
        "+---+\n  |   |\n      |\n      |\n      |\n      |\n=========",
        "+---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========",
        "+---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========",
        "+---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========",
        "+---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========",
        "+---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========",
        "+---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n========="
    };
    
    printf("%s\n", hangmanFigures[attempts]);
}

void enterCustomWords(char *customWords[], int *customWordCount) {
    printf("Enter custom words (up to %d words, one per line):\n", MAX_CUSTOM_WORDS);

    int i = 0;
    while (i < MAX_CUSTOM_WORDS) {
        char word[MAX_CUSTOM_WORD_LENGTH];
        printf("Enter word %d (or enter 'q' to finish): ", i + 1);
        scanf("%s", word);

        if (strcmp(word, "q") == 0) {
            break;
        }

        customWords[i] = strdup(word);
        i++;
    }

    *customWordCount = i;
}

int main() {
    srand(time(NULL));

    int wordCount = MAX_WORDS;  // Default word count
    char *wordToGuess = wordList[rand() % wordCount];  // Select word from default list

    char *customWords[MAX_CUSTOM_WORDS];  // Array to store custom words
    int customWordCount = 0;  // Number of custom words

    // Allow the player to choose between custom words and default words
    int choice;
    printf("Choose an option:\n1. Play with default words\n2. Enter custom words\n");
    scanf("%d", &choice);

    if (choice == 2) {
        enterCustomWords(customWords, &customWordCount);
        if (customWordCount > 0) {
            wordCount = customWordCount;
            wordToGuess = customWords[rand() % wordCount];  // Select word from custom list
        }
    }

    int wordLength = strlen(wordToGuess);
    char guessedWord[MAX_WORD_LENGTH];
    int correctGuesses = 0;
    int attempts = 0;

    for (int i = 0; i < wordLength; i++) {
        guessedWord[i] = '_';
    }
    guessedWord[wordLength] = '\0';

    printf("Welcome to WordPursuit!\n");

    while (correctGuesses < wordLength && attempts < MAX_ATTEMPTS) {
        printf("\nWord: %s\n", guessedWord);
        displayWordPursuit(attempts, 0); // Pass attempts and gameOver=0

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
        displayWordPursuit(attempts, 1); // Pass attempts and gameOver=1
    }

    return 0;
}
