#include <cs50.h>
#include <stdio.h>

void print_space(int num);
void print_pound(int num);


int main(void)
{
    int height;
    //To get input from user for height between integers 1 to 8 only.
    do
    {
        height = get_int("Enter a number between 1 to 8 for Pyramid height\n");
    }
    while (height < 1 || height > 8);

    //printing the pyramid with given height
    for (int i = 1; i <= height ; i++)
    {
        print_space(height - i); //initial spaces for each line (decrease for each line)
        print_pound(i);  // initial "#" for each line (increase for each line)
        printf("  "); //Two space are present after end for left pyramid
        print_pound(i); // printing "#" for right pyramid (increase for each line)
        printf("\n"); // Move to next line after each line is completed
    }


}

// Printing " " with given number
void print_space(int num)
{
    for (int i = 0; i < num; i++)
    {
        printf(" ");
    }
}

// Printing "#" with given number.
void print_pound(int num)
{
    for (int i = 0; i < num; i++)
    {
        printf("#");
    }
}
