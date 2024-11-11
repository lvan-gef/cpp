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
                rhs = 1
            return np.float32(lhs / rhs)


def basic_op_tester() -> Generator[Tuple[str, np.float32], None, None]:
    for op in OPERATORS:
        for neg in range(INT_MIN, 0):
            yield f'{neg} {neg} {op}', _do_op(op, neg, neg)

            for pos in range(1, INT_MAX):
                yield f'{neg} {pos} {op}', _do_op(op, neg, pos)
                yield f'{pos} {neg} {op}', _do_op(op, pos, neg)


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
        expression.append(op)
        output.append(_do_op(op, np.float32(second), np.float32(last)))

    assert len(output) == 1

    result = output.pop()
    return ' '.join((str(x) for x in expression)), result
