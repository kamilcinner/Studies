import os
import datetime
import shutil


def make_dirs(archive_base, archive_data):
    if not os.path.isdir(archive_base):
        os.system(f'mkdir {archive_base}')

    if not os.path.isdir(archive_data):
        os.system(f'mkdir {archive_data}')


def get_free_space(archive_base):
    total, used, free = shutil.disk_usage(archive_base)
    free //= 2**20
    print(f'free space available: {free} MiB')
    return free


def check_fail(archive_data):
    if len(os.listdir(archive_data)) == 0:
        os.removedirs(archive_data)


def check_space(archive_base):
    free = get_free_space(archive_base)

    dirs = os.listdir(archive_base)
    dirs.sort()
    dir_index = 0

    while free < 30:
        dir_to_delete = dirs[dir_index]
        print('removing oldest backups to free up space')
        shutil.rmtree(f'{archive_base}/{dir_to_delete}')
        print(f'removed: {dir_to_delete}')
        dir_index += 1
        free = get_free_space(archive_base)


def print_backups(archive_base):
    dirs = os.listdir(archive_base)
    if len(dirs) > 0:
        dirs.sort()
        print('all backups:')
        for dir in dirs:
            print(dir)
    else:
        print('no backups available')


def main():
    date = datetime.datetime.now().strftime('%Y_%m_%d_%H_%M_%S')
    archive_base = '/mnt/archiwum'
    data = '~/bsi/zad6.1/dane/'
    archive_data = f'{archive_base}/archiwum_{date}'

    check_space(archive_base)
    make_dirs(archive_base, archive_data)

    # -p to preserve permissions
    cmd = f'rsync -azp {data} {archive_data}'
    os.system(cmd)

    check_fail(archive_data)
    print_backups(archive_base)
    get_free_space(archive_base)


if __name__ == "__main__":
    main()
