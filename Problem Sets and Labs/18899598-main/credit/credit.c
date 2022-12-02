#include <cs50.h>
#include<math.h>
#include <stdio.h>

int cal_length(long card_num);
int first_Digit(long card_num, int length);
int first_Two_Digit(long card_num, int length);


int main(void)
{
// Take input from user about card number
    long card_number = get_long("Enter credit card number\n");

    int length = cal_length(card_number);
    int odd_place_total = 0; // To calculate total of odd places in card number
    int even_place_total = 0;
    int check_sum;
    int first_digit = card_number / pow(10, length - 1);
    int first_two_digit = card_number / pow(10, length - 2);
    long temporary = card_number;

// Code for finding the CHECK-SUM
    for (int i = 1; i <= length; i++) // For each iteration "temporary" is reduced by one decimal to get the last digit
    {
        if (i % 2 == 1) //finding odd locations in CARD NUMBER
        {
            odd_place_total += temporary % 10 ; //directly add the digits at odd locations
            temporary /= 10;
        }
        else // finding even locations
        {
            if (temporary % 10 < 5) // if the multiplication by 2 resutls in single digit number
            {
                even_place_total += (temporary % 10) * 2;
                temporary /= 10;
            }
            else // if the multiplication by 2 resutls in two digit number add every digit separately
            {
                int temporary2 = (temporary % 10) * 2;
                even_place_total += temporary2 % 10;
                temporary2 /= 10;
                even_place_total += temporary2;
                temporary /= 10;
            }
        }
    }

    check_sum = odd_place_total + even_place_total; //Final CHECK SUM

    // Code for Checking validity of CARD NUMBER

    if (check_sum % 10 == 0)
    {
        //Check for VISA - 13 digit
        if (length == 13 && first_digit == 4)
        {
            printf("VISA\n");
            return 0;
        }
        //Check for AMEX - 15 digit
        else if (length == 15 && (first_two_digit == 34 || first_two_digit == 37))
        {
            printf("AMEX\n");
            return 0;
        }
        //Check for Visa - 16 digit
        else if (length == 16 && first_digit == 4)
        {
            printf("VISA\n");
            return 0;
        }
        //Check for MasterCard - 16 digit
        else if (length == 16 && (first_two_digit >= 51 && first_two_digit <= 55))
        {
            printf("MASTERCARD\n");
            return 0;
        }
        else
        {
            printf("INVALID\n");
            return 0;
        }
    }
    else
    {
        printf("INVALID\n");
        return 0;
    }

}

//Calculates the lgenth of CARD NUMBER
int cal_length(long card_num)
{
    int i = 1;
    do
    {
        card_num /= 10;
        i++;
    }
    while (card_num > 9);
    return i;
}

