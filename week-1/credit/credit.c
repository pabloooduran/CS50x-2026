#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int get_length(long number);
int first_digits(long number, int number_digits);
int luhn(long number);

int main(void)
{
    long number = get_long("What's your credit card number? ");
    if (get_length(number) == 15 &&
     (first_digits(number, 2) == 34 || first_digits(number, 2) == 37) && luhn(number))
    {
        printf("AMEX\n");
    }
    else if (get_length(number) == 16 &&
     (first_digits(number, 2) >= 51 && first_digits(number, 2) <= 55) && luhn(number))
    {
        printf("MASTERCARD\n");
    }
    else if ((get_length(number) == 13 || get_length(number) == 16) &&
     first_digits(number, 1) == 4 && luhn(number))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

int get_length(long number)
{
    char text[20];
    sprintf(text, "%ld", number);
    int length = strlen(text);
    return length;
}

int first_digits(long number, int number_digits)
{
    int divisor = pow(10, number_digits);
    while (number >= divisor)
    {
        number /= 10;
    }
    return number;
}

int luhn(long number)
{
    char digits[20];
    sprintf(digits, "%ld", number);
    int count = 0;
    for (int i = (get_length(number) - 2); i >= 0; i -= 2)
    {
        int j = (digits[i] - '0');
        j *= 2;
        if (j > 9)
        {
            char second_digits[3];
            int division = j % 100;
            sprintf(second_digits, "%d", division);
            int second_count = 0;
            int second_length = strlen(second_digits);
            for (int k = 0; k < second_length; k++)
            {
                int l = (second_digits[k] - '0');
                second_count = l + second_count;
            }
            j = second_count;
        }
        count = j + count;
    }
    for (int i = (get_length(number) - 1); i >= 0; i -= 2)
    {
        int m = (digits[i] - '0');
        count = m + count;
    }
    if ((count % 10) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
