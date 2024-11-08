#! /usr/bin/env python3

from pathlib import Path
import csv
import datetime

import numpy as np


# first value of db can not be more then 1000 i have no idea what to then...
def load_test_db2(path: Path, delim: str = ',') -> dict[datetime.date, np.float32]:
    """
    Load in the csv file, if we have missing date's we will add those.
    The value of it is the previous date in db.
    """

    db = {}

    with open(path, newline='') as csvfile:
        reader = csv.reader(csvfile, delimiter=delim)
        next(reader)  # Skip header
        for row in reader:
            date = datetime.datetime.strptime(row[0], '%Y-%m-%d').date()
            value = np.float32(float(row[1]))
            db[date] = value

    # Early return if empty
    if not db:
        return {}

    # Get date range
    dates = sorted(db.keys())
    start_date = dates[0]
    end_date = dates[-1]

    # Initialize result dictionary with all dates
    result = {}
    current_date = start_date

    # Fill all dates between start and end
    while current_date <= end_date:
        if current_date in db:
            # If current value is > 1000 and not the first entry,
            # use the previous day's value
            if db[current_date] > np.float32(1000) and current_date != start_date:
                result[current_date] = result[current_date -
                                              datetime.timedelta(days=1)]
            else:
                result[current_date] = db[current_date]
        else:
            # For missing dates, use the previous day's value
            result[current_date] = result[current_date -
                                          datetime.timedelta(days=1)]

        current_date += datetime.timedelta(days=1)

    return result


if __name__ == '__main__':
    load_test_db2(path=Path('db/data.csv'), delim=',')
