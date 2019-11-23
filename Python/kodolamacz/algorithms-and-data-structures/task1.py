# exponentiation

def main():
    print(effexp(9,103))

# exponent must be greater or equal 0
def effexp(base, exponent = 1):
    if exponent == 1:
        return base
    if exponent == 0:
        return 1

    result = effexp(base, exponent // 2)
    result *= result

    if exponent % 2 == 1:
        result *= base

    return result

if __name__ == "__main__":
    main()