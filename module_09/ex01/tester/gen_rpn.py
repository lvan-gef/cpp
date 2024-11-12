from typing import Generator, Tuple
import itertools
import collections

import numpy as np

OPERATORS = ('+', '-', '*', '/')
INT_MIN = -9  # inclusive
INT_MAX = 10  # exclusive


def _do_op(op: str, lhs: np.float32, rhs: np.float32) -> np.float32:
    match op:
        case '+':
            return np.float32(lhs + rhs)
        case '-':
            return np.float32(lhs - rhs)
        case '*':
            return np.float32(lhs * rhs)
        case '/':
            if rhs == 0:
                raise Exception
            else:
                return np.float32(lhs / rhs)
        case _:
            raise Exception('Unkown operator in tester')


def basic_op_tester() -> Generator[Tuple[str, np.float32], None, None]:
    for op in OPERATORS:
        for neg in range(INT_MIN, 0):
            yield f'{neg} {neg} {op}', _do_op(op, np.float32(neg), np.float32(neg))

            for pos in range(1, INT_MAX):
                yield f'{neg} {pos} {op}', _do_op(op, np.float32(neg), np.float32(pos))
                yield f'{pos} {neg} {op}', _do_op(op, np.float32(pos), np.float32(neg))

        for pos in range(1, INT_MAX):
            yield f'{pos} {pos} {op}', _do_op(op, np.float32(pos), np.float32(pos))


def multi_op_tester(size: int) -> Tuple[str, np.float32]:
    if size < 2:
        assert size >= 2

    op_cycle = itertools.cycle(OPERATORS)
    neg_cycle = itertools.cycle(range(INT_MIN, 0))
    pos_cycle = itertools.cycle(range(1, INT_MAX))

    output = collections.deque()
    expression = []
    for count in range(size):
        for neg in neg_cycle:
            output.append(neg)
            expression.append(neg)
            count += 1

            for pos in pos_cycle:
                output.append(pos)
                expression.append(pos)
                break
            break

    while len(output) > 1:
        last = output.pop()
        second = output.pop()

        op = next(op_cycle)
        try:
            output.append(_do_op(op=op, lhs=np.float32(second), rhs=np.float32(last)))
            expression.append(op)
        except Exception:
            output.append(second)
            output.append(last)
            continue

    assert len(output) == 1

    result = output.pop()
    return ' '.join((str(x) for x in expression)), result


def valid_zero_test() -> Generator[Tuple[str, np.float32], None, None]:
    for op in OPERATORS[:3]:
        for neg in range(INT_MIN, 1):
            yield f'{neg} {0} {op}', _do_op(op=op, lhs=np.float32(neg), rhs=np.float32(0))
            yield f'{0} {neg} {op}', _do_op(op=op, lhs=np.float32(0), rhs=np.float32(neg))

            for pos in range(0, INT_MAX):
                yield f'{pos} {0} {op}', _do_op(op=op, lhs=np.float32(pos), rhs=np.float32(0))
                yield f'{0} {pos} {op}', _do_op(op=op, lhs=np.float32(0), rhs=np.float32(pos))


def div_zero_test() -> Generator[Tuple[str, bool], None, None]:
    for nbr in range(INT_MIN, INT_MAX):
        yield f'{nbr} 0 /', False

    yield '0 0 0 0 0 + - - /', False
    yield '1 1 1 1 1 + - + /', False
    yield '2 2 2 2 2 + - + /', False
    yield '3 3 3 3 3 + - + /', False
    yield '4 4 4 4 4 + - + /', False
    yield '5 5 5 5 5 + - + /', False
    yield '6 6 6 6 6 + - + /', False
    yield '7 7 7 7 7 + - + /', False
    yield '8 8 8 8 8 + - + /', False
    yield '9 9 9 9 9 + - + /', False
    yield '-9 1 -8 2 -7 3 -6 4 -5 5 -4 6 -3 7 -2 8 -1 9 + - * / + - * / + - * / + - * / +', False


def decimals_tester(size: int = 25) -> Generator[Tuple[str, np.float32], None, None]:
    neg_cycle = itertools.cycle(range(INT_MIN, 0))
    pos_cycle = itertools.cycle(range(1, INT_MAX))

    for _ in range(size):
        for neg in neg_cycle:
            if neg % 2 == 0:
                continue

            for pos in pos_cycle:
                if pos % 2 != 0:
                    continue

                result = _do_op(op='/', lhs=np.float32(neg), rhs=np.float32(pos))
                if not result.is_integer():
                    yield f'{neg} {pos} /', result

                result = _do_op(op='/', lhs=np.float32(pos), rhs=np.float32(neg))
                if not result.is_integer():
                    yield f'{pos} {neg} /', result
                break

            break


def invalid_tester() -> Generator[Tuple[str, bool], None, None]:
    invalids = [
        '',
        '1 /',
        '1 2',
        '+ -',
        '*',
        '- 1',
        '- 7 7'
        '3 4 5 +',
        'a b',
        'a b +'
        '1 c',
        '1 c -',
        '2 d',
        '2 d *'
        '10 0 +',
        '10 0 -',
        '1 2 &',
        '1.1.1 2 +',
        '1.2 2 +',
        '8. 9 +',
        '6 7 + +'
    ]

    for invalid in invalids:
        yield invalid, False


def really_why_test() -> Tuple[str, np.float32]:
    output = collections.deque()
    expression = []
    op_cycle = itertools.cycle(OPERATORS)

    for x in range(-9, 10):
        if x == 0:
            continue

        for _ in range(abs(x)):
            output.append(x)
            expression.append(x)


    while len(output) > 1:
        last = output.pop()
        second = output.pop()

        op = next(op_cycle)
        try:
            output.append(_do_op(op=op, lhs=np.float32(second), rhs=np.float32(last)))
            expression.append(op)
        except Exception:
            output.append(second)
            output.append(last)
            continue

    assert len(output) == 1

    result = output.pop()
    return ' '.join((str(x) for x in expression)), result
