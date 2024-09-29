from tabulate import tabulate
import sys 
import csv 

def read_csv(filename: str) -> list[tuple]:
    with open(filename) as f :
        data = [row for row in csv.reader(f, delimiter="|")]
    return data 

if __name__ == "__main__":
    data = read_csv(sys.argv[1])
    print(tabulate(data[:5]))