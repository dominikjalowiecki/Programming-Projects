from bokeh.plotting import figure, output_file, show
import json
from collections import Counter

with open('scientists_birthdays.json', 'r') as file:
    dict = json.load(file)

months = {1: 'January',
          2: 'February',
          3: 'March',
          4: 'April',
          5: 'May',
          6: 'June',
          7: 'July',
          8: 'August',
          9: 'September',
          10: 'October',
          11: 'November',
          12: 'December'}

tab = []

for val in dict.values():
    tab.append(months[int(val[3:5])])

c = Counter(tab)

output_file('plot.html')
x_cat = list(months.values())
x = list(c.keys())
y = list(c.values())

p = figure(
    title="Number of births for every month",
    x_axis_label="Months",
    x_range=x_cat,
    y_axis_label="Births"
)
p.vbar(x=x, top=y, width=0.9, fill_color="#ffff00")

show(p)