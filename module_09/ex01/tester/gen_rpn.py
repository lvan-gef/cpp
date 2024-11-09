from itertools import product, permutations
from typing import Generator


def valid_rpn(numbers: list[int]) -> Generator[str, None, None]:
    operators = ['*', '/', '+', '-']
    n = len(numbers)

    number_permutations = set(permutations(numbers))

    for num_perm in number_permutations:
        operator_combinations = product(operators, repeat=n - 1)

        for ops in operator_combinations:
            expr = list(map(str, num_perm)) + list(ops)
            yield ' '.join(expr)
