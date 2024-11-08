from pathlib import Path
import csv
import datetime

import numpy as np


# for debug check if every day is increased by 1
def _check_increasing_order(date_list: list[datetime.date]):
    prev_date = None

    for date_str in date_list:
        date = datetime.datetime.fromisoformat(str(date_str))
        if prev_date is not None:
            diff = date - prev_date
            if diff.days != 1:
                print(prev_date, date)
                return False
        prev_date = date

    return True


def load_test_db(path: Path, delim: str = ',') -> dict[datetime.date, np.float32]:
    db = dict()

    # collect all data from the data source
    with open(path, newline='') as csvfile:
        spamreader = csv.reader(csvfile, delimiter=delim)
        for index, row in enumerate(spamreader):
            if index == 0:
                continue
            db[row[0]] = np.float32(float(row[1]))

    # sorted all date's that is used in de db
    db = dict(sorted(db.items()))

    # convert string to date inplace
    db = {datetime.datetime.strptime(
        k, '%Y-%m-%d').date(): v for k, v in db.items()}
    db1 = dict()

    # when a date is not in it use prev date's value and add this date value
    prev_date = list(db.keys())[0]
    for k, v in db.items():
        if k == prev_date:
            db1[k] = v
            continue

        differ = (k - prev_date).days
        if differ > 1:
            for counter in range(differ - 1):
                prev_value = db1[prev_date]
                cur_date = prev_date + datetime.timedelta(days=1)
                db1[cur_date] = prev_value
                prev_date = cur_date
        db1[k] = v
        prev_date = k

    # if not _check_increasing_order(list(db1.keys())):
    #     print('days not correctly')
    #     exit(1)

    return db1


# first value of db can not be more then 1000 i have no idea what to then...
def load_test_db2(path: Path, delim: str = ',') -> dict[datetime.date, np.float32]:
    db = dict()

    # collect all data from the data source
    with open(path, newline='') as csvfile:
        spamreader = csv.reader(csvfile, delimiter=delim)
        for index, row in enumerate(spamreader):
            if index == 0:
                continue
            db[row[0]] = np.float32(float(row[1]))

    # sorted all date's that is used in de db
    db = dict(sorted(db.items()))

    # convert string to date inplace
    db = {datetime.datetime.strptime(
        k, '%Y-%m-%d').date(): v for k, v in db.items()}
    db1 = dict()

    # when a date is not in it use prev date's value and add this date value
    prev_date = list(db.keys())[0]
    for index, (k, v) in enumerate(db.items()):
        value = v
        if value > np.float32(1000) and index == 0:
            print('Invalid state for the tester!!!')
            exit(99)

        if k == prev_date:
            db1[k] = v
            continue

        if value > np.float32(1000):
            value = db[prev_date]
        differ = (k - prev_date).days
        if differ > 1:
            for counter in range(differ - 1):
                prev_value = db1[prev_date]
                cur_date = prev_date + datetime.timedelta(days=1)
                db1[cur_date] = prev_value
                prev_date = cur_date

        db1[k] = value
        prev_date = k

    # if not _check_increasing_order(list(db1.keys())):
    #     print('days not correctly')
    #     exit(1)

    return db1


if __name__ == '__main__':
    load_test_db(path=Path('db/data.csv'), delim=',')
    load_test_db2(path=Path('db/data.csv'), delim=',')
