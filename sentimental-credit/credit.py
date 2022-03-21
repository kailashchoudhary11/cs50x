from cs50 import get_string
number = get_string("Number: ")
lst = list()
for i in range(len(number) - 2, -1, -2):
    lst.append(str(int(number[i]) * 2))

sum = 0

for item in lst:
    for c in item:
        sum += int(c)

for i in range(len(number) - 1, -1, -2):
    sum += int(number[i])

if sum % 10 == 0:
    if number.startswith("4"):
        print("VISA")
    if number.startswith(("34", "37")):
        print("AMEX")
    if number.startswith(("51", "52", "53", "54", "55", "56")):
        print("MASTERCARD")
else:
    print("INVALID")