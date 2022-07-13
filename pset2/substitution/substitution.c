#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // make sure user input key
    if (argc != 2)
    {
        printf("Usage : ./substitution key\n");
        return 1;
    }

    // make sure key is alphabrts
    string key = argv[1];
    for (int i = 0; i < strlen(key); i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Usage : ./substitution key\n");
            return 1;
        }
    }

    // Validate that key consist of 26 char
    if (strlen(key) != 26)
    {
        printf("Usage : ./substitution key\n");
        return 1;
    }

    // Validate that each key is uniq and make it upper
    for (int i = 0; i < strlen(key); i++)
    {
        for (int j = i + 1; j < strlen(key); j++)
        {
            if (toupper(key[i] == toupper(key[j])))
            {
                printf("Usage : ./substitution key\n");
                return 1;
            }
        }
    }

    // prompt user to get text
    string plain = get_string("Plaintext: ");

    //convert key to upper
    for (int i = 0; i < strlen(key); i++)
    {
        if (islower(key[i]))
        {
            key[i] = key[i] - 32;
        }
    }


    // print the cypher text
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plain); i++)
    {
        if (isupper(plain[i]))
        {
            int letter = plain[i] - 65;                 //to know the place of key for that char
            printf("%c", key[letter]);
        }
        else if (islower(plain[i]))
        {
            int letter = plain[i] - 97;
            printf("%c", key[letter] + 32);
        }
        else
        {
            printf("%c", plain[i]);                     // for sympoles
        }
    }
    printf("\n");
}