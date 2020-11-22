import os
import random


def generate_text(length):
    chars = [
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
        'm', 'n', 'o', 'p', 'r', 's', 't', 'u', 'w', 'z', 'x', 'v'
    ]
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


def break_hash(source_hash, source_text, algorithm, max_try_count, _property='irreversibility'):
    count = 0
    text = ''
    while count < max_try_count:
        count += 1

        text = generate_text(len(source_text))
        if (_property == 'collision' and text == source_text) or \
                (_property == 'irreversibility' and text != source_text):
            continue

        new_hash = do_hash(text, algorithm)
        if source_hash == new_hash:
            break

    result = None
    if count < max_try_count:
        result = {
            'message': f'{_property} broken on {count} try by \'{text}\'',
            'try': count
        }

    return result


def main():
    source_text = 'ala'
    algorithm = 'md5'
    source_hash = do_hash(source_text, algorithm)
    success_count = 0

    tries = 1000
    max_try_count = 10000
    try_counter = 0

    print(f'original: \'{source_text}\'\n')
    for i in range(1, tries + 1):
        result = break_hash(source_hash, source_text, algorithm, max_try_count)
        if result:
            success_count += 1
            print(f'{i} - {result["message"]}')
            try_counter += result['try']

    percent_success = success_count * (100 / tries)
    average_tries = try_counter // success_count

    print(f'\nSuccess rate: {percent_success}%')
    print(f'Average tries: {average_tries}')


if __name__ == "__main__":
    main()
