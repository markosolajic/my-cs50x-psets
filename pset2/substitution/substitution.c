// Author: Marko Solajic

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool check_alphabetic(string argv, int str_len);
bool check_repeating_chars(string argv, int str_len);
void print_ciphertext(int plaintext_len, string plaintext, int key_len, char original_alphabet[], string argv);

int main(int argc, string argv[])
{
    int key_len;
    string plaintext;

    // check if the key is valid
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        // key length
        key_len = strlen(argv[1]);
        bool if_alpha = check_alphabetic(argv[1], key_len);
        bool if_repeating_chars = check_repeating_chars(argv[1], key_len);

        if (key_len != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        else if (if_alpha != true)
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
        else if (if_repeating_chars != true)
        {
            printf("Key must not contain repeated characters.\n");
            return 1;
        }
        else
        {
            // prompt the user for plaintext
            plaintext = get_string("plaintext:  ");
        }
    }

    // normal alphabet
    char original_alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                                'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    // plaintext length
    int plaintext_len = strlen(plaintext);

    // print ciphertext from function
    printf("ciphertext: ");
    print_ciphertext(plaintext_len, plaintext, key_len, original_alphabet, argv[1]);

    return 0;
}

// check if any of the characters are not alphabetic
bool check_alphabetic(string argv, int key_len)
{
    for (int i = 0; i < key_len; i++)
    {
        if (isalpha(argv[i]) == false)
        {
            return false;
            break;
        }
    }
    return true;
}

// check for repeating characters
bool check_repeating_chars(string argv, int key_len)
{
    for (int i = 0; i < key_len; i++)
    {
        for (int j = i + 1; j < key_len; j++)
        {
            if (tolower(argv[i]) == tolower(argv[j]))
            {
                return false;
                break;
            }
        }
    }
    return true;
}

// print ciphertext, map each letter with correct letter
void print_ciphertext(int plaintext_len, string plaintext, int key_len, char original_alphabet[], string argv)
{
    for (int i = 0; i < plaintext_len; i++)
    {
        if (isalpha(plaintext[i]) == false)
        {
            printf("%c", plaintext[i]);
            continue;
        }

        for (int j = 0; j < key_len; j++)
        {
            if (isupper(plaintext[i]))
            {
                if (plaintext[i] == original_alphabet[j])
                {
                    printf("%c", toupper(argv[j]));
                }
            }
            else if (islower(plaintext[i]))
            {
                if (plaintext[i] == tolower(original_alphabet[j]))
                {
                    printf("%c", tolower(argv[j]));
                }
            }
        }
    }
    printf("\n");
}
