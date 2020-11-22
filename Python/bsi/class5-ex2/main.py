import os

kB = 1000
MB = 1000000


def create_files(files):
    for name in files:
        if not os.path.isfile(name):
            os.system(f'touch {name}')
    fill_files(files)


def fill_files(files):
    for name in files:
        size = files[name]

        if size == os.path.getsize(name):
            continue

        with open(name, 'w') as f:
            for i in range(0, size):
                f.write('x')


def do_hash(files, algorithms, file_result, hkeys):
    for name in files:
        for alg in algorithms:
            for hkey in hkeys:
                with open(file_result, 'a') as f:
                    f.write(f'key: "{hkey}"\n')
                cmd = f'openssl dgst -{alg} -hmac "{hkey}" {name} >> {file_result}'
                print(cmd)
                os.system(cmd)


def recreate_files(*files):
    for name in files:
        if not os.path.isfile(name):
            os.system(f'touch {name}')
        else:
            # Clear file
            open(name, 'w').close()


def main():
    file_result_hash = 'result-hash.txt'
    recreate_files(file_result_hash)

    files = {
        'test100kB.txt': 100 * kB
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
