def main():
    print("Enter the word to check if it's palindrome:")
    myWord = input()
    print(isPalindrome(myWord))

def isPalindrome(word = ""):
    n = len(word)
    for i in range(0, n // 2):
        if word[i] != word[n - 1 - i]:
            return False
    return True

if __name__ == "__main__":
    main()