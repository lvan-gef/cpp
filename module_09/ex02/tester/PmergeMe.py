#! /usr/bin/env python3

import random
from typing import Generator
import time
import string


INT_MAX = 2147483647
INT_MIN = -2147483648
SIZES = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 13, 21, 35, 42, 55, 69, 78, 87, 96,
         100, 1_000, 20_000, 300_000, 4_000_000, 10_000_000]


def _gen_nbr(start: int, end: int) -> Generator[int, None, None]:
    while True:
        yield random.randint(start, end)


def _gen_chars(min_length: int, max_length: int) -> Generator[str, None, None]:
    while True:
        length = random.randint(min_length, max_length)
        yield ''.join(random.choices(string.ascii_letters, k=length))


def test_invalid_input():
    neg_nbr_gen = _gen_nbr(start=INT_MIN, end=-1)
    pos_nbr_gen = _gen_nbr(start=0, end=INT_MAX)
    str_gen = _gen_chars(min_length=1, max_length=10)


    # only negative numbers
    for size in SIZES[:24]:
        yield ' '.join(
            str(next(neg_nbr_gen))
            for _ in range(size)
        )

    # only chars
    for size in SIZES[:24]:
        yield ' '.join(
            next(str_gen)
            for _ in range(size)
        )

    # first char then number and vica versa
    for index, size in enumerate(SIZES[:24]):
        if index % 2 == 0:
            yield f'{next(str_gen)} {' '.join(next(str_gen) if random.randint(1, 2) % 2 else str(next(neg_nbr_gen)) for _ in range(size - 1))}'
        else:
            yield f'{next(neg_nbr_gen)} {' '.join(next(str_gen) if random.randint(1, 2) % 2 else str(next(neg_nbr_gen)) for _ in range(size - 1))}'

    # first valid numbers last one is invalid
    for index, size in enumerate(SIZES[1:24]):
        valid_inputs = [next(pos_nbr_gen) for _ in range(size - 1)]
        valid_inputs.append(next(neg_nbr_gen))
        yield ' '.join(str(x) for x in valid_inputs)

        valid_inputs.pop(-1)
        valid_inputs.append(next(str_gen))
        yield ' '.join(str(x) for x in valid_inputs)

    yield ''
    yield '   '

def test_valid_input():
    gen = _gen_nbr(start=0, end=INT_MAX)

    for size in SIZES:
        inputs = [
            next(gen)
            for _ in range(size)
        ]

        start = time.time()
        output = sorted(inputs)
        end = time.time()

        print('Duur:', end - start)
        yield ' '.join(str(x) for x in inputs)


for valid in test_valid_input():
    pass

for invalid in test_invalid_input():
    pass
    # print(x)
