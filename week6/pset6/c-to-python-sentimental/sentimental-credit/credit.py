# TODO

# importing get_string function
from cs50 import get_string

number = get_string("Number: ")

lst = list()

# Multiply every 2nd digit from last by 2
for i in range(len(number) - 2, -1, -2):
    lst.append(str(int(number[i]) * 2))

sum = 0

# Finding the sum of all the digits of the numbers multiplied by 2
for item in lst:
    for c in item:
        sum += int(c)

# Adding the sum to the sum of remaining digits
for i in range(len(number) - 1, -1, -2):
    sum += int(number[i])

# Checking if the card is valid or not
if sum % 10 == 0:

    # Printing the name of card
    if number.startswith("4"):
        print("VISA")
    if number.startswith(("34", "37")):
        print("AMEX")
    if number.startswith(("51", "52", "53", "54", "55", "56")):
        print("MASTERCARD")
else:
    print("INVALID")