# TODO

from cs50 import get_float

while True:
    cents = get_float("Change owed: ")
    if cents > 0:
        break

count = 0
while cents > 0:
    if cents >= 0.25:
        print(cents)
        cents -= 0.25
        count += 1
    elif cents >= 0.10:
        print(cents)
        cents = (cents - 0.1)
        count += 1
    elif cents >= 0.05:
        print(cents)
        cents -= 0.05
        count += 1
    else:
        print(cents)
        cents -= 0.01
        count += 1

print(count)