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
    # print(f'Run {exe} with argument: {rpn}')

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
                        return -1, 'Error: Not enough elements on the stack for `+` opperator'
                elif lttr == '-':
                    if sum(1 for elem in result_stack) >= 2:
                        last = result_stack.pop()
                        second_last = result_stack.pop()
                        result_stack.append(second_last - last)  # b - c
                    else:
                        return -1, 'Error: Not enough elements on the stack for `-` opperator'
                elif lttr == '*':
                    if sum(1 for elem in result_stack) >= 2:
                        last = result_stack.pop()
                        second_last = result_stack.pop()
                        result_stack.append(second_last * last)  # b * c
                    else:
                        return -1, 'Error: Not enough elements on the stack for `*` opperator'
                else:
                    if sum(1 for elem in result_stack) >= 2:
                        last = result_stack.pop()
                        second_last = result_stack.pop()
                        if last == 0.0:
                            return -1, 'Error: div by zero'

                        result_stack.append(second_last / last)  # b / c
                    else:
                        return -1, 'Error: Not enough elements on the stack for `/` opperator'
            else:
                return -1, 'Error'

    return float(result_stack.pop()), ''


def run_test(exe: Path, rpn: str):
    rpn_stdout, rpn_stderr = get_result(exe=exe, rpn=rpn)

    result, err = rpn_result(sum_input=rpn)
    if err != '':
        try:
            assert rpn_stderr.split('\n')[0].lower().startswith('error')
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
    tests = [
        '1 2 5 + -',
        '8 9 9 9 - 9 8 9 - 4 - 1 + - - / +',
        '8 9 9 9 9 * 9 - 9 8 9 - 4 - 1 + - - / + +'
        '0 1 + 2 - 3 * 4 / 5 + 6 - 7 * 8 / 9 +'
    ]

    test_cases = [
        # Basic operations
        ("2 3 +", 5),              # Simple addition
        ("5 3 -", 2),              # Simple subtraction
        ("4 2 *", 8),              # Simple multiplication
        ("6 2 /", 3),              # Simple division
        ("10 3 %", 1),             # Modulus
        ("2 3 ^", 8),              # Exponentiation

        # Multiple operations
        ("3 4 + 5 *", 35),         # (3 + 4) * 5
        ("7 2 3 + -", 2),          # 7 - (2 + 3)
        ("15 7 1 1 + - / 3 *", 3),  # 15 / (7 - (1 + 1)) * 3
        ("1 2 + 4 * 3 +", 15),     # ((1 + 2) * 4) + 3

        # Stack manipulation required
        ("3 4 2 * +", 11),         # 3 + (4 * 2)
        ("5 4 7 2 + * -", -41),    # 5 - (4 * (7 + 2))

        # Zero handling
        ("0 1 +", 1),              # Adding zero
        ("1 0 *", 0),              # Multiplying by zero
        ("0 10 /", 0),             # Zero divided by number

        # Negative numbers
        ("-3 -2 +", -5),           # Adding negatives
        ("3 -2 *", -6),            # Multiplying by negative
        ("-15 3 /", -5),           # Dividing negative

        # More complex expressions
        ("10 5 2 * 3 + -", 0),     # 10 - (5 * 2 + 3)
        ("2 3 4 * 5 - +", 10),     # 2 + (3 * 4 - 5)
        ("3 4 + 5 6 + *", 77),     # (3 + 4) * (5 + 6)

        # Edge cases
        ("1", 1),                  # Single number
        ("-1", -1),                # Single negative
        ("0", 0),                  # Zero

        # Larger numbers
        ("100 50 25 / *", 200),    # 100 * (50 / 25)
        ("999 1 +", 1000),         # Adding to three digits
        ("2 10 ^", 1024),          # Power of 10

        # Decimal results
        ("5 2 /", 2.5),            # Division resulting in decimal
        ("10 3 /", 3.3333333333333335),  # Division with repeating decimal

        # More complex mathematical expressions
        ("3 4 + 5 6 + * 7 -", 70),     # (3 + 4) * (5 + 6) - 7
        ("2 3 ^ 4 5 ^ +", 1032),       # (2^3) + (4^5)
        ("10 2 8 * 3 + /", 0.5263157894736842),  # 10 / (2 * 8 + 3)

        # Testing operator precedence
        ("4 5 * 6 7 * +", 62),         # (4 * 5) + (6 * 7)
        ("3 4 5 * + 6 -", 17),         # (3 + (4 * 5)) - 6
        ("2 3 + 4 * 5 2 ^ -", 15)      # ((2 + 3) * 4) - (5 ^ 2)
    ]


    # Edge cases that should raise errors
    error_cases = [
        "",                # Empty expression
        "1 +",            # Not enough operands
        "1 2",            # No operator
        "1 0 /",          # Division by zero
        "+ - ",           # Only operators
        "1 2 3 +",        # Too many operands
        "a b +",          # Invalid tokens
        "1 2 &",          # Invalid operator
        "1.1.1 2 +",      # Malformed number
        "2 2 + +",        # Too many operators
    ]

    for expression, expected in test_cases:
        result = get_result(exe=exe, rpn=expression)
        if result[0] == '':
            print('waarom')
            continue
        assert abs(float(result[0]) - expected) < 1e-10, f"Failed: {expression} = {float(result[0])}, expected {expected}"


if __name__ == '__main__':
    # subject_tester(exe='../RPN')
    random_inputs(exe='../RPN')
