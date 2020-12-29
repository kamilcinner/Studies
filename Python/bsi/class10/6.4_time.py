import os


def main():
    rotations = 5
    file_result_time = 'result_time.txt'
    time_log = '/home/student/bsi/zad6.4/time.log'
    recreate_files(file_result_time, time_log)
    
    time = ''
    modes = {'local full': '', 'remote full': '', 'remote incremental': ''}

    # Temporal files
    if not os.path.isdir('temp'):
        os.system('mkdir temp')
    temp_time = './temp/temp_time.txt'

    # Get sys + user time in seconds
    time_format = '%e'

    for mode in modes:
        print(f'doing {mode} backup test')
        os.system(f'echo "\n{mode}" >> {time_log}')
        cmd = f'time -o {temp_time} -f "{time_format}" sh -c \''
        for i in range(0, rotations):
            if mode == 'local full':
                cmd += f'python3 /home/student/bsi/zad6.1/6.1.py >> {time_log}; '
            elif mode == 'remote full':
                cmd += f'python3 /home/student/bsi/zad6.4/6.4_host1.py full >> {time_log}; '
            else:
                cmd += f'python3 /home/student/bsi/zad6.4/6.4_host1.py incremental >> {time_log}; '
            
        cmd = cmd[:-2]
        cmd += '\''

        os.system(cmd)
        
        with open(temp_time) as f:
            # -1 to remove new line char
            time = f.readline()[:-1]

        seconds = float(time)

        modes[mode] = seconds / rotations

    # Perform clean
    os.system('rm -r temp')

    # Save result
    save_time_result_to_file(modes, file_result_time)


def save_time_result_to_file(time, result_file):
    with open(result_file, 'w') as f:
        for mode in time:
            seconds = time[mode]
            f.write(f'{seconds}s\t{mode}\n')


def recreate_files(*files):
    for name in files:
        if not os.path.isfile(name):
            os.system(f'touch {name}')
        else:
            # Clear file
            open(name, 'w').close()


if __name__ == "__main__":
    main()
