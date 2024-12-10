import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.dates as mdates
import math
import re
import os
import sys

if len(sys.argv) < 3:
    data_path = "data"
    plots_path = "plots"
else:
    data_path = sys.argv[1]
    plots_path = sys.argv[2]

if data_path[-1] == '/':
    data_path = data_path[:-1]

if plots_path[-1] == '/':
    plots_path = plots_path[:-1]

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
                create_histogram(data_path + "/" + file)
            else:
                process_file(data_path + "/" + file)

# Process one file, creating two plots
def process_file(filename):
    # Load the CSV file
    file_path = filename[5:-4]  # Update with actual file path
    data = pd.read_csv(filename, delimiter=';')

    # Convert date and time into a single datetime column
    data['datetime'] = pd.to_datetime(data['date'] + ' ' + data['time'], format='%d-%m-%Y %H:%M:%S')

    # Extract description, frequency, and duration for the title and subtitle
    description = data['description'].iloc[0].capitalize().replace("-", " ")
    frequency = data['frequency'].iloc[0]
    duration = data['duration_s'].iloc[0]

    # First plot: Original data
    title = file_path[:-4].capitalize().replace("-", " ")
    subtitle = f"Frequency: {frequency}Hz, Duration: {duration}s"
    create_plot(file_path, data, title, subtitle)

    data_no_outliers = data.copy()
    for col in ['min', 'max', 'avg']:
        data_no_outliers = remove_outliers(data_no_outliers, col)

    # Second plot: Without outliers
    create_plot(file_path, data_no_outliers, title, subtitle, outliers_removed=True)

# Plot with and without outliers
def create_plot(filename, data, title, subtitle, outliers_removed=False):
    plt.subplots_adjust(hspace=0.5)
    fig, axs = plt.subplots(3, 1, figsize=(12, 9))

    myFmt = mdates.DateFormatter('%H:%M\n%d-%m')

    metrics = ['min', 'max', 'avg']
    colors = ['blue', 'red', 'green']
    labels = ['Min', 'Max', 'Avg']
    # plt.title(title, fontsize=16)

    for i, (metric, color, label) in enumerate(zip(metrics, colors, labels)):
        axs[i].xaxis.set_major_formatter(myFmt)
        axs[i].plot(data['datetime'], data[metric], label=label, color=color, alpha=0.7, linewidth=0.9)
        # axs[i].set_title(f"{label} Values", fontsize=14)
        axs[i].set_ylabel('Values', fontsize=12)
        axs[i].grid(True, linestyle='--', alpha=0.5)
        axs[i].legend()

    axs[-1].set_xlabel('Datetime', fontsize=12)
    # axs[0].set_title(title, fontsize=18)
    # plt.xticks()

    # Add subtitle with frequency and duration
    plt.suptitle(subtitle, fontsize=10)

    # File name adjustment based on outliers condition
    suffix = '_no_outliers' if outliers_removed else ''

    fig.tight_layout(pad=2.0)
    plt.savefig(f'{plots_path}/{filename}{suffix}.png')
    plt.close()

def create_histogram(filename):
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
        plt.figure(figsize=(8, 5))
        # plt.title(f"{title}")
        plt.imshow(data_array, cmap='coolwarm')
        plt.colorbar()
        plt.savefig(f'{plots_path}/{filename[5:-4]}_{name}.png')

# Removing outliers for the second plot
def remove_outliers(df, column):
    Q1 = df[column].quantile(0.25)
    Q3 = df[column].quantile(0.75)
    IQR = Q3 - Q1
    return df[(df[column] >= Q1 - 1.5 * IQR) & (df[column] <= Q3 + 1.5 * IQR)]

if __name__ == "__main__":
    main()
