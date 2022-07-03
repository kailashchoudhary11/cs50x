# TODO
from cs50 import get_int

# prompt user for height
while True:
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break

# print the towers with given height
for i in range(height):
    print(" " * (height - 1 - i), end="")
    print("#" * (i + 1), end="  ")
    print("#" * (i + 1))