import csv
import sys 

def read_csv(filename: str) -> list[tuple]:
    with open(filename) as f :
        data = [row for row in csv.reader(f, delimiter="|")]
    return data 

if __name__ == "__main__":
    data = read_csv(sys.argv[1])
    for row in data[:5] :
        print(row)

