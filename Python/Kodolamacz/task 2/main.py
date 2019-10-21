def main():
    proceed = True
    while proceed:
        print("Podaj w oddzielnych wierszach liczbę, operację matematyczną: +,-,*,/,%, a następnie kolejną liczbę:")

        a = float(input())
        operator = input()
        b = float(input())

        if operator == '+':
            wynik = a + b
        elif operator == '-':
            wynik = a - b
        elif operator == '*':
            wynik = a * b
        elif operator == '/':
            if b == 0:
                print("Nie mozna dzielic przez 0! Spróbuj ponownie...")
                continue
            wynik = a / b
        elif operator == '%':
            wynik = a % b
        else:
            print("Podano nieprawidłową operację arytmetyczną! Spróbuj ponownie...")
            continue

        print("Twój wynik to: " + str(wynik))

        proceedS = True
        while proceedS:
            proceedS = False
            print("Chcesz wykonać kolejne działanie? Wpisz literę t lub n.")
            choice = input()
            if choice == 'n':
                proceed = False
            elif choice != 't':
                print("Podano nieprawidlowy znak! Spróbuj ponownie...")
                proceedS = True


if __name__ == "__main__":
    main()
