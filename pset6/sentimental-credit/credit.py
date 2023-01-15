from cs50 import get_int

while True:
    cardnumber = get_int("Number: ")
    if cardnumber > 0:
        break
counter = 0
total = 0
pre = 0
after = 0
final = 0
firstdiget = 0
visadiget = 0
diget = 0
while cardnumber > 0:
    diget = cardnumber % 10
    cardnumber = cardnumber // 10
    counter += 1
    if counter % 2 == 0:
        pre = diget * 2
        if pre > 9:
            after = pre % 10
            pre = pre // 10
            final = pre + after
            total = total + final
        else:
            total = total + pre
    if cardnumber > 10 and cardnumber < 100:
        firstdiget = cardnumber
        visadiget = cardnumber // 10
    if counter % 2 == 1:
        total = total + diget
if counter == 16 and (firstdiget == 51 or firstdiget == 52 or firstdiget == 53 or firstdiget == 54 or firstdiget == 55) and total % 10 == 0:
    print("MASTERCARD")
elif (counter == 13 or counter == 16) and visadiget == 4 and total % 10 == 0:
    print("VISA")
elif counter == 15 and (firstdiget == 34 or firstdiget == 37) and total % 10 == 0:
    print("AMEX")
else:
    print("INVALID")

