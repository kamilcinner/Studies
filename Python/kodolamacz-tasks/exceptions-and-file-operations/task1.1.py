def main():
    proceed = True

    while proceed:
        proceed = False
        print("Enter the number, mathematical operation: +, -, *, /, %")
        print("in separate lines, followed by the next number:")
        try:
            a = float(input())
            operation = str(input())
            b = float(input())
        except ValueError as e:
            print(e)
            proceed = True
            continue

        if operation == "+":
            result = a + b
        elif operation == "-":
            result = a - b
        elif operation == "*":
            result = a * b
        elif operation == "/":
            try:
                result = a / b
            except ZeroDivisionError as e:
                print(e)
                proceed = True
                continue
        elif operation == "%":
            result = a % b
        else:
            print("Not valid mathematical operation provided! Program will stop execution.")
            return

        print("The result is: " + str(result))

        print("Would you like to compute another operation? Enter letter y or n.")
        decision = str(input())
        if decision == "y":
            proceed = True
        elif decision != "n":
            print("Not valid letter provided! Program will stop execution.")

if __name__ == "__main__":
    main()