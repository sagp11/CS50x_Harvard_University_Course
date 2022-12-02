#include<cs50.h>
#include<stdio.h>

int main(void)
{
    // To get name from user
    string name = get_string("What is your name? ");
    //Concatenating "hello" and name input by user
    printf("hello, %s\n", name);
}