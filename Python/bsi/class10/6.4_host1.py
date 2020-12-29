import os
import sys
import subprocess
from pathlib import Path

def main():
    host2_address = 'kamil@192.168.59.4'

    # Mode 'full' or 'incremental'
    mode = sys.argv[1]
    if not check_mode(mode):
        print('bad mode provided')
        exit()

    data_path = '/home/student/bsi/zad6.1/dane'
    
    # Get size of data to backup in MiB
    root_directory = Path(data_path)
    size = sum(f.stat().st_size for f in root_directory.glob('**/*') if f.is_file()) // (2**20  )
    print(f'data size: {size}MiB')

    cmd = f'sshpass -p student ssh {host2_address} python3 /home/kamil/bsi/zad6.4/main_host2.py {size} {mode}'
    os.system(cmd)


def check_mode(mode):
    return mode in ['full', 'incremental']


if __name__ == "__main__":
    main()
