# TODO

from cs50 import get_float

while True:
    cents = get_float("Change owed: ")
    if cents > 0:
        break

count = 0
while cents > 0:
    if cents >= 0.25:
        cents -= 0.25
        count += 1
    elif cents >= 0.10:
        cents -= 0.10
        count += 1
    elif cents >= 0.05:
        cents -= 0.05
        count += 1
    else:
        cents -= 0.01
        count += 1

print(count)