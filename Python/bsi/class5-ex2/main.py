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


def do_hash(files, algorithms, result_file_hash, hkeys):
    for key in files:
        name = files[key][0]
        for alg in algorithms:
            for hkey in hkeys:
                with open(result_file_hash, 'a') as f:
                    f.write(f'key: "{hkey}"\n')
                cmd = f'openssl dgst -{alg} -hmac "{hkey}" {name} >> {result_file_hash}'
                print(cmd)
                os.system(cmd)


def recreate_file(path):
    if not os.path.isfile(path):
        os.system(f'touch {path}')
    else:
        # Clear file
        open(path, 'w').close()


def main():
    file_result_hash = 'result-hash.txt'
    recreate_file(file_result_hash)

    files = {
        'file_test': ['test100kB.txt', 100 * kB]
    }
    algorithms = ['md5', 'sha256', 'sha1']
    keys = [
        'abcdefg',
        'fsdf34rgdfgdgd',
        'fsdfdfsdfsdf3434t3trgdfg',
        'dfgethjyj677i67iujtyj657u65u5j55jrtgeg'
    ]

    create_files(files)
    do_hash(files, algorithms, file_result_hash, keys)


if __name__ == "__main__":
    main()
