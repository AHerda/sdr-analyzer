import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.dates as mdates
from datetime import datetime
import math
import re
import os

data_path = "data/"

def main():
    files = []

    for path in os.scandir(data_path):
        if path.is_file():
            files.append(path.name)

    print(files)

    for file in files:
        if re.search(".csv$", file):
            print(f"processing: {file}")
            if re.search("heatmap", file):
                create_heatmap(data_path + file)

def normalize(data):
    data2 = data[~np.isnan(data)]
    maximum = np.max(data2)
    minimum = np.min(data2)
    value_range = maximum - minimum

    data = (data - minimum) / value_range

    return data

def create_heatmap(filename):
    data = pd.read_csv(filename, delimiter=';')
    frequency = data['frequency'].iloc[0]

    title = filename[5:-4].capitalize().replace("-", " ")
    subtitle = f"Frequency: {frequency}Hz"

    data['row'] = data['description'].str.extract(r'x(\d)')[0].astype(int)
    data['col'] = data['description'].str.extract(r'(\d)x')[0].astype(int)

    max_row = data['row'].max() + 1
    max_col = data['col'].max() + 1

    counters = np.full((max_row, max_col), 0)
    avgs = np.full((max_row, max_col), float('nan'))
    mins = np.full((max_row, max_col), float('nan'))
    maxs = np.full((max_row, max_col), float('nan'))

    for _, row in data.iterrows():
        r, c = row['row'], row['col']
        for data_array, name in [(avgs, "avg"), (mins, "min"), (maxs, "max")]:
            if math.isnan(data_array[r, c]):
                data_array[r, c] = 0
            data_array[r, c] += row[name]
            counters[r, c] += 1

    for r in range(max_row):
        for c in range(max_col):
            avgs[r, c] /= counters[r, c]
            mins[r, c] /= counters[r, c]
            maxs[r, c] /= counters[r, c]

    for data_array, name in [(avgs, "avgs"), (mins, "mins"), (maxs, "maxs")]:
        data_array = normalize(data_array)

        plt.figure(figsize=(8, 5))
        # plt.title(f"{title}")
        plt.imshow(data_array, cmap='coolwarm')
        plt.colorbar()
        plt.savefig(f'plots3/{filename[5:-4]}_{name}_mynorm.png')

if __name__ == "__main__":
    main()
