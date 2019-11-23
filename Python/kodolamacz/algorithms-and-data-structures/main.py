def main():
    print("How many numbers do you want to enter?:")
    n = input()
    numbers = []
    for i in range(0, int(n)):
        print("Enter number [" + str(i) + "]:")
        k = input()
        numbers.append(k)
    print("Your mode is: " + str(mode(numbers)))

def mode(numbers):
    counterDB = {}
    for i in range(0, len(numbers)):
        k = numbers[i]
        if k in counterDB:
            counterDB[k] += 1
        else:
            counterDB[k] = 1
    max = 0
    maxNumber = "null"
    for i in range(0, len(numbers)):
        k = numbers[i]
        n = counterDB[k]
        if n > max:
            max = n
            maxNumber = k
    return maxNumber

if __name__ == "__main__":
    main()