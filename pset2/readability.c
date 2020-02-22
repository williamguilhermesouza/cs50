# include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>

int count_letters(char text[]);
int count_words(char text[]);
int count_sentences(char text[], int word_count);
float coleman_liau(int letter_count, int word_count, int sentence_count);


int main(void)
{
    int letters, words, sentences;
    string input = get_string("Text: ");

    letters = count_letters(input);
    words = count_words(input);
    sentences = count_sentences(input, words);
    float grade = coleman_liau(letters, words, sentences);

    printf("%f", grade);

    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %.0f\n", round(grade));
    }

}

int count_letters(char text[])
{
    int counter = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        int letter = tolower(text[i]);
        if (letter >= 'a' && letter <= 'z')
        {
            counter++;
        }
    }

    return counter;
}

int count_words(char text[])
{
    int counter = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ' && text[i - 1] != ' ')
        {
            counter++;
        }

    }

    if (counter != 0)
    {
        counter++;
    }

    return counter;
}

int count_sentences(char text[], int word_count)
{
    int counter = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            counter++;
        }
    }

    if (counter == 0 && word_count != 0)
    {
        counter++;
    }

    return counter;
}

float coleman_liau(int letter_count, int word_count, int sentence_count)
{
    float L; // average number of letters per 100 words in the text
    float  S; // average number of sentences per 100 words in the text

    L = letter_count * 100.0 / word_count;
    S = sentence_count * 100.0 / word_count;


    float index = 0.0588 * L - 0.296 * S - 15.8;
    return index;
}