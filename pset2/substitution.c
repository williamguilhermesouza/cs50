#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int invalid(char key[]);
string encrypt(char text[], char key[]);



int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution <arg> \n");
        return 1;
    }

    if (invalid(argv[1]) != 0)
    {
        printf("Invalid argument\n");
        return 1;
    }

    string plaintext = get_string("plaintext: ");
    string cipher = encrypt(plaintext, argv[1]);
    printf("ciphertext: %s\n", cipher);
    return 0;
}

int invalid(char key[])
{
   int length = 0;

   for (int i = 0; key[i] != '\0'; i++)
    {
        length++; // for testing if the length is 26
        if (isalpha(key[i]) == 0) // loop that tests if the key is made of letters
        {
            return 1;
        }
        for (int j = i + 1; key[j] != '\0'; j++) // loop that test if any of the letters repeat at the key
        {
            if (tolower(key[i]) == tolower(key[j]))
            {
                return 2;
            }
        }
    }

    if (length != 26)
    {
        return 3;
    }

    return 0;
}

string encrypt(char text[], char key[])
{

    char coded[strlen(text)];
    int letter_int;
    char letter;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]) != 0)
        {
            if (isupper(text[i]) != 0)
            {
                letter_int = text[i] - 65;
                letter = toupper(key[letter_int]);
                coded[i] = letter;
            }
            else
            {
                letter_int = text[i] - 97;
                letter = tolower(key[letter_int]);
                coded[i] = letter;
            }
        }
        else
        {
            coded[i] = text[i];
        }
    }

    string coded_return = coded;
    return coded_return;
}