#! /usr/bin/env python3

from pathlib import Path
import csv
import datetime

import numpy as np

def load_test_db2(path: Path, delim: str = ',') -> dict[datetime.date, np.float32]:
    """
    Load in the csv file, if we have missing dates we will add those.
    For any missing date, use the last available value from the database.
    """
    db = {}

    with open(path, newline='') as csvfile:
        reader = csv.reader(csvfile, delimiter=delim)
        next(reader)  # Skip header
        for row in reader:
            date = datetime.datetime.strptime(row[0], '%Y-%m-%d').date()
            value = np.float32(float(row[1]))
            db[date] = value

    if not db:
        return {}

    dates = sorted(db.keys())
    start_date = dates[0]
    end_date = dates[-1]

    result = {}
    current_date = start_date
    last_value = db[start_date]

    while current_date <= end_date:
        if current_date in db:
            result[current_date] = db[current_date]
            last_value = db[current_date]
        else:
            result[current_date] = last_value

        current_date += datetime.timedelta(days=1)

    return result


if __name__ == '__main__':
    load_test_db2(path=Path('db/data.csv'), delim=',')
