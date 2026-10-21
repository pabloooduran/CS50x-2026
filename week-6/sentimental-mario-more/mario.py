while True:
    try:
        height = int(input("Height: "))
        if 1 <= height <= 8:
            break
    except ValueError:
        print("Introduce a number")

for j in range(1, height + 1):
    print((" " * (height - j)) + ("#" * j) + "  " + ("#" * j))
