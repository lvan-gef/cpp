import subprocess
import sys
from typing import Tuple
import collections
from pathlib import Path
import random
import itertools

import gen_rpn

INT_MIN = 0
INT_MAX = 9


def get_result(exe: Path, rpn: str) -> Tuple[str, str]:
    print(f'Run {exe} with argument: {rpn}')

    result = subprocess.run(f'{exe} "{rpn}"',
                            shell=True,
                            capture_output=True,
                            text=True)

    stdout = result.stdout.strip()
    stderr = result.stderr.strip()

    try:
        assert result.returncode == 0
    except AssertionError:
        print(f'Expect returncode 0 got: {result.returncode}, stderr: {stderr}',
              file=sys.stderr)
        exit(1)

    return stdout, stderr


def rpn_result(sum_input: str) -> Tuple[float, str]:
    result_stack = collections.deque()
    for lttr in sum_input.split(' '):
        if lttr.isdigit():
            result_stack.append(int(lttr))
        else:
            if lttr in ['+', '-', '*', '/']:
                if lttr == '+':
                    if sum(1 for elem in result_stack) >= 2:
                        last = result_stack.pop()
                        second_last = result_stack.pop()
                        result_stack.append(second_last + last)  # b + c
                    else:
                        return -1, 'Not enough elements on the stack for `+` opperator'
                elif lttr == '-':
                    if sum(1 for elem in result_stack) >= 2:
                        last = result_stack.pop()
                        second_last = result_stack.pop()
                        result_stack.append(second_last - last)  # b - c
                    else:
                        return -1, 'Not enough elements on the stack for `-` opperator'
                elif lttr == '*':
                    if sum(1 for elem in result_stack) >= 2:
                        last = result_stack.pop()
                        second_last = result_stack.pop()
                        result_stack.append(second_last * last)  # b * c
                    else:
                        return -1, 'Not enough elements on the stack for `*` opperator'
                else:
                    if sum(1 for elem in result_stack) >= 2:
                        last = result_stack.pop()
                        second_last = result_stack.pop()
                        if last == 0.0:
                            return -1, 'Error: div by zero'

                        result_stack.append(second_last / last)  # b / c
                    else:
                        return -1, 'Not enough elements on the stack for `/` opperator'
            else:
                return -1, 'Error'

    return float(result_stack.pop()), ''


def run_test(exe: Path, rpn: str):
    rpn_stdout, rpn_stderr = get_result(exe=exe, rpn=rpn)

    result, err = rpn_result(sum_input=rpn)
    if err != '':
        try:
            assert rpn_stderr.split('\n')[0].lower().startswith(err.lower())
            return
        except AssertionError:
            print(f'Except stderr to startswith: \'{err.lower()}\', got: \'{rpn_stderr}\'',
                  file=sys.stderr)
            exit(1)

    try:
        assert len(rpn_stderr) == 0
    except AssertionError:
        print(f'There should not messsage on stderr, got: \'{rpn_stderr}\'',
              file=sys.stderr)
        exit(1)

    try:
        assert len(rpn_stdout) > 0
    except AssertionError:
        print('Expect something on stdout got notthing', file=sys.stderr)

        exit(1)

    try:
        assert round(float(rpn_stdout), 2) == round(result, 2)
    except AssertionError:
        print(f'Expect output: \'{result}\' got: \'{rpn_stdout}\'',
              file=sys.stderr)
        exit(1)


def subject_tester(exe: Path):
    subject_tests = [
        '5 5 5 * +',
        '8 9 * 9 - 9 - 9 - 4 - 1 +',
        '7 7 * 7 -',
        '1 2 * 2 / 2 * 2 4 - +',
        '(1 + 1)'
    ]

    for test in subject_tests:
        run_test(exe=exe, rpn=test)


def random_inputs(exe: Path):
    max_size = 1_000_000

    # for combination in itertools.product(range(10), repeat=10):
    #     print(combination)
    #     break

    for length in range(1, 11):
        for combination in itertools.product(range(10), repeat=length):
            for rpn in gen_rpn.valid_rpn(numbers=list(combination)):
                run_test(exe=exe, rpn=rpn)

    # for size in range(1, 9):
    #     inputs = [size - 1 for _ in range(size)]
    #
    #     for rpn in gen_rpn.valid_rpn(numbers=inputs):
    #         run_test(exe=exe, rpn=rpn)


if __name__ == '__main__':
    # subject_tester(exe='../RPN')
    random_inputs(exe='../RPN')
