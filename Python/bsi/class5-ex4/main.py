import os
import random


def generate_text(length):
    chars = ['a', 'b', 'c', 'd', 'e', 'f', 'g', ' ', 'l', 'm', 'k', 'o', 't']
    string = ''
    for i in range(0, length):
        string += random.choice(chars)
    return string


def do_hash(text, algorithm):
    cmd = f'echo "{text}" > temp-source.txt'
    os.system(cmd)
    cmd = f'openssl dgst -{algorithm} temp-source.txt >> temp-hash.txt'
    os.system(cmd)
    _hash = parse_hash()
    os.system('rm temp*')
    return _hash


def parse_hash():
    _hash = ''
    got_pos = False
    with open('temp-hash.txt', 'r') as f:
        for line in f:
            for char in line:
                if got_pos and char != '\n':
                    _hash += char
                if (not got_pos) and char == ' ':
                    got_pos = True

    return _hash[:3]


def main():
    source_text = 'a'
    algorithm = 'md5'
    count = 0
    source_hash = do_hash(source_text, algorithm)
    while True:
        count += 1
        text = generate_text(len(source_text))
        new_hash = do_hash(text, algorithm)
        if source_hash == new_hash:
            break
    print(count)


if __name__ == "__main__":
    main()
