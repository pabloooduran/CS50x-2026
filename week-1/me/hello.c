#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string question = get_string("What's your name? ");
    printf("hello, %s\n", question);
}
