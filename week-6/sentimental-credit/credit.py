number = input("What's your credit card number? ")


def luhn(number):
    count = 0
    for i in range(len(number) - 2, -1, -2):
        j = int(number[i])
        j *= 2
        if j > 9:
            division = j % 100
            division = str(division)
            second_count = 0
            for k in range(len(division)):
                l = int(division[k])
                second_count += l
            j = second_count
        count += j
    for m in range(len(number) - 1, -1, -2):
        n = int(number[m])
        count += n
    if (count % 10) == 0:
        return True
    else:
        return False


if len(number) == 15 and (number[:2] == "34" or number[:2] == "37") and luhn(number):
    print("AMEX")
elif len(number) == 16 and 51 <= int(number[:2]) <= 55 and luhn(number):
    print("MASTERCARD")
elif (len(number) == 13 or len(number) == 16) and number[0] == "4" and luhn(number):
    print("VISA")
else:
    print("INVALID")
