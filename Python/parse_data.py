import pandas as pd
import matplotlib.pyplot as plt 

# Import the required Module
import tabula

# Read a PDF File
# make sure your pdf file is in the same directory as your notebook
df = tabula.read_pdf("C:\\Users\\amisi\\Downloads\\brokerage.pdf", pages='all')

# convert PDF into CSV
# tabula.convert_into("C:\\Users\\amisi\\Downloads\\brokerage.pdf", "C:\\Users\\amisi\\Downloads\\brokerage.csv", output_format="csv", pages='all')

for val in df:
    search_value = 'Transaction'
    result = val.eq(search_value).any()
    result
#print(df)


# file_path = "C:\\Users\\amisi\\Downloads\\brokerage.csv"
# df = pd.read_csv(file_path, on_bad_lines='skip')

# for column in df.columns:
#     print(df[column])
#     plt.figure()
#     plt.title(column)
#     plt.plot(df[column])
#     plt.show()