def main():
    print("Enter first word:")
    word1 = input()
    print("Enter second word:")
    word2 = input()
    print(isAnagram(word1, word2))

def isAnagram(word1 = "", word2 = ""):
    if len(word1) != len(word2):
        return False
    letters1 = []
    letters2 = []
    n = len(word1)
    for i in range(0, n):
        letters1.append(word1[i])
        letters2.append(word2[i])
    letters1.sort()
    letters2.sort()
    if letters1 != letters2:
        return False
    return True

if __name__ == "__main__":
    main()