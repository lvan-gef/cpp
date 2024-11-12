import argparse
import subprocess
import sys
from typing import List, Generator, Tuple
from pathlib import Path
import numpy as np

import gen_rpn

INT_MIN = -9  # inclusive
INT_MAX = 10  # exclusive


def error_out(msg: str, rpn: str):
    print(f'On input: "{rpn}:\n{msg}', file=sys.stderr)
    exit(1)


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
            error_out(
                msg=f'Expect returncode 0 got: {result.returncode}, stderr: {stderr}',
                rpn=rpn)
        else:
            error_out(
                msg=f'Expect returncode non 0 got: {result.returncode}, stderr: {stderr}',
                rpn=rpn)

    return [stdout, stderr]


def gen_valid_input() -> Generator[Tuple[str, np.float32], None, None]:

    print('    Start basic operations test')
    for expression, result in gen_rpn.basic_op_tester():
        yield expression, result
    print('    Pass basic operations test\n')

    # Multiple operations
    print('    Start multiple operations test')
    for x in range(3, 500):
        yield gen_rpn.multi_op_tester(x)
    print('    Pass multiple operations test\n')

    # Zero handling
    print('    Start valid zero test')
    for expression, result in gen_rpn.valid_zero_test():
        yield expression, result
    print('    Pass valid zero test\n')

    print('    Start single digit test')
    for x in range(INT_MIN, INT_MAX):
        yield str(x), np.float32(x)
    print('    Pass single digit test\n')

    print('    Start large numbers test')
    # "100 50 25 / *", 200
    yield "5 9 * 2 * 5 5 + + 5 9 * 5 + 5 5 * / *", np.float32(200)
    yield "5 8 5 * *", np.float32(200)

    # "999 1 +", 1000,
    yield "5 5 9 9 9 * + + + 5 5 + * 1 1 - +", np.float32(1000)
    yield "5 5 5 8 * * *", np.float32(1000)

    # "1256 5761 *", 1024
    yield "6 6 * 6 6 * * 5 8 * - 6 9 * 4 + 5 5 + * 5 5 + * 4 9 * 3 + - *", np.float32(7235816)
    print('    Pass large numbers test\n')

    print('    Start decimal test')
    for expression, result in gen_rpn.decimals_tester(size=25):
        yield expression, result
    print('    Pass decimal test\n')

    print('    Start really why test')
    yield gen_rpn.really_why_test()
    print('    Pass really why test\n')

    print('    Start subject valid test')
    yield '8 9 * 9 - 9 - 9 - 4 - 1 +', np.float32(42)
    yield '7 7 * 7 -', np.float32(42)
    yield '1 2 * 2 / 2 * 2 4 - +', np.float32(0)
    print('    Pass subject valid test')


def invalid_inputs():
    print('    Start div by zero')
    for expression, result in gen_rpn.div_zero_test():
        yield expression, result
    print('    Pass div by zero\n')

    print('    Start some other things test')
    for expression, result in gen_rpn.invalid_tester():
        yield expression, result
    print('    Pass some other things test\n')

    print('    Start subject invalid test')
    yield '(1 + 1)', False
    print('    Pass subject invalid test')


def run_tests(exe: Path):
    print('Start valid inputs test')
    for expression, expected in gen_valid_input():
        stdout, stderr = get_result(exe=exe, rpn=expression)

        try:
            assert not stderr
        except AssertionError:
            error_out(
                msg=f'Expect no message on stderr, got: \'{stderr}\'',
                rpn=expression)

        try:
            assert stdout
        except AssertionError:
            error_out(
                msg=f'Expect message on stdout, got: \'{stdout}\'',
                rpn=expression)

        try:
            stdout = np.float32(stdout)
            np.testing.assert_almost_equal(
                expected, stdout, decimal=2)
        except AssertionError:
            error_out(
                msg=f'Expect: \'{expected:.2f}\', got: \'{stdout:.2f}\'',
                rpn=expression)
        except Exception as e:
            error_out(
                msg=f'Unkown error: \'{e}\'',
                rpn=expression)

    print('Pass valid inputs test\n')

    print('Start invalid test')
    for expression, _ in invalid_inputs():
        stdout, stderr = get_result(exe=exe, rpn=expression, fail=True)
        try:
            assert not stdout
        except AssertionError:
            error_out(
                msg=f'Expect no message on stdout, got: \'{stdout}\'',
                rpn=expression)

        try:
            assert stderr
        except AssertionError:
            error_out(
                msg=f'Expect message on stderr, got: \'{stderr}\'',
                rpn=expression)

        try:
            assert stderr.lower().startswith('error')
        except AssertionError:
            error_out(
                msg=f'Expect message to startswith: \'error\', got: \'{stderr}\'',
                rpn=expression)
    print('Pass invalid test')


if __name__ == '__main__':
    parser = argparse.ArgumentParser(
                    prog='rpn tester',
                    description='A simple tester for Codam cpp 09 ex01',
                    epilog='Good luck with it')
    parser.add_argument('filename', help='The path to the rpn exe')
    args = parser.parse_args()
    rpn_path = Path(args.filename).resolve()
    if not rpn_path.exists():
        print(f'Could not find the exe: {rpn_path}')
        exit(1)

    run_tests(exe=rpn_path)
