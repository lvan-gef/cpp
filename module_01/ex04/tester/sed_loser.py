#! /usr/bin/env python3

from pathlib import Path
import sys
import subprocess
import os
import argparse


def test_one(lsed: str):
    print('Start Test 1: To less or to many arguments', file=sys.stdout)

    tests = [
        f'{lsed}',
        f'{lsed} 1',
        f'{lsed} 1 2',
        f'{lsed} 1 2 3 4',
        f'{lsed} 1 2 3 4 5 6 7 8 9'
    ]

    for i, test in enumerate(tests, start=1):
        print(f'Start Test 1.{i}: "{test}"', file=sys.stdout)
        result = subprocess.run(f'{test}', shell=True, capture_output=True)
        assert result.returncode != 0
        assert result.stdout.decode() == ''
        assert result.stderr.decode() != ''

    print('Pass Test 1 : To less or to many arguments\n', file=sys.stdout)


def test_two(lsed: str):
    print('Start Test 2: Invalid input file', file=sys.stdout)

    test_dir = Path().cwd().joinpath('src').joinpath('test2')
    files = [
        test_dir.joinpath('not_exists'),
        test_dir.joinpath('no_permision'),
        test_dir.joinpath('no_read'),
        test_dir.joinpath('a_dir')
    ]
    if not test_dir.exists():
        print('Create test dir and files', file=sys.stdout)
        test_dir.mkdir(parents=True)
        test_dir.joinpath('a_dir').mkdir(parents=True)

        with open(files[1], 'w'):
            pass
        os.chmod(files[1], 0o000)

        with open(files[2], 'w'):
            pass
        os.chmod(files[2], 0o022)

    tests = [
        f'{lsed} {file} smurf smurfin'
        for file in files
    ]

    for i, test in enumerate(tests, start=1):
        print(f'Start Test 2.{i}: "{test}"', file=sys.stdout)
        result = subprocess.run(f'{test}', shell=True, capture_output=True)
        assert result.returncode != 0
        assert result.stdout.decode() == ''
        assert result.stderr.decode() != ''

    print('Pass  Test 2: Invalid input file\n', file=sys.stdout)


def test_three(lsed: str):
    print('Start Test 3: Empty input file', file=sys.stdout)

    test_dir = Path().cwd().joinpath('src').joinpath('test4')
    if not test_dir.exists():
        print('Create test dir', file=sys.stdout)
        test_dir.mkdir(parents=True)

        with open(test_dir.joinpath('empty.txt'), 'w'):
            pass

    test = f'{lsed} {test_dir.joinpath("empty.txt")} earth space'
    print(f'Start Test 3.1: "{test}"', file=sys.stdout)
    result = subprocess.run(test, shell=True, capture_output=True)
    assert result.returncode == 0
    assert result.stdout.decode() == ''
    assert result.stderr.decode() == ''

    # check outfile is leeg
    with open(test_dir.joinpath('empty.txt.replace'), 'r') as f:
        data = f.read()
    assert data == ''

    print('Pass  Test 3: Empty input file\n', file=sys.stdout)


def test_four(lsed: str):
    print('Start Test 4: no match', file=sys.stdout)
    test_dir = Path().cwd().joinpath('src')

    test_file = test_dir.joinpath('holy_bible.txt')
    test = f'{lsed} {test_file} is_er_niet space'
    print(f'Start Test 4.1: "{test}"', file=sys.stdout)
    result = subprocess.run(test, shell=True, capture_output=True)
    assert result.returncode == 0
    assert result.stdout.decode() == ''
    assert result.stderr.decode() == ''

    with open(test_dir.joinpath('holy_bible.txt.replace'), 'r') as f:
        own = f.read()
    with open(test_file, 'r') as f:
        og = f.read()

    assert own == og

    print('Pass  Test 4: no match\n', file=sys.stdout)


def test_five(lsed: str):
    print('Start Test 5: sub things in file', file=sys.stdout)
    test_dir = Path().cwd().joinpath('src')

    test_file = test_dir.joinpath('holy_bible.txt')
    test = f'{lsed} {test_file} the de'
    print(f'Start Test 5.1: "{test}"', file=sys.stdout)
    result = subprocess.run(test, shell=True, capture_output=True)
    assert result.returncode == 0
    assert result.stdout.decode() == ''
    assert result.stderr.decode() == ''

    with open(test_dir.joinpath('holy_bible.txt.replace'), 'r') as f:
        own = f.read()
    og = subprocess.run(f'sed "s/the/de/g" {test_file}', shell=True, capture_output=True)

    assert own == og.stdout.decode()

    test_file = test_dir.joinpath('smurf.txt')
    test = f'{lsed} {test_file} la na'
    print(f'Start Test 5.2: "{test}"', file=sys.stdout)
    result = subprocess.run(test, shell=True, capture_output=True)
    assert result.returncode == 0
    assert result.stdout.decode() == ''
    assert result.stderr.decode() == ''

    with open(test_dir.joinpath('smurf.txt.replace'), 'r') as f:
        own = f.read()
    og = subprocess.run(f'sed "s/la/na/g" {test_file}', shell=True, capture_output=True)

    assert own == og.stdout.decode()

    print('Pass  Test 5: sub things in file', file=sys.stdout)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("lsed", help="path to exe")
    args = parser.parse_args()
    lexe = args.lsed

    test_one(lsed=lexe)
    test_two(lsed=lexe)
    test_three(lsed=lexe)
    test_four(lsed=lexe)
    test_five(lsed=lexe)
