# exponentiation

def main():
    print(exp(9,103))

# exponent must be greater than 0
def exp(base, exponent = 1):
    if exponent == 1:
        return base

    result = exp(base, int(exponent / 2))
    result *= result

    if exponent % 2 == 1:
        result *= base

    return result

if __name__ == "__main__":
    main()