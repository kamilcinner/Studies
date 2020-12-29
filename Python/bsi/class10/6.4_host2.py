import sys
import os
import datetime
import shutil


def main():
    host1_address = 'student@192.168.59.2'

    # Size must be MiB
    required_size = int(sys.argv[1])
    mode = sys.argv[2]

    date = datetime.datetime.now().strftime('%Y_%m_%d_%H_%M_%S')
    data_path = f'{host1_address}:/home/student/bsi/zad6.1/dane/'
    archive_base_dir = '/mnt/archiwum'
    archive_data_dir = f'{archive_base_dir}/archiwum_{date}'

    latest_link = f'{archive_base_dir}/latest'

    check_space(archive_base_dir, required_size)
    make_dir(archive_data_dir)

    if mode == 'incremental':
        mode = f'--link-dest {latest_link}'
    else:
        mode = ''

    cmd = f'sshpass -p student rsync -azp {mode} {data_path} {archive_data_dir}'
    os.system(cmd)

    if not check_fail(archive_data_dir):
        os.system(f'rm -rf {latest_link}')
        os.system(f'ln -s {archive_data_dir} {latest_link}')
    else:
        print('backup FAILED!!!')

    print_backups(archive_base_dir)
    get_free_space(archive_base_dir)


def check_fail(archive_data):
    if len(os.listdir(archive_data)) == 0:
        os.removedirs(archive_data)
        return True
    return False


def make_dir(archive_data):
    if not os.path.isdir(archive_data):
        os.system(f'mkdir {archive_data}')


def check_space(archive_base, size):
    free = get_free_space(archive_base)

    dirs = os.listdir(archive_base)
    dirs.sort()
    dir_index = 0

    while free < size:
        dir_to_delete = dirs[dir_index]
        print('removing oldest backups to free up space')
        shutil.rmtree(f'{archive_base}/{dir_to_delete}')
        print(f'removed: {dir_to_delete}')
        dir_index += 1
        free = get_free_space(archive_base)


def get_free_space(archive_base):
    total, used, free = shutil.disk_usage(archive_base)
    free //= 2**20
    print(f'free space available: {free} MiB')
    return free


def print_backups(archive_base):
    dirs = os.listdir(archive_base)
    if len(dirs) > 0:
        dirs.sort()
        print('all backups:')
        for dir in dirs:
            print(dir)
    else:
        print('no backups available')


if __name__ == "__main__":
    main()
