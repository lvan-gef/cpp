#! /usr/bin/env python3

import csv
from pathlib import Path
from datetime import datetime
import numpy
import subprocess


# def get_closest_previous_date(date_dict, target_date_str, date_format='%Y-%m-%d'):
#     target_date = datetime.strptime(target_date_str, date_format)
#     date_objects = [(datetime.strptime(date_str, date_format), date_str)
#                     for date_str in date_dict.keys()]
#     date_objects.sort(reverse=True)
#
#     for date_obj, original_str in date_objects:
#         if date_obj <= target_date:
#             return original_str
#
#     return None

def get_closest_previous_date(date_dict, target_date_str, date_format='%Y-%m-%d'):
    target_date = datetime.strptime(target_date_str, date_format)
    date_objects = [(datetime.strptime(date_str, date_format), date_str)
                    for date_str in date_dict.keys()]

    date_objects.sort(reverse=True)

    for date_obj, original_str in date_objects:
        if date_obj <= target_date:
            return original_str

    return None


def gen_data(path: Path, delim: str = '|'):
    with open(path, newline='') as csvfile:
        spamreader = csv.reader(csvfile, delimiter=delim)
        for index, row in enumerate(spamreader):
            if index == 0:
                continue
            yield [x.strip() for x in row]


def load_db(path: Path, delim: str = ',') -> dict:
    db = dict()

    with open(path, newline='') as csvfile:
        spamreader = csv.reader(csvfile, delimiter=delim)
        for index, row in enumerate(spamreader):
            if index == 0:
                continue
            db[row[0]] = float(row[1])

    return db


# def get_results(path: Path, db: dict, delim: str) -> tuple[list[str], list[str], list[str], list[str]]:
#     stdout = []
#     stderr = []
#
#     for input_data in gen_data(path=path, delim=delim):
#         if len(input_data) != 2:
#             stderr.append(f'Error: bad input => {input_data[0]}')
#             continue
#
#         if numpy.float64(input_data[1]) > 1000.0:
#             stderr.append('Error: to large a number.')
#             continue
#
#         if numpy.float64(input_data[1]) < 0.0:
#             stderr.append('Error: not a positive number.')
#             continue
#
#         if input_data[0] in db:
#             stdout.append(
#                 f'{input_data[0]} => {numpy.float64(input_data[1]):.2f} = {numpy.float64(input_data[1]) * numpy.float64(db[input_data[0]]):.2f}')
#             continue
#
#         prev_date = get_closest_previous_date(db, input_data[0])
#         if prev_date is None:
#             stderr.append('Error: date is lower then what is in the database.')
#             continue
#
#         stdout.append(
#             f'{input_data[0]} => {numpy.float64(input_data[1])} = {numpy.float64(input_data[1]) * numpy.float64(db[prev_date]):.2f}')
#
#     print(f'Run btc with argument: {path}')
#     result = subprocess.run(
#         f'../btc {path}', shell=True, capture_output=True, text=True)
#     try:
#         assert result.returncode == 0
#     except AssertionError:
#         print(f'Expect returncode to be 0 got: {result.returncode}')
#         exit(1)
#
#     return [x.strip() for x in stdout if x], [x.strip() for x in stderr if x], [x.strip() for x in result.stdout.split('\n') if x], [x.strip() for x in result.stderr.split('\n') if x]


