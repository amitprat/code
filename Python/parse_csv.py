import pandas as pd
import matplotlib.pyplot as plt 
from decimal import Decimal
import re

file_path = "C:\\Users\\amisi\\Downloads\\8091073b-9293-5d5e-902c-84f8bb11afb7.csv"
df = pd.read_csv(file_path, on_bad_lines='skip')

options = ['Buy', 'Sell'] 
rslt_df = df[df['Trans Code'].isin(options)] 
#print(rslt_df)

for i, g in rslt_df.groupby(['Instrument']):
    ticker_df = g

    ticker_df_filters = ticker_df[["Activity Date", "Instrument", "Trans Code", "Quantity", "Price", "Amount"]]

    amount_col = ticker_df_filters['Amount']
    new_age_column = amount_col.apply(to_float)
    amount_col = re.sub('[(){}<>]$', '', amount_col)
    ticker_df_filters['Amount'] = amount_col

    print(ticker_df_filters)

    x = [] 
    y = []

    for index, row in ticker_df_filters.iterrows():
        #dollars_dec = re.sub('[(){}<>]$', '', row['Amount'])
        #row['Amount'] = dollars_dec

        print(row)

        # row['Amount'].plot()
        # plt.show()

    # ticker_df_filters.set_index('Activity Date').plot()
    # plt.show()



    # for row in ticker_df_filters: 
    #     x.append(row[0]) 
    #     dollar_amount = row[5]
    #     dollars_dec = re.sub('[(){}<>]$', '', dollar_amount)
    #     y.append(dollars_dec) 

    # plt.bar(x, y, color = 'g', width = 0.72, label = "Amount") 
    # plt.xlabel('Activity Date') 
    # plt.ylabel('Amount') 
    # plt.title(ticker_df_filters['Instrument']) 
    # plt.legend() 
    # plt.show() 

    break

# for column in df.columns:
#     print(df[column])
#     plt.figure()
#     plt.title(column)
#     plt.plot(df[column])
#     plt.show()

def to_float(x):
    return float(re.sub('[(){}<>]$', '', x))