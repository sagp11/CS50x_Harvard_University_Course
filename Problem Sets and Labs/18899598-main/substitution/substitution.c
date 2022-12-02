#include <cs50.h>
#include <stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

int check_key(string key);
string cipher_gen(string plaintext, string key);

int main(int argc, string argv[])
{

    string key;
    //Check if only one command line argument is passed
    if (argc != 2)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }
    //Check for other incorrect inputs or format for KEY
    else
    {
        switch (check_key(argv[1]))
        {
            case 0:
                key = argv[1];
                break;

            case 1:
                printf("KEY should be of length 26\n");
                return 1;
                break;

            case 2:
                printf("Each character in key must be an alphabet\n");
                return 1;
                break;

            case 3:
                printf("No duplicate alphabets allowed in the KEY\n");
                return 1;
                break;
        }

    }

    // Take user input for plain-text
    string plaintext = get_string("plaintext: ");
    string ciphertext = cipher_gen(plaintext, key);
    printf("ciphertext: %s", ciphertext);
    printf("\n");
    return 0;

}


//To check if the key matches the prescribed format
int check_key(string key)
{
    int length = strlen(key);
    int duplicate[length];
    memset(duplicate, 0, sizeof(duplicate));

    // Check for length of KEY
    if (length != 26)
    {
        return 1;
    }
    else
    {
        for (int i = 0; i < length; i++)
        {
            //Check if all characters are alphabets
            if (!isalpha(key[i]))
            {
                return 2;
            }
            else
            {
                // Create a histogram of alphabets
                int check = ((int) toupper(key[i])) - 65;
                duplicate[check] ++;

                // Check if duplicate alphabets are present in KEY
                if (duplicate[check] > 1)
                {
                    return 3;
                }
            }

        }
    }
    return 0;
}


//Encryption of PLAINTEXT using KEY to return CIPHERTEXT
string cipher_gen(string plaintext, string key)
{
    int plaintext_len = strlen(plaintext);
    int key_len = strlen(key);

    //Initialize ciphertext
    string ciphertext = plaintext;

    for (int i = 0; i < plaintext_len; i++)
    {
        //Check if the plaintext is alphabet and if uppercase
        if (isalpha(plaintext[i]) && isupper(plaintext[i]))
        {
            ciphertext[i] = toupper(key[plaintext[i] - 65]);
        }
        //Check if the plaintext is alphabet and if lowercase.
        else if (isalpha(plaintext[i]) && islower(plaintext[i]))
        {
            ciphertext[i] = tolower(key[plaintext[i] - 97]);
        }

    }
    return ciphertext;
}