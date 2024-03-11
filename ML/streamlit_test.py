import streamlit as st

# Create a title
st.title("My Streamlit App")

# Write some text
st.write("This is my first Streamlit app!")

# Display a number
st.write(10)

# Display a plot
import numpy as np
x = np.linspace(0, 10, 100)
y = np.sin(x)
st.line_chart(y)