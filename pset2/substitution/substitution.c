#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

void substitution_cipher(string text, string cipher_key);

int main(int argc, string argv[])
{
    string key = argv[argc - 1];

    // validate CL argument
    if (argc != 2)
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }

    if (strlen(argv[argc - 1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // check for repeating characters    
    for (int i = 0; i < 26; i++)
    {
        
        for (int j = 0; j < 26; j++)
        {
            if (tolower(key[i]) == tolower(key[j]) && !(i == j))
            {
                printf("Key cannot contain repeating charachters.\n");
                return 1;
            }
        }
    }

    // check if key contains non-alphabetical characters
    for (int i = 0; i < 26; i++)
    {
        if (!(isalpha(key[i])))
        {
            printf("Key must be completely alphabetical.\n");
            return 1;
        }
    }

    // VALIDATION END


    // get plaintext
    string plaintext = get_string("plaintext: ");
    
    // output cipher
    printf("ciphertext: ");
    substitution_cipher(plaintext, key);
    printf("\n");
}

void substitution_cipher(string \text, string cipher_key)
{
    char alpha_u[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    char alpha_l[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    
    // loop through each character of the plaintext
    int text_len = strlen(text);
    for (int i = 0; i < text_len; i++)
    {
        if (isalpha(text[i]))
        {
            if ((int) text[i] < 91)
            {
                // plaintext[i] is uppercase
                // loop through uppercase letters to get the index
                for (int j = 0; j < 26; j++)
                {
                    if (text[i] == alpha_u[j])
                    {
                        // loop through the key
                        for (int k = 0; k < 26; k++)
                        {
                            if (j == k)
                            {
                                printf("%c", toupper(cipher_key[j]));
                            }
                        }
                    }
                }
            }
            else 
            {
                // plaintext[i] is lowercase
                // loop through uppercase letters to get the index
                for (int j = 0; j < 26; j++)
                {
                    if (text[i] == alpha_l[j])
                    {
                        // loop through the key
                        for (int k = 0; k < 26; k++)
                        {
                            if (j == k)
                            {
                                printf("%c", tolower(cipher_key[j]));
                            }
                        }
                    }
                }
            }
        }
        else
        {
            // not an alphabet
            printf("%c", text[i]);
        }
    }
}