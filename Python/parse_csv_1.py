import pandas as pd
import matplotlib.pyplot as plt 
from decimal import Decimal
from collections import defaultdict
from dataclasses import dataclass
import re

file_path = "C:\\Users\\amisi\\Downloads\\8091073b-9293-5d5e-902c-84f8bb11afb7.csv"
df = pd.read_csv(file_path, on_bad_lines='skip')

@dataclass
class DataPoint:
    buy: float = 0.0
    sell: float = 0.0

def csv_analyzer():
    def to_float(x):
        return float(re.sub('[!@#$(),]', '', x))

    def filter_trans_data(df):
        options = ['Buy', 'Sell'] 
        df = df[df['Trans Code'].isin(options)] 

        return df
    
    def plot_graph(df):
        df['Amount'].plot()
        plt.show()

    def iterate_rows(df):
        ticker = df['Instrument']
        buys = df.loc[df['Trans Code'] == 'Buy', 'Amount'].sum()
        sells = df.loc[df['Trans Code'] == 'Sell', 'Amount'].sum()

        return (ticker, buys, sells)
    
    def preprocess_group(df):
        df = df[["Activity Date", "Instrument", "Trans Code", "Quantity", "Price", "Amount"]]
        amount_col = df['Amount']
        amount_col = amount_col.apply(to_float)
        df['Amount'] = amount_col

        return df

    def process_all_groups(df):
        data = defaultdict(dict)
        for i, g in df.groupby(['Instrument']):
            df = preprocess_group(g)
            (ticker, buys, sells) = iterate_rows(df)
            ticker_name = ticker.to_string(index=False).split('\n')[0]
            data[ticker_name] = DataPoint(buys, sells);
    
        cols = ['Buy','Sell']
        new_df = pd.DataFrame.from_dict(data, orient='index', columns=cols)

        return data

    def process_data(df):
        df = filter_trans_data(df)
        out = process_all_groups(df)

        for k, v in out.items():
            print("{:<8} {:<15} {:<10}".format(k, v.buy, v.sell))

    process_data(df)

csv_analyzer()