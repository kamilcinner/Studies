def compress_dna(dna):
    temp = dna[0]
    counter = 0
    cdna = ""
    for l in dna:
        if temp == l:
            counter += 1
        else:
            cdna += temp + str(counter)
            temp = l
            counter = 1
    cdna += temp + str(counter)
    return cdna


def main():
    t1 = "aaaabbccddefg"
    t2 = "ftgdfddggdfhwbaucudsadsdssssssdsaduhfsdfsddfsffrrrrrr"

    print(compress_dna(t1))
    print(compress_dna(t2))


if __name__ == "__main__":
    main()
