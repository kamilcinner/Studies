import os

kB = 1000
MB = kB * kB

openssl = '~/Downloads/openssl-1.0.1p/apps/openssl'


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


def do_time(source_files, algorithms, operations):
    print('Calculating time...\nR-rotations')

    rotations = 100
    time = ''
    calculated_time = {}

    # Temporal files
    if not os.path.isdir('temp'):
        os.system('mkdir temp')
    temp_time = './temp/temp_time.txt'
    temp_out = './temp/temp_out.txt'
    
    # Get sys + user time in seconds
    time_format = '%S %U'

    for name in source_files:
        print(f'\n{name}')
        calculated_time[name] = {}
        for alg in algorithms:
            calculated_time[name][alg] = {}
            for operation in operations:
                cmd = f'time -o {temp_time} -f "{time_format}" sh -c \''

                key_type = 'public'
                is_public = '-pubin'
                file_in = name
                file_out = f'./temp/{alg}.encrypted.{name}'

                if operation == 'decrypt':
                    key_type = 'private'
                    is_public = ''
                    file_in = file_out
                    file_out = temp_out

                for i in range(0, rotations):
                    if alg[:3] == 'rsa':
                        key_file = f'./keys/{key_type}.{alg[3:]}.key'

                        cmd += f'{openssl} rsautl -in {file_in} -out {file_out} {is_public} -inkey {key_file} -{operation} 2> /dev/null; '
                    else:
                        key = '0123456789abcdef'
                        op_type = operation[0]
    
                        cmd += f'{openssl} enc -{alg} -{op_type} -in {file_in} -out {file_out} -K {key} -iv {key} 2> /dev/null; '
                cmd = cmd[:-2]
                cmd += '\''
    
                os.system(cmd)
    
                with open(temp_time) as f:
                    # -1 to remove new line char
                    time = f.readline()[:-1]
    
                time_pair = time.split(' ')
    
                try:
                    seconds = float(time_pair[0]) + float(time_pair[1])
                    size = source_files[name]
    
                    bytes_ps = calculate_k_bytes_per_sec(seconds, size, rotations)
                    calculated_time[name][alg][operation] = bytes_ps
    
                    print(f'{operation}\t{alg}\tsys user {rotations}R:\t{time}')
                    print(f'{operation}\t{alg}\tkBps:\t\t{bytes_ps:.3f}')
                except ValueError:
                    calculated_time[name][alg][operation] = 'error'
                    print(f'{operation}\t{alg}\tsys user {rotations}R:\terror')
                    print(f'{operation}\t{alg}\tkBps:\t\terror')

    # Perform clean
    os.system('rm -r temp')

    return calculated_time


def calculate_k_bytes_per_sec(seconds, size, rotations):
    one_rotation_time = seconds / rotations
    return (size / one_rotation_time) / float(kB)


def save_time_result_to_file(time, result_file):
    with open(result_file, 'w') as f:
        for name in time:
            for alg in time[name]:
                for operation in time[name][alg]:
                    seconds = time[name][alg][operation]
                    if type(seconds) == float:
                        seconds = f'{seconds:.3f}'
                    f.write(f'{name}  \t{operation}\t{alg}\tkBps:\t{seconds}\n')


def recreate_files(*files):
    for name in files:
        if not os.path.isfile(name):
            os.system(f'touch {name}')
        else:
            # Clear file
            open(name, 'w').close()


def calculate_average(time, algorithms, operations):
    average = {}
    for alg in algorithms:
        average[alg] = {}
        for operation in operations:
            alg_sum = .0
            alg_count = 0
            for file in time:
                try:
                    alg_sum += float(time[file][alg][operation])
                    alg_count += 1
                except ValueError:
                    break
            if alg_count > 0:
                average[alg][operation] = alg_sum / alg_count
            else:
                average[alg][operation] = 'error'
    return average


def save_average_to_file(average, result_file):
    with open(result_file, 'w') as f:
        for alg in average:
            for operation in average[alg]:
                k_bytes_ps = average[alg][operation]
                if type(k_bytes_ps) == float:
                    k_bytes_ps = f'{k_bytes_ps:.3f}'
                f.write(f'{operation}\t{alg}\tkBps:\t{k_bytes_ps}\n')


def main():
    file_result_time = 'result-time.txt'
    file_result_average = 'result-average.txt'
    recreate_files(file_result_time, file_result_average)

    files = {
        '16B.txt': 16,
        '100kB.txt': 100 * kB,
        '5MB.txt': 5 * MB
    }
    algorithms = ['rsa1024', 'rsa2048', 'rsa4096', 'aes128', 'des3']
    operations = ['encrypt', 'decrypt']

    create_files(files)

    time = do_time(files, algorithms, operations)
    save_time_result_to_file(time, file_result_time)

    average = calculate_average(time, algorithms, operations)
    save_average_to_file(average, file_result_average)


if __name__ == "__main__":
    main()
