#include <stdio.h>
#include <cs50.h>

int main()
{
    //getting card number
    long card_number;
    card_number = get_long("Number: ");
    long size_counter = card_number;
    
    // loop to get size of the card number
    int number_length = 0;
    while (size_counter != 0) 
    {
        number_length++;
        size_counter /= 10;
    }
    
    int card_array[number_length];
    size_counter = card_number;
    
    // loop to turn the number into an array
    for (int i = 0; i < number_length; i++) 
    {
        card_array[i] = size_counter % 10;
        size_counter /= 10;
    }
    
    // calculating the sum by luhn's algorithm
    int card_sum = 0;
    int mpy_digit;
    for (int i = 1; i <= number_length; i++)
    {
        if (i % 2 == 0) 
        {
            mpy_digit = 2 * card_array[i - 1];
            
            if (mpy_digit < 10) 
            {
                card_sum += mpy_digit;
            }
            else 
            {
                card_sum += mpy_digit % 10 + 1;
            }
        }
        else
        {
            card_sum += card_array[i - 1];
        }
    }
    
    // print the message that says which card number it is
    // or if it is not a card number
    if (card_sum % 10 != 0) 
    {
        printf("INVALID\n");
    }
    else 
    {
        int second_digit = card_array[number_length - 2];
        
        int aux_verifier;
        if (second_digit > 0 && second_digit < 6) 
        {
            aux_verifier = 1;
        } 
        else 
        {
            aux_verifier = 0;
        }
        
        switch (card_array[number_length - 1])
        {
            case 3:
                
                if (number_length == 15) 
                {
                    if ((second_digit == 4) || (second_digit == 7)) 
                    {
                        printf("AMEX\n");
                    }
                    else 
                    {
                        printf("INVALID\n");
                    }
                }
                else 
                {
                    printf("INVALID\n");
                }
                break;
                
            case 5:
                
                if ((number_length == 16) && (aux_verifier == 1)) 
                {
                    printf("MASTERCARD\n");
                }
                else 
                {
                    printf("INVALID\n");
                }
                break;
               
            case 4:
                if ((number_length == 13) || (number_length == 16)) 
                {
                    printf("VISA\n");
                }
                else 
                {
                    printf("INVALID\n");
                }
                break;
                
            default:
                printf("INVALID\n");
        }
    }
    
}
