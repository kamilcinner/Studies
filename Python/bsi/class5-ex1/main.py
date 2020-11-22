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


def do_hash(files, algorithms, result_file):
    for name in files:
        for alg in algorithms:
            cmd = f'openssl dgst -{alg} {name} >> {result_file}'
            print(cmd)
            os.system(cmd)


def do_time(files, algorithms):
    print('Calculating time...\nR-rotations')

    time = ''
    rotations = 10
    time_temp = 'temp.txt'
    # Get sys + user time in seconds
    time_format = '%S %U'

    calculated_time = {}

    for name in files:
        print(f'\n{name}')
        calculated_time[name] = {}
        for alg in algorithms:
            cmd = f'/bin/time -o {time_temp} -f "{time_format}" sh -c \''
            for i in range(0, rotations):
                cmd += f'openssl dgst -{alg} {name} > /dev/null; '
            cmd = cmd[:-2]
            cmd += '\''

            os.system(cmd)

            with open(time_temp) as f:
                # -1 to remove new line char
                time = f.readline()[:-1]
                print(f'{alg}\tsys user {rotations}R:\t{time}')

            time_pair = time.split(' ')

            seconds = float(time_pair[0]) + float(time_pair[1])
            seconds *= MB / rotations

            size = files[name]
            if size != 0:
                actual_time = seconds / size

                calculated_time[name][alg] = actual_time
                print(f'{alg}\t1MB average:\t{actual_time}s')

    os.system(f'rm {time_temp}')

    return calculated_time


def save_time_result_to_file(time, result_file):
    with open(result_file, 'w') as f:
        for name in time:
            for alg in time[name]:
                seconds = time[name][alg]
                f.write(f'{name}\t{alg} \t1MB average:\t{seconds:.6f}s\n')


def recreate_files(*files):
    for name in files:
        if not os.path.isfile(name):
            os.system(f'touch {name}')
        else:
            # Clear file
            open(name, 'w').close()


def main():
    file_result_hash = 'result-hash.txt'
    file_result_time = 'result-time.txt'
    recreate_files(file_result_hash, file_result_time)

    files_to_hash = {
        'empty.txt': 0,
        '1B.txt': 1,
        '100kB.txt': 100 * kB,
        '1MB.txt': MB,
        '20MB.txt': 20 * MB
    }
    algorithms = ['md5', 'sha1', 'sha256', 'sm3']

    create_files(files_to_hash)
    do_hash(files_to_hash, algorithms, file_result_hash)

    time = do_time(files_to_hash, algorithms)

    save_time_result_to_file(time, file_result_time)


if __name__ == "__main__":
    main()
