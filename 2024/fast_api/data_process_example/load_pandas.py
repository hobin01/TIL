import pandas
import sys 

def read_pandas(filename: str) -> pandas.DataFrame :
    data = pandas.read_csv(filename, sep="|")
    return data 

if __name__ == "__main__":
    data = read_pandas(sys.argv[1])
    print(data.head(5))