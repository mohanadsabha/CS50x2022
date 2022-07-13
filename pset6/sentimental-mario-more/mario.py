# TODO

# Take input from user and chck that is an int
while True:
    try:
        num = int(input("Height: "))
        if num >= 1 and num <= 8:
            break
    except ValueError:
        print("this is not an int!")

# print the struct
for i in range(1, num+1):
    print(" " * (num - i), end="")
    print("#" * i, end="  ")
    print("#" * i)