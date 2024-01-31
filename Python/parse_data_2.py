import csv
from collections import  defaultdict
import re
from dataclasses import dataclass
import pandas as pd
import matplotlib.pyplot as plt 

data = defaultdict(list)

file_path = r'C:\\Users\\amisi\\Downloads\\8091073b-9293-5d5e-902c-84f8bb11afb7.csv'

@dataclass
class DataPoint:
    date: str
    ticker: str
    quantity: float
    price: float = 0.0

def csv_analyzer():
    def to_float(x):
        return float(re.sub('[!@#$(),]', '', x))
    
    def read_file():
        with open(file_path,'rt') as f:
            rd = csv.DictReader(f)
            for row in rd:
                #print(row['Instrument'], row['Quantity'], row['Trans Code'], row['Price'])
                data[row['Instrument']].append(DataPoint(row['Activity Date'], row['Trans Code'], row['Quantity'], row['Price']))
                # for j in i.keys():
                #     print(j)
                    #data[j].append(i[j])

        df = pd.DataFrame.from_dict(data)
        print(df)

    read_file()

#print({k:v for k,v in data.items()})
csv_analyzer()