#! /usr/bin/python3

import argparse
import sys
import subprocess
import random
from pathlib import Path

MAX_INT = 2147483647
MIN_INT = -2147483648

INPUT_SIZES = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 35, 42, 100, 166, 200, 259,
               300, 369, 400, 444, 500, 512, 600, 666, 700, 714, 800, 823,
               900, 999, 1000, 1111, 1222, 1333, 1444, 1555, 1666, 1777, 1888, 1999,
               2000, 2111, 2222, 2333, 2444, 2555, 2666, 2777, 2888, 2999,
               3099, 3111, 3200, 3344, 3455, 3566, 3677, 3788, 3899, 3922,
               4045, 4168, 4257, 4313, 4489, 4598, 4632, 4712, 4896, 4942,
               5069, 5168, 5257, 5313, 5589, 5598, 5632, 5712, 5896, 5952,
               6042, 6168, 6267, 6313, 6489, 6598, 6632, 6712, 6896, 6962,
               7089, 7178, 7277, 7313, 7489, 7598, 7632, 7712, 7897, 7972,
               8053, 8188, 8288, 8313, 8489, 8598, 8632, 8712, 8898, 8982,
               9052, 9199, 9299, 9313, 9499, 9599, 9632, 9712, 9899, 9992,
               11234, 11567, 12000]  # python subprocess will stop after 1200 to much args


def get_uniq_valid_seq(size: int) -> list[int]:
    return random.sample(range(0, MAX_INT + 1), size)


def get_valid_seq(size: int) -> list[int]:
    return random.choices(range(0, MAX_INT), k=size)


def get_uniq_invalid_seq(size: int) -> list[int]:
    return random.sample(range(MIN_INT, 0), size)


def run_program(exe: Path, seq: list[int], should_pass = True) -> tuple[list[int], int, list[int], int]:
    """
    Run the program, check if was succesfull, if yes then parse the output

    Args:
        exe: The path to the exe of the test
        seq: The list of unsorted intergers
        should_pass: Process must be succesfull

    Returns: tuple[sorted_con1, duration_con1, sorted_con2, duration_con2]

    """
    nbrs = ' '.join(str(x) for x in seq)

    try:
        result = subprocess.run(f'{exe} {nbrs}', shell=True, capture_output=True, text=True)
    except OSError as ose:
        print(f'python3 subprocess went wrong: {ose}', file=sys.stderr)
        exit(1)

    if should_pass:
        assert result.returncode == 0
        assert result.stderr == ''
    else:
        print(result.returncode)
        print(result.stdout)
        print(result.stderr)
        assert result.returncode != 0
        assert result.stderr != ''

    lines = [line for line in result.stdout.split('\n') if line]
    index = 0
    for index, line in enumerate(lines):
        if not line:
            continue

        if line.lower().startswith('time'):
            break

    return [int(nbr) for nbr in lines[index + 1].split(':')[1].split(' ') if nbr], int(lines[index].split(':')[-1].split(' ')[1]), [], 0


def main(exe: Path, retry: int) -> None:
    if not exe.exists():
        print(f'could not found: {exe}', file=sys.stderr)
        return

    # print('Start uniq random seq test')
    # for inp in INPUT_SIZES:
    #     vec_times = []
    #     seq = get_uniq_valid_seq(size=inp)
    #     py_seq = sorted(seq)
    #
    #     for _ in range(retry):
    #         vec_seq, vec_time, _, _ = run_program(exe=exe, seq=seq, should_pass=True)
    #         vec_times.append(int(vec_time))
    #
    #         assert vec_seq == py_seq
    #
    #     print(f'\tsize: {inp}, min/avg/max: {min(vec_times)} {sum(vec_times) / len(vec_times)} {max(vec_times)}')
    # print('Pass uniq random seq test\n')
    #
    #
    # print('Start random seq test')
    # for inp in INPUT_SIZES:
    #     vec_times = []
    #     seq = get_valid_seq(size=inp)
    #     py_seq = sorted(seq)
    #
    #     for _ in range(retry):
    #         vec_seq, vec_time, _, _ = run_program(exe=exe, seq=seq, should_pass=True)
    #         vec_times.append(int(vec_time))
    #
    #         assert vec_seq == py_seq
    #
    #     print(f'\tsize: {inp}, min/avg/max: {min(vec_times)} {sum(vec_times) / len(vec_times)} {max(vec_times)}')
    # print('Pass random seq test')

    print('Start uniq random invalid seq test')
    for inp in INPUT_SIZES:
        seq = get_uniq_invalid_seq(size=inp)

        run_program(exe=exe, seq=seq, should_pass=False)

    print('Pass uniq random seq test\n')


if __name__ == '__main__':
    parser = argparse.ArgumentParser(prog='PmergeMeTester', description='A simple tester')
    parser.add_argument('exe', help='The exe of the tester for PmergeMe', type=Path)
    parser.add_argument('-r', '--retry', help='How many times to test with the same input, to get a better result', default=100, type=int)
    args = parser.parse_args()

    main(exe=args.exe.resolve(), retry=args.retry)
