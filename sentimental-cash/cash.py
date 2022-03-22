# TODO

from cs50 import get_float

# Prompt user for input
while True:
    cents = get_float("Change owed: ")
    if cents > 0:
        break

count = 0

# Counting the number of coins required
while cents > 0:
    if cents >= 0.25:
        print(cents)
        cents = round(cents - 0.25, 2)
        count += 1
    elif cents >= 0.10:
        print(cents)
        cents = round(cents - 0.1, 2)
        count += 1
    elif cents >= 0.05:
        print(cents)
        cents = round(cents - 0.05, 2)
        count += 1
    else:
        print(cents)
        cents = round(cents - 0.01, 2)
        count += 1

# Printing the result 
print(count)