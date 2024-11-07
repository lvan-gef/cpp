import csv
from pathlib import Path


def all_bitcoin():
    with open('data/all_bitcoin.csv', 'r') as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            date, price = row
            yield date, price

