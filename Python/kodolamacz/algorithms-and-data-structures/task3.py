def main():
    print("Enter first word:")
    word1 = input()
    print("Enter second word:")
    word2 = input()
    print(isAnagram(word1, word2))

def isAnagram(word1 = "", word2 = ""):
    if len(word1) != len(word2):
        return False
    letters1 = {}
    letters2 = {}
    n = len(word1)
    for i in range(0, n):
        if word1[i] in letters1:
            letters1[word1[i]] += 1
        else:
            letters1[word1[i]] = 1

        if word2[i] in letters2:
            letters2[word2[i]] += 1
        else:
            letters2[word2[i]] = 1

if __name__ == "__main__":
    main()