def get_results(path: Path, db: dict, delim: str) -> tuple[list[str], list[str], list[str], list[str]]:
    stdout = []
    stderr = []

    debug_date = "2010-07-17"  # Pick any date from your output

    for input_data in gen_data(path=path, delim=delim):
        if len(input_data) != 2:
            stderr.append(f'Error: bad input => {input_data[0]}')
            continue

        # Debug print for our specific date
        if input_data[0] == debug_date:
            print(f"\nDEBUG for date {debug_date}:")
            print(f"Input value: {input_data[1]}")
            print(f"Database has date? {debug_date in db}")
            if debug_date in db:
                print(f"Direct DB value: {db[debug_date]}")
            else:
                prev_date = get_closest_previous_date(db, debug_date)
                print(f"Previous date: {prev_date}")
                print(f"Previous date value: {db[prev_date]}")

    # Collect all valid inputs first and sort them
    valid_inputs = []
    for input_data in gen_data(path=path, delim=delim):
        if len(input_data) != 2:
            stderr.append(f'Error: bad input => {input_data[0]}')
            continue

        if numpy.float64(input_data[1]) > 1000.0:
            stderr.append('Error: to large a number.')
            continue

        if numpy.float64(input_data[1]) < 0.0:
            stderr.append('Error: not a positive number.')
            continue

        valid_inputs.append(input_data)

    # Sort by date
    valid_inputs.sort(key=lambda x: x[0])  # Sort by date string

    # Process sorted inputs
    for input_data in valid_inputs:
        if input_data[0] in db:
            stdout.append(
                f'{input_data[0]} => {numpy.float64(input_data[1]):.2f} = {numpy.float64(input_data[1]) * numpy.float64(db[input_data[0]]):.2f}')
            continue

        prev_date = get_closest_previous_date(db, input_data[0])
        if prev_date is None:
            stderr.append('Error: date is lower then what is in the database.')
            continue

        stdout.append(
            f'{input_data[0]} => {numpy.float64(input_data[1])} = {numpy.float64(input_data[1]) * numpy.float64(db[prev_date]):.2f}')

    print(f'Run btc with argument: {path}')
    result = subprocess.run(
        f'../btc {path}', shell=True, capture_output=True, text=True)
    try:
        assert result.returncode == 0
    except AssertionError:
        print(f'Expect returncode to be 0 got: {result.returncode}')
        exit(1)

    return [x.strip() for x in stdout if x], [x.strip() for x in stderr if x], [x.strip() for x in result.stdout.split('\n') if x], [x.strip() for x in result.stderr.split('\n') if x]


def tester(db_path: Path, target_path: Path, delim: str):
    db = load_db(path=db_path)
    stdout, stderr, btc_stdout, btc_stderr = get_results(
        path=target_path, db=db, delim=delim)

    print("\nFirst few raw input entries:")
    for i, input_data in enumerate(gen_data(path=db_path, delim=delim)):
        if i < 5:
            print(f"Raw input: {input_data}")
        if i >= 5:
            break

    # Debug: Print some DB entries
    print("\nFirst few DB entries:")
    for i, (date, value) in enumerate(sorted(db.items())):
        if i < 5:
            print(f"DB: {date}: {value}")
        if i >= 5:
            break

    # assert that we have the same amount of messages on stdout as that we expect
    try:
        assert len(btc_stdout) == len(stdout)
    except AssertionError:
        with open('std.txt', 'w') as f:
            f.write('\n'.join(stdout))

        with open('btc_std.txt', 'w') as f:
            f.write('\n'.join(btc_stdout))

        print(
            f'Expect: {len(stdout)} Prints to stdout\nGot   : {len(btc_stdout)}')
        exit(1)

    # assert that the results are the same
    for std, btc in zip(stdout, btc_stdout):
        std_split = std.split(' ')
        btc_split = btc.split(' ')

        # assert date's
        try:
            assert std_split[0] == btc_split[0]
        except AssertionError:
            print(f'Expect date: {std_split[0]} got: {btc_split[0]}')
            exit(1)

        # assert value
        try:
            assert numpy.float64(std_split[-1]) == numpy.float64(btc_split[-1])
        except AssertionError:
            print(
                f'DB date: {std_split[0]}, lookup date: {btc_split[0]}, Expect value: {numpy.float64(std_split[-1])} got: {numpy.float64(btc_split[-1])}')
            exit(1)

    # assert that we have the same amount of messages on stderr as that we expect
    try:
        assert len(btc_stderr) == len(stderr)
    except AssertionError:
        with open('stderr.txt', 'w') as f:
            f.write('\n'.join(stderr))

        with open('btc_stderr.txt', 'w') as f:
            f.write('\n'.join(btc_stderr))

        print(
            f'Expect: {len(stderr)} Prints to stderr\nGot   : {len(btc_stderr)}')
        exit(1)

    # check if all messages from stderr starts with error
    for msg in btc_stderr:
        try:
            assert msg.lower().startswith('error')
        except AssertionError:
            print('Not all messages on stderr starts with \'error\'')
            exit(1)


if __name__ == '__main__':
    # print('Start subject tester')
    # tester(db_path=Path('db/data.csv'), target_path='db/input.txt')
    # print('Pass subject tester')

    print('Start all_bitcoin tester')
    tester(db_path=Path('db/data.csv'), target_path=Path('db/all_bitcoin.csv'), delim=',')
    print('Pass all_bitcoin tester')
