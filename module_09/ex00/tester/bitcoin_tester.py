#! /usr/bin/env python3

import argparse
import csv
from pathlib import Path
import datetime
import numpy as np
import subprocess
from typing import Optional

import create_database as cs
import invalid_dates as id


DATE_FORMAT = '%Y-%m-%d'
TESTER_PATH = Path().cwd().joinpath('tester')
TESTER_DB_PATH = TESTER_PATH.joinpath('db')
CODAM_CSV_PATH = TESTER_DB_PATH.joinpath('data.csv')
CODAM_INPUT_PATH = TESTER_DB_PATH.joinpath('input.txt')
ALL_BITCOIN_PATH = TESTER_DB_PATH.joinpath('all_bitcoin.csv')
INVALID_DATES_PATH = TESTER_DB_PATH.joinpath('invalid_dates.csv')


def save_state(py_out: list[str], btc_out: list[str], file: str) -> None:
    """
    Save the state of the python's expected output.
    And the state of the btc's output.
    """

    with open(f'py_{file}.txt', 'w') as f:
        f.write('\n'.join(py_out))

    with open(f'btc_{file}.txt', 'w') as f:
        f.write('\n'.join(btc_out))


def get_closest_previous_date(date_dict: dict[datetime.date, np.float32], target_date_str: str) -> Optional[str]:
    """
    If date is not in dict search for the closest date that is lower then the one we looking for
    """

    target_date = datetime.datetime.strptime(str(target_date_str), DATE_FORMAT)
    date_objects = [
        (datetime.datetime.strptime(str(date_str), DATE_FORMAT), date_str)
        for date_str in date_dict.keys()]
    date_objects.sort(reverse=True)

    for date_obj, original_str in date_objects:
        if date_obj <= target_date:
            return original_str

    return None


def gen_data(path: Path, delim: str = '|'):
    """
    Read csv file and yield a line back
    """

    with open(path, newline='') as csvfile:
        reader = csv.reader(csvfile, delimiter=delim)
        for index, row in enumerate(reader):
            if index == 0:
                continue
            yield [x.strip() for x in row]


def get_results(db: dict[datetime.date, np.float32], path: Path, delim: str, btc: Path) -> tuple[list[str], list[str], list[str], list[str]]:
    """
    Python will create 2 lists, one for stdout and one for stderr.
    What is on stdout is the valid output we expect, stderr is for all the errors.
    Then the btc program get called and we capture his stdout and stderr.
    And create also 2 lists, stdout should be the output that the program make and stderr for the errors
    It also assert that the returncode of the btc program is 0
    """

    stdout = []
    stderr = []

    for input_data in gen_data(path=path, delim=delim):
        if len(input_data) != 2:
            stderr.append(f'Error: bad input => {input_data[0]}')
            continue

        if not id.validate_date(input_data[0]):
            stderr.append(f'Error: bad input => {input_data[0]}')
            continue

        input_data[0] = datetime.datetime.strptime(
            input_data[0], DATE_FORMAT).date()

        if np.float32(input_data[1]) > np.float32(1000):
            stderr.append('Error: to large a number.')
            continue

        if np.float32(input_data[1]) < np.float32(0):
            stderr.append('Error: not a positive number.')
            continue

        if input_data[0] in db:
            stdout.append(
                f'{input_data[0]} => {np.float32(input_data[1]):.2f} = {np.float32(input_data[1]) * np.float32(db[input_data[0]]):.2f}')
            continue

        prev_date = get_closest_previous_date(db, input_data[0])
        if prev_date is None:
            stderr.append('Error: date is lower then what is in the database.')
            continue

        stdout.append(
            f'{input_data[0]} => {np.float32(input_data[1]):.2f} = {np.float32(input_data[1]) * np.float32(db[prev_date]):.2f}')

    print(f'Run {btc} with argument: {path}')
    result = subprocess.run(
        f'{btc} {path}', shell=True, capture_output=True, text=True)
    try:
        assert result.returncode == 0
    except AssertionError:
        print(f'Expect returncode to be 0 got: {result.returncode}')
        exit(1)

    return [x.strip() for x in stdout if x], [x.strip() for x in stderr if x], [x.strip() for x in result.stdout.split('\n') if x], [x.strip() for x in result.stderr.split('\n') if x]


def tester(db: dict[datetime.date, np.float32], target_path: Path, delim: str, btc: Path):
    """
    Compare the expected output (of python) with the btc output.
    """

    py_std, py_err, btc_std, btc_err = get_results(
        db=db, path=target_path, delim=delim, btc=btc)

    # assert that we have the same amount of messages on stdout
    try:
        assert len(py_std) == len(btc_std)
    except AssertionError:
        print(f'Expect: {len(py_std)} to stdout, got: {len(btc_std)}')
        save_state(py_out=py_std, btc_out=btc_std, file='stdout')
        exit(1)

    # assert alle dates are the same
    for py_line, btc_line in zip(py_std, btc_std):
        py_split = [x for x in py_line.split() if x]
        btc_split = [x for x in btc_line.split() if x]

        # assert we have data in from the btc program
        try:
            assert len(btc_split) > 0
        except AssertionError:
            print('The output of btc have a empty line in it')
            exit(1)

        # assert date's
        try:
            assert py_split[0] == btc_split[0]
        except AssertionError:
            print(f'Expect date: {py_split[0]} got: {btc_split[0]}')
            exit(1)

        # assert result
        try:
            lookup_date = datetime.datetime.strptime(
                py_split[0], DATE_FORMAT).date()
            np.testing.assert_almost_equal(
                np.float32(py_split[-1]),
                np.float32(btc_split[-1]),
                decimal=2)
        except AssertionError:
            print(py_line, btc_line)
            print(
                f'For date: {py_split[0]}, expect value: {np.float32(py_split[-1])} got: {np.float32(btc_split[-1])}')
            exit(1)

    # assert that we have the same amount of messages on stderr
    try:
        assert len(py_err) == len(btc_err)
    except AssertionError:
        print(f'Expect: {len(py_err)} to stderr, got: {len(btc_err)}')
        save_state(py_out=py_err, btc_out=btc_err, file='stderr')
        exit(1)

    # assert that all messages starts with error
    for msg in btc_err:
        try:
            assert msg.lower().startswith('error')
        except AssertionError:
            print(
                f'Expect that message on stderr startswith error, got: {msg}')
            exit(1)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(
                    prog='btc tester',
                    description='A simple tester for Codam cpp 09 ex00',
                    epilog='Good luck with it')
    parser.add_argument('filename', help='The path to the btc exe')
    args = parser.parse_args()
    btc_path = Path(args.filename).resolve()
    if not btc_path.exists():
        print(f'Could not find the exe: {btc_path}')
        exit(1)
    print(btc_path)

    db = cs.load_test_db2(path=CODAM_CSV_PATH, delim=',')

    print('Start subject tester')
    tester(db=db, target_path=CODAM_INPUT_PATH, delim='|', btc=btc_path)
    print('Pass subject tester')

    print('Start all_bitcoin tester')
    tester(db=db, target_path=ALL_BITCOIN_PATH, delim=',', btc=btc_path)
    print('Pass all_bitcoin tester')

    print('Start invalid date test')
    tester(db=db, target_path=INVALID_DATES_PATH, delim='|', btc=btc_path)
    print('Pass invalid date test')
