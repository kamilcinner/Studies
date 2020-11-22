import os

kB = 1000
MB = 1000000


def create_files(files):
    for key in files:
        name = files[key][0]
        if not os.path.isfile(name):
            os.system(f'touch {name}')
    fill_files(files)


def fill_files(files):
    for key in files:
        name = files[key][0]
        size = files[key][1]

        if size == os.path.getsize(name):
            continue

        with open(name, 'w') as f:
            for i in range(0, size):
                f.write('a')


def do_hash(files, algorithms, result_file_hash):
    for alg in algorithms:
        for key in files:
            name = files[key][0]
            cmd = f'openssl dgst -{alg} {name} >> {result_file_hash}'
            print(cmd)
            os.system(cmd)


def recreate_file(path):
    if not os.path.isfile(path):
        os.system(f'touch {path}')
    else:
        # Clear file
        open(path, 'w').close()


def change_bit_on_position_in_file(file, byte_pos, bit_pos):
    with open(file, 'r+b') as f:
        f.seek(byte_pos)
        byte = f.read(1)
        f.seek(byte_pos)
        byte_toggled = bytes([ord(byte) ^ int((pow(2, bit_pos)))])
        print(bin(ord(byte))[2:].zfill(8))
        print(bin(ord(byte) ^ int((pow(2, bit_pos))))[2:].zfill(8))
        f.write(byte_toggled)


def parse_hashes(file_result_hash, algorithms):
    hashes = {}
    hash_pair = []
    with open(file_result_hash, 'r') as f:
        for index, line in enumerate(f):
            got_pos = False
            current_hash = ''

            for char in line:
                if got_pos and char != '\n':
                    current_hash += char
                if (not got_pos) and char == ' ':
                    got_pos = True

            hash_pair.append(current_hash)

            if index % 2 == 1:
                hashes[f'{algorithms[index // 2]}'] = hash_pair
                hash_pair = []
    return hashes


def compare_hashes(hash_pairs, file_result):
    same = {}
    for key in hash_pairs:
        bit_same = 0
        pair = hash_pairs[key]
        print(pair)
        for i in range(0, len(pair[0])):
            for j in range(0, 4):
                bit_pos = int(pow(2, j))
                if (int(pair[0][i], 16) & bit_pos) == (int(pair[1][i], 16) & bit_pos):
                    bit_same += 1
        same[key] = bit_same

    with open(file_result, 'a') as f:
        for key in same:
            f.write(f'{key}: {same[key]}\n')
    print(same)


def main():
    file_result_hash = 'result_hash.txt'
    file_result_same = 'result_same.txt'
    recreate_file(file_result_hash)
    recreate_file(file_result_same)

    files = {
        'file_test': ['test100kB.txt', 100 * kB],
        'file_test_changed': ['test100kB-changed.txt', 100 * kB]
    }
    algorithms = ['md5', 'sha256']

    recreate_file(files['file_test_changed'][0])
    create_files(files)
    change_bit_on_position_in_file(files['file_test_changed'][0], 34, 5)
    do_hash(files, algorithms, file_result_hash)

    hashes = parse_hashes(file_result_hash, algorithms)
    compare_hashes(hashes, file_result_same)


if __name__ == "__main__":
    main()
