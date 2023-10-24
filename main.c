#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

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

void DisplayMenu()
{
    printf("Welcome to the Hangman game.\nPress:\n- h for help\n- s to start\n- q to quit\n");
}

void Help()
{
    printf("Help\n");
}

void Quit()
{
    printf("Quit\n");
}

size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    char **result = (char **)userp;

    *result = (char *)realloc(*result, realsize + 1);
    if (*result)
    {
        memcpy(*result, contents, realsize);
        (*result)[realsize] = '\0';
    }

    return realsize;
}

char *chooseWord()
{
    CURL *curl;
    CURLcode res;
    char *result = NULL;

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "https://givemeaword.vercel.app/word?lang=en");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
    }

    return result;
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

int PlayGame()
{
    char *wordToGuess = chooseWord();
    char guessedLetters[27] = "";
    char input[10];
    int nbError = 0;

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
        else if (strlen(input) == 1) // vérifie que la saisie est une seule lettre
        {
            char letter = input[0];
            // vérifie si la lettre n'a pas déjà été devinée
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
    return nbError; // Return le nbr d'error
}

int main(int ac, char **av)
{
    DisplayMenu();
    char c;

    while (1)
    {
        printf("Enter a command: ");
        scanf(" %c", &c);
        switch (c)
        {
        case 'h':
            Help();
            break;
        case 's':
            PlayGame();
            break;
        case 'q':
            Quit();
            return 0; // End the game
        default:
            printf("Unknown command\n");
            break;
        }
    }
    return 0;
}
