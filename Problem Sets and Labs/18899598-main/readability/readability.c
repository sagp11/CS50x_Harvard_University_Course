#include <cs50.h>
#include <stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    //Getting input text from user
    string text = get_string("Text: ");

    // Counting words, letters, sentences
    float words = count_words(text);
    float letters = count_letters(text);
    float sentences = count_sentences(text);

    //Average letters and sentences per 100 words
    float L = letters / words * 100.00;
    float S = sentences / words * 100.00;

    // Applying Coleman-Liau formula
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int grade = (int) round(index);

    //Checking conditions for grades between 1 to 16
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
        printf("Grade %i\n", grade);
    }
    return 0;

}


//To count number of letters in the given text
//Consider only alphabets ignoring other symbols
int count_letters(string text)
{
    int letters = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }
    return letters;
}


//Counting number of words in the given text
//After each whitespace we declare a word is complete
int count_words(string text)
{
    int words = 0;
    for (int i = 0, n = strlen(text); i <= n; i++)
    {
        if (isspace(text[i]) || text[i] == '\0')
        {
            words++;
        }
    }
    return words;
}


//Counting number of sentences in the given text
//After each "." we declare a sentence is complete
int count_sentences(string text)
{
    int sentences = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (((int) text[i] == 46) || ((int) text[i] == 33) || ((int) text[i] == 63))
        {
            sentences++;
        }
    }
    return sentences;
}



