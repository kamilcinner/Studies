def main():
    x = 7
    y = 3

    sum = x + y
    print("Addition: " + str(sum))

    diff = x - y
    print("Difference: " + str(diff))

    multiplication = x * y
    print("Multiplication: " + str(multiplication))

    division = x / y
    print("Division: " + str(division))

    rest = x % y
    print("Rest from dividing: " + str(rest))

    print(str(x) + " < " + str(y) + " == " + str(x < y))
    print(str(x) + " <= " + str(y) + " == " + str(x <= y))
    print(str(x) + " > " + str(y) + " == " + str(x > y))
    print(str(x) + " >= " + str(y) + " == " + str(x >= y))
    print(str(x) + " == " + str(y) + " == " + str(x == y))
    print(str(x) + " != " + str(y) + " == " + str(x != y))

    age = 35
    isWorkingAge = 18 <= age <= 65
    print(isWorkingAge)

    isWorkingAge = 18 <= age and age <= 65
    print(isWorkingAge)

    print("1 i 1: " + str(True and True))
    ## 1 i 1: True
    print("0 i 1: " + str(False and True))
    ## 0 i 1: False
    print("1 i 0: " + str(True and False))
    ## 1 i 0: False
    print("0 i 0: " + str(False and False))
    ## 0 i 0: False

    print("1 lub 1: " + str(True or True))
    ## 1 lub 1: True
    print("0 lub 1: " + str(False or True))
    ## 0 lub 1: True
    print("1 lub 0: " + str(True or False))
    ## 1 lub 0: True
    print("0 lub 0: " + str(False or False))
    ## 0 lub 0: False

    print("nie 1: " + str(not True))
    ## nie 1: False
    print("nie 0: " + str(not False))
    ## nie 0: True

    age = 19
    if age >= 21:
        print("a person can drink alcohol and have a weapon")
    elif age >= 18:
        print("a person can drink alcohol")
    else:
        print("a person cannot drink alcohol or carry a weapon")

    for i in range(0, 10):
        print(i)

    i = 0
    while i < 10:
        print(i)
        i += 1

    print("Enter number of grades that will fall into the averange:")
    numberOfGrades = int(input())
    sum = 0

    for i in range(1, numberOfGrades + 1):
        print("Enter grade " + str(i) + ":")
        grade = float(input())
        sum += grade

    print("Sum of the grades is " + str(sum))
    print("Averange grade is " + str(sum / numberOfGrades))

    print("Enter number of grades that will fall into the averange:")
    numberOfGrades = int(input())
    sum = 0

    i = 1
    while i <= numberOfGrades:
        print("Enter grade " + str(i) + ":")
        grade = float(input())
        if grade < 0:
            continue
        sum += grade
        i += 1

    print("Sum of the grades is " + str(sum))
    print("Averange grade is " + str(sum / numberOfGrades))

if __name__ == "__main__":
    main()