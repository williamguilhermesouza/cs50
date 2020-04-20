
# getting card number
card_number = input("Number: ")

number_length = len(card_number)

card_array = list()

for digit in card_number:
    card_array.insert(0, int(digit))

# calculating the sum by luhn's algorithm
card_sum = 0

for i in range(1, number_length + 1):

    if i % 2 == 0:
        mpy_digit = 2 * card_array[i - 1]

        if mpy_digit < 10:
            card_sum += mpy_digit

        else:
            card_sum += mpy_digit % 10 + 1

    else:
        card_sum += card_array[i - 1]


# print the message that says which card number it is
# or if it is not a card number
if card_sum % 10 != 0:
    print("INVALID\n")

else:
    second_digit = card_array[-2]

    if second_digit > 0 and second_digit < 6:
        aux_verifier = 1

    else:
        aux_verifier = 0

    if card_array[-1] == 3 and number_length == 15 and (second_digit == 4 or second_digit == 7):
        print("AMEX\n")

    elif card_array[-1] == 5 and number_length == 16 and aux_verifier == 1:
        print("MASTERCARD\n")

    elif card_array[-1] == 4 and (number_length == 13 or number_length == 16):
        print("VISA\n")

    else:
        print("INVALID\n")

