#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int is_string_alphabetic(string key);
int check_repeated_character(string key);
string conversion(string text, string key);

int main(int argc, string argv[])
{
    // More than one key or none key
    if (argc != 2)
    {
        printf("Error: introduce one key\n");
        return 1;
    }
    // Non-alphabetic key, less or more than 26 characters or repeated letters
    else if (strlen(argv[1]) != 26 || is_string_alphabetic(argv[1]) == 1 ||
             check_repeated_character(argv[1]) == 1)
    {
        printf("Error: invalid key, introduce 26 alphabetic, non-repeated characters key\n");
        return 1;
    }
    // Correct key
    else
    {
        string input = get_string("plaintext: ");
        string output = conversion(input, argv[1]);
        printf("ciphertext: %s\n", output);
        return 0;
    }
}

// To check if all the chars are alphabetic
int is_string_alphabetic(string key)
{
    for (int i = 0; i < strlen(key); i++)
    {
        if (isalpha(key[i]) == false)
        {
            return 1;
        }
    }
    return 0;
}

// To check if there are repeated letters
int check_repeated_character(string key)
{
    // Array where 0 is non-seen letter and 1 is an already seen letter
    int seen[26] = {0};
    for (int i = 0; key[i] != '\0'; i++)
    {
        char c = tolower(key[i]);
        // One different idx for each letter deppending on the ASCII value
        int idx = c - 97;
        if (seen[idx] == 1)
        {
            return 1;
        }
        // We mark that we have seen that letter
        seen[idx] = 1;
    }
    return 0;
}

// Converts from a base text to a cipher text preserving uppercase or lowercase condition of the base text
string conversion(string text, string key)
{
    for (int i = 0; i < strlen(text); i++)
    {
        if (islower(text[i]))
        {
            text[i] = tolower(key[text[i] - 97]);
        }
        else if ((isupper(text[i])))
        {
            text[i] = toupper(key[text[i] - 65]);
        }
    }
    return text;
}
