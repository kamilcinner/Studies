import datetime
import os


def main():
    print("Enter a path to folder:")
    folder_path = str(input())
    file_list = os.listdir(folder_path)
    for f in file_list:
        file_path = os.path.join(folder_path, f)
        (mode, ino, dev, nlink, uid, gid, size, atime, mtime, ctime) = os.stat(file_path)
        modification_time = datetime.datetime.fromtimestamp(mtime)
        time_diff = datetime.datetime.now() - modification_time
        if time_diff.days >= 0 and size > 1024 * 1024:
            print(f"Deleting file: {f}")
            os.remove(file_path)


if __name__ == "__main__":
    main()
