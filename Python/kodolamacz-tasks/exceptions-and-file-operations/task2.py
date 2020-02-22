def main():
    print("Enter read pile path:")
    read_file_path = str(input())
    try:
        with open(read_file_path) as f:
            rows = f.readlines()
            line_counter = len(rows)
            print(f"Lines number: {line_counter}")
            print("Enter save file path:")
            save_file_path = str(input())
            with open(save_file_path, 'w') as f:
                f.write(read_file_path + "\n" + str(line_counter))
    except FileNotFoundError:
        print("File not found!")


if __name__ == "__main__":
    main()
