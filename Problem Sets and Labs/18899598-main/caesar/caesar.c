#include <cs50.h>
#include <stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>


bool only_digits(string cl_arg);
string rotate(string plaintext, int key);

int main(int argc, string argv[])
{
    int key;
    // Check for only single input in command line
    if (argc != 2)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    // Check if only digits are present
    else if (!only_digits(argv[1]))
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    //Convert digits to integer to extract key
    else
    {
        key = atoi(argv[1]);
        printf("Key: %i\n", key);
    }


    //ask user for input text
    string plaintext = get_string("palintext: ");

    // Convert the alphabets using key conforming with the cases and also ignore
    //characters other than alphabets
    string ciphertext = rotate(plaintext, key);
    printf("ciphertext: %s\n", ciphertext);
}


//Check if the string consists of only digits
bool only_digits(string cl_arg)
{
    bool status = true;
    for (int i = 0, n = strlen(cl_arg); i < n; i++)
    {
        if (!isdigit(cl_arg[i]))
        {
            status = false;
            return status;
        }
    }
    return status;
}


// Rotate the letter based on key and ignore characters other than alphabets
string rotate(string plaintext, int key)
{
    string ciphertext = plaintext;

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isalpha(plaintext[i]) && isupper(plaintext[i]))
        {
            int index = (((int) plaintext[i] - 65) + key) % 26;
            ciphertext[i] = (char)(index + 65);

        }
        else if (isalpha(plaintext[i]) && islower(plaintext[i]))
        {
            int index = (((int) plaintext[i] - 97) + key) % 26;
            ciphertext[i] = (char)(index + 97);

        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }
    return ciphertext;
}

