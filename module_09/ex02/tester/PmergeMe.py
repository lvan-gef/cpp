
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

    for size in SIZES[:24]:
        for neg, r_str in zip(neg_nbr_gen, str_gen):
            pass


    # # neg and chars
    # for size in SIZES[1:24]:
    #     if random.randint(0, 1) % 2:
    #         yield ' '.join(
    #             next(str_gen) if random.randint(0, 1) % 2 else str(next(neg_nbr_gen))
    #             for _ in range(size)
    #         )
    #     else:
    #         yield ' '.join(
    #             str(next(neg_nbr_gen)) if random.randint(0, 1) % 2 else next(str_gen)
    #             for _ in range(size)
    #         )
    #
    # # pos and neg
    # for size in SIZES[1:24]:
    #     if random.randint(0, 1) % 2:
    #         yield ' '.join(
    #             str(next(pos_nbr_gen)) if random.randint(0, 1) % 2 else str(next(neg_nbr_gen))
    #             for _ in range(size)
    #         )
    #     else:
    #         yield ' '.join(
    #             str(next(neg_nbr_gen)) if random.randint(0, 1) % 2 else str(next(pos_nbr_gen))
    #             for _ in range(size)
    #         )
    #
    # # pos and char
    # for size in SIZES[1:24]:
    #     if random.randint(0, 1) % 2:
    #         yield ' '.join(
    #             str(next(pos_nbr_gen)) if random.randint(0, 1) % 2 else next(str_gen)
    #             for _ in range(size)
    #         )
    #     else:
    #         yield ' '.join(
    #             next(str_gen) if random.randint(0, 1) % 2 else str(next(pos_nbr_gen))
    #             for _ in range(size)
    #         )


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


# test_valid_input()

for x in test_invalid_input():
    pass
