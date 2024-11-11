import subprocess
import sys
from typing import List, Generator, Tuple
from pathlib import Path
import numpy as np

import gen_rpn

INT_MIN = -9  # inclusive
INT_MAX = 10  # exclusive


def get_result(exe: Path, rpn: str, fail: bool = False) -> List[str]:
    result = subprocess.run(f'{exe} "{rpn}"',
                            shell=True,
                            capture_output=True,
                            text=True)

    stdout = result.stdout.strip()
    stderr = result.stderr.strip()

    try:
        if not fail:
            assert result.returncode == 0
        else:
            assert result.returncode != 0
    except AssertionError:
        if not fail:
            print(f'Expect returncode 0 got: {result.returncode}, stderr: {stderr}',
                  file=sys.stderr)
            exit(1)
        else:
            print(rpn)
            print(f'Expect returncode non 0 got: {result.returncode}, stderr: {stderr}',
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

    print('Start basic operations test')
    for expression, result in gen_rpn.basic_op_tester():
        yield expression, result
    print('Pass basic operations test\n')

    # Multiple operations
    print('Start multiple operations test')
    for x in range(3, 25):
        yield gen_rpn.multi_op_tester(x)
    print('Pass multiple operations test\n')

    # Zero handling
    print('Start valid zero test')
    for expression, result in gen_rpn.valid_zero_test():
        yield expression, result
    print('Pass valid zero test\n')

    print('Start single digit test')
    for x in range(INT_MIN, INT_MAX):
        yield str(x), x
    print('Pass single digit test\n')

    print('Start large numbers test')
    # "100 50 25 / *", 200
    yield "5 9 * 2 * 5 5 + + 5 9 * 5 + 5 5 * / *", 200
    yield "5 8 5 * *", 200

    # "999 1 +", 1000,
    yield "5 5 9 9 9 * + + + 5 5 + * 1 1 - +", 1000
    yield "5 5 5 8 * * *", 1000

    # "1256 5761 *", 1024
    yield "6 6 * 6 6 * * 5 8 * - 6 9 * 4 + 5 5 + * 5 5 + * 4 9 * 3 + - *", 7235816
    print('Pass large numbers test\n')

    print('Start decimal test')
    for expression, result in gen_rpn.decimals_tester(size=25):
        yield expression, result
    print('Pass decimal test')

    print('Start really why test')
    yield gen_rpn.really_why_test()
    print('Pass really why test')


def invalid_inputs(exe: Path):
    print('Start div by zero')
    for expression, result in gen_rpn.div_zero_test():
        yield expression, result
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


def run_tests(exe: Path):
    print('Start valid inputs test\n')
    for expression, expected in valid_inputs(exe=exe):
        result, err = get_result(exe=exe, rpn=expression)

        try:
            assert not err
        except AssertionError:
            print(f'{expression}')
            print(f'Except that there are no errors, got: \'{err}\'', file=sys.stderr)
            exit(1)

        try:
            result = np.float32(result)
            np.testing.assert_almost_equal(
                expected, result, decimal=2)
        except AssertionError:
            print(
                f'on input: \'{expression}\', we expect: \'{expected:.2f}\', got: \'{result:.2f}\'',
                file=sys.stderr)
            exit(1)
    print('\nPass valid inputs test\n')

    print('Start invalid test\n')
    for expression, _ in invalid_inputs(exe=exe):
        result, err = get_result(exe=exe, rpn=expression, fail=True)
        try:
            assert not result
        except AssertionError:
            print(f'Except that there are no messages on stdout, got: \'{result}\'', file=sys.stderr)
            exit(1)

        try:
            assert err
        except AssertionError:
            print(f'Except that there is a errors, got: \'{err}\'', file=sys.stderr)
            exit(1)


if __name__ == '__main__':
    # subject_tester(exe='../RPN')
    run_tests(exe='../RPN')
