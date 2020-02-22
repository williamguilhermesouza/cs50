#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int size;
    do 
    {
        size = get_int("Height: ");
    }
    while(size < 1 || size > 8);
    
    // initializing variables
    int l, p, spaces, i;
    
    // outer loop of the piramid
    for (l = 1; l <= size; l++) 
    {
        spaces = size - l; //calculating spaces
        
        //spaces loop
        for (i = 1; i <= spaces; i++)
        {
            printf(" ");
        }
        
        // first column loop
        for (p = 0; p < l; p++) 
        {
            printf("#");
        }
        printf("  "); // space between piramids
        
        // second column loop
        for (p = 0; p < l; p++)
        {
            printf("#");
        }
        printf("\n"); // go to the piramid next line
    }
}
