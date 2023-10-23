#include <unistd.h>
#include <stdio.h>
#include <string.h>

void dispayHangman(int nb_error)
{
    if (nb_error == 0)
    {
        printf("  _______\n");
        printf(" |/      |\n");
        printf(" |\n");
        printf(" |\n");
        printf(" |\n");
        printf(" |\n");
        printf("_|___\n\n");
    }
    else if (nb_error == 1)
    {
        printf("  _______\n");
        printf(" |/      |\n");
        printf(" |      (_)\n");
        printf(" |\n");
        printf(" |\n");
        printf(" |\n");
        printf("_|___\n\n");
    }
    else if (nb_error == 2)
    {
        printf("  _______\n");
        printf(" |/      |\n");
        printf(" |      (_)\n");
        printf(" |       |\n");
        printf(" |       |\n");
        printf(" |\n");
        printf("_|___\n\n");
    }
    else if (nb_error == 3)
    {
        printf("  _______\n");
        printf(" |/      |\n");
        printf(" |      (_)\n");
        printf(" |      \\|\n");
        printf(" |       |\n");
        printf(" |\n");
        printf("_|___\n\n");
    }
    else if (nb_error == 4)
    {
        printf("  _______\n");
        printf(" |/      |\n");
        printf(" |      (_)\n");
        printf(" |      \\|/\n");
        printf(" |       |\n");
        printf(" |\n");
        printf("_|___\n\n");
    }
    else if (nb_error == 5)
    {
        printf("  _______\n");
        printf(" |/      |\n");
        printf(" |      (_)\n");
        printf(" |      \\|/\n");
        printf(" |       |\n");
        printf(" |      /\n");
        printf("_|___\n\n");
    }
    else if (nb_error == 6)
    {
        printf("  _______\n");
        printf(" |/      |\n");
        printf(" |      (_)\n");
        printf(" |      \\|/\n");
        printf(" |       |\n");
        printf(" |      / \\\n");
        printf("_|___\n\n");
    }
}

char *chooseWord()
{
    return "test";
}

void displayWord(char *word, char *guessedLetters)
{
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (strchr(guessedLetters, word[i]))
        {
            printf("%c ", word[i]);
        }
        else
        {
            printf("_ ");
        }
    }
    printf("\n");
}

int main(int ac, char **av)
{
    printf("Welcome to the Hangman game.\nPress:\n- h for help\n- s to start\n- q to quit\n");
    char c;

    while (1)
    { // boucle infinie jusqu'à ce quon quitte
        printf("Enter a command: ");
        scanf(" %c", &c); // l'espace avant %c mange tous les espaces blancs
        if (c == 'h')
        {
            printf("Help\n");
        }
        else if (c == 's')
        {
            char wordToGuess[100];
            char guessedLetters[27] = "";
            char input[10];
            int nbError = 0;
            strcpy(wordToGuess, chooseWord());
            printf("Start\n");
            printf("Guess the word:\n");
            displayWord(wordToGuess, guessedLetters);
            while (1)
            {
                printf("Guess a letter (or 'quit' to quit): ");
                scanf("%9s", input);
                if (strcmp(input, "quit") == 0)
                {
                    break;
                }
                else if (strlen(input) == 1) // vérifiez que la saisie est une seule lettre
                {
                    char letter = input[0];
                    // vérifiez si la lettre n'a pas déjà été devinée
                    if (strchr(guessedLetters, letter) == NULL)
                    {
                        strncat(guessedLetters, &letter, 1); // ajoute la lettre à guessedLetters
                        if (strchr(wordToGuess, letter) == NULL)
                        {
                            nbError++;
                            printf("Wrong guess!\n");
                            dispayHangman(nbError);
                            if (nbError > 5)
                            {
                                printf("You lost!\n");
                                break;
                            }
                        }
                        else
                        {
                            printf("Good guess!\n");
                            // vérifier si le mot à était trouvé
                            int found = 1;
                            for (int i = 0; wordToGuess[i] != '\0'; i++)
                            {
                                if (strchr(guessedLetters, wordToGuess[i]) == NULL)
                                {
                                    found = 0;
                                    break;
                                }
                            }
                            if (found)
                            {
                                printf("You won!\n");
                                break;
                            }
                            dispayHangman(nbError);
                        }
                    }
                    else
                    {
                        printf("You already guessed that letter!\n");
                    }
                }
                else
                {
                    printf("Please enter a single letter or 'quit'.\n");
                }

                displayWord(wordToGuess, guessedLetters);
            }
        }
        else if (c == 'q')
        {
            printf("Quit\n");
            break;
        }
        else
        {
            printf("Unknown command\n");
        }
    }
    return 0;
}
