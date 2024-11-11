import subprocess
import sys
from typing import List, Generator, Tuple
from pathlib import Path
import itertools
import numpy as np

import gen_rpn


def get_result(exe: Path, rpn: str) -> List[str]:
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

    return [stdout, stderr]


# def subject_tester(exe: Path):
#     subject_tests = [
#         '5 5 5 * +',
#         '8 9 * 9 - 9 - 9 - 4 - 1 +',
#         '7 7 * 7 -',
#         '1 2 * 2 / 2 * 2 4 - +',
#         '(1 + 1)'
#     ]
#
#     for test in subject_tests:
#         run_test(exe=exe, rpn=test)


def valid_inputs(exe: Path) -> Generator[Tuple[str, np.float32], None, None]:

    # Basic operations
    for expression, result in gen_rpn.basic_op_tester():
        yield expression, result

    # # Multiple operations
    for x in range(3, 25):
        yield gen_rpn.multi_op_tester(x)

    # # Zero handling
    # yield "0 1 +", 1
    # yield "1 0 *", 0
    # yield "0 9 /", 0
    #
    # # Negative numbers
    # yield "-3 -2 +", -5
    # yield "3 -2 *", -6
    # yield "-6 3 /", -2
    #
    # # More complex expressions
    # yield "9 2 5 2 * 3 + - *", -99
    # yield "2 3 4 * 5 - +", 9
    # yield "3 4 + 5 6 + *", 77
    #
    # # Edge cases
    # for x in range(INT_MIN, INT_MAX):
    #     yield str(x), x
    #
    # # Larger numbers
    # # "100 50 25 / *", 200
    # #        100     |    50   | 25  |
    # yield "5 9 * 2 * 5 5 + + 5 9 * 5 + 5 5 * / *", 200
    #
    # # ("999 1 +", 1000),
    # #           1000           |
    # yield "5 5 9 9 9 * + + + 5 5 + * 1 1 - +", 1000
    #
    # # ("1256 5761 *", 1024),
    # #           1256       |                   5761              |
    # yield "6 6 * 6 6 * * 5 8 * - 6 9 * 4 + 5 5 + * 5 5 + * 4 9 * 3 + - *", 7235816
    #
    # # Decimal results
    # yield "5 2 /", 2.5
    # yield "10 3 /", 3.3333333333333335
    #
    # # More complex mathematical expressions
    # yield "3 4 + 5 6 + * 7 -", 70
    # yield "2 3 ^ 4 5 ^ +", 1032
    # yield "10 2 8 * 3 + /", 0.5263157894736842
    #
    # # Testing operator precedence
    # yield "4 5 * 6 7 * +", 62
    # yield "3 4 5 * + 6 -", 17
    # yield "2 3 + 4 * 5 2 ^ -", 15
    #
    # yield really_why(), 80.08975794403399

    # # Edge cases that should raise errors
    # error_cases = [
    #     "",                # Empty expression
    #     "1 +",            # Not enough operands
    #     "1 2",            # No operator
    #     "1 0 /",          # Division by zero
    #     "+ - ",           # Only operators
    #     "1 2 3 +",        # Too many operands
    #     "a b +",          # Invalid tokens
    #     "1 2 &",          # Invalid operator
    #     "1.1.1 2 +",      # Malformed number
    #     "2 2 + +",        # Too many operators
    # ]
    #
    # for expression, expected in test_cases:
    #     result = get_result(exe=exe, rpn=expression)
    #     if result[0] == '':
    #         print('waarom', result[1], expression)
    #         continue
    #
    #     expected = np.float32(str(expected))
    #     result[0] = np.float32(result[0])
    #     try:
    #         np.testing.assert_almost_equal(
    #             np.float32(expected),
    #             np.float32(result[0]),
    #             decimal=2)
    #     except AssertionError:
    #         print(f"Failed: {expression} = {float(result[0])}, expected {expected}")
    #         exit(1)


def really_why():
    inputs = []
    for x in range(-9, 10):
        if x == 0:
            continue

        for y in range(abs(x)):
            inputs.append(str(x))

    operators = itertools.cycle(['*', '-', '/', '+'])
    for _ in range(len(inputs) - 1):
        inputs.append(next(operators))

    return ' '.join(inputs)


def run_tests(exe: Path):
    print('Start valid inputs test')
    for expression, expected in valid_inputs(exe=exe):
        result, err = get_result(exe=exe, rpn=expression)

        try:
            assert not err
        except AssertionError:
            print(f'Except that there are no errors, got: \'{
                  err}\'', file=sys.stderr)
            exit(1)

        try:
            result = np.float32(result)
            np.testing.assert_almost_equal(
                expected, result, decimal=2)
        except AssertionError:
            print(
                f'on input: \'{expression}\', we expect: \'{
                    expected:.2f}\', got: \'{result:.2f}\'',
                file=sys.stderr)
            exit(1)
    print('Pass valid inputs test')


if __name__ == '__main__':
    # subject_tester(exe='../RPN')
    run_tests(exe='../RPN')
