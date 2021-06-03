#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

float count_letters(string txt);
float count_words(string txt);
float count_sentences(string txt);
void coleman_index(float letter_count, float word_count, float sentence_count);

int main(void)
{
    // get the text from the user
    string text = get_string("Text: ");

    // all required metrics
    float letters = count_letters(text);
    float words = count_words(text);
    float sentences = count_sentences(text);

    // output no. of letters
    printf("\n%f %s\n", letters, "letter(s)");

    // output no. of words
    printf("%f %s\n", words, "word(s)");

    // output no. of sentences
    printf("%f %s\n", sentences, "sentence(s)");

    // output coleman liau index
    coleman_index(letters, words, sentences);
}


// custom functions

float count_letters(string txt)
{
    int letters_count = 0;

    // iterate through the text
    for (int i = 0; i < strlen(txt); i++)
    {
        // check whether txt[i] is a letter
        if (isalpha(txt[i]))
        {
            letters_count++;
        }
    }

    return letters_count;
}

float count_words(string txt)
{
    int word_count = 0;

    // iterate through the text
    for (int i = 0; i < strlen(txt); i++)
    {
        if (txt[i] == ' ')
        {
            word_count++;
        }
    }

    // adding 1 to counter act the fact that the last word isn't accounted for by this method
    return word_count + 1;
}

float count_sentences(string txt)
{
    int sentence_count = 0;

    // iterate through the text
    for (int i = 0; i < strlen(txt); i++)
    {
        if (txt[i] == '.' || txt[i] == '?' || txt[i] == '!')
        {
            sentence_count++;
        }
    }

    return sentence_count;
}

void coleman_index(float letter_count, float word_count, float sentence_count)
{
    float index;
    float L;
    float S;
    string result;

    L = (letter_count / word_count) * 100;
    S = (sentence_count / word_count) * 100;

    index = round((0.0588 * L) - (0.296 * S) - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", index);
    }
}