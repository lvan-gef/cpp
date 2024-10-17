#! /usr/bin/env python3

from typing import Generator, Tuple
import json
import subprocess

# def gen_input():
# data = [
#     ['a', "char: 'a'\nint: 97\nfloat: 97.0f\ndouble: 97.0\n"],
# ]
# {"0", "char: Non displayable\nint: 0\nfloat: 0.0f\ndouble: 0.0\n"},
# {"2147483647", "char: Non displayable\nint: 2147483647\nfloat: 2147483647.0f\ndouble: 2147483647.0\n"},
# {"2147483648", "char: Non displayable\nint: impossible\nfloat: 2147483648.0f\ndouble: 2147483648.0\n"},
# {"42", "char: '*'\nint: 42\nfloat: 42.0f\ndouble: 42.0\n"},
# {"-42",
#  "char: Non displayable\nint: -42\nfloat: -42.0f\ndouble: -42.0\n"},
# {"4.2f", "char: Non displayable\nint: 4\nfloat: 4.2f\ndouble: 4.2\n"},
# {"4.", "char: Non displayable\nint: 4\nfloat: 4.0f\ndouble: 4.0\n"},
# {"4.2", "char: Non displayable\nint: 4\nfloat: 4.2f\ndouble: 4.2\n"},
# {"nan",
#  "char: Non displayable\nint: impossible\nfloat: nanf\ndouble: nan\n"},
# {"nanf",
#  "char: Non displayable\nint: impossible\nfloat: nanf\ndouble: nan\n"},
# {"+inf",
#  "char: Non displayable\nint: impossible\nfloat: inff\ndouble: +inf\n"},
# {"-inff", "char: Non displayable\nint: impossible\nfloat: "
#           "-inff\ndouble: -inf\n"},
# {"42.42.42", "Invalid input\n"}

# for d in data:
#     yield d


# def create_floating_map(ranges):
#     result = {}
#
#     for start, end, value in ranges:
#         result.update({i: value for i in range(start, end + 1)})
#
#     return result


# Define the ranges and their corresponding values
# ranges = [
#     (-2147483647, -2147483584, -2147483648),
#     (-2147483583, -2147483520, -2147483520)
# ]

# Define the complete range mappings
# ranges = [
#     (-2147483648, -2147483648, -2147483648),  # Minimum 32-bit integer value
#     (-2147483647, -2147483610, -2147483648),  # Your original range
#     (-2147483609, -2147483520, -2147483520.00),  # The range you mentioned
#     (-2147483519, -1073741824, None),  # Midpoint, assuming linear progression
#     (-1073741823, -1, None),  # Up to -1
#     (0, 0, 0)  # Zero
# ]

# floating_map = create_floating_map(ranges)

def create_floating_map(ranges):
    result = {}
    for start, end, value in ranges:
        result.update({i: value for i in range(start, end + 1)})
    return result


# Define the complete range mappings
ranges = [
    (-2147483648, -2147483648, -2147483648),  # Minimum 32-bit integer value
    (-2147483647, -2147483610, -2147483648),  # Your original range
    (-2147483609, -2147483520, -2147483520.00),  # The range you mentioned
    (-2147483519, -1073741824, None),  # Midpoint, assuming linear progression
    (-1073741823, -1, None),  # Up to -1
    (0, 0, 0)  # Zero
]


# Function to calculate float value for the middle ranges
def calculate_float(x):
    if -2147483519 >= x >= -1073741824:
        return float(x)
    elif -1073741823 >= x >= -1:
        return float(x)
    else:
        return x  # For values already specified


# Create the floating map
floating_map = create_floating_map(ranges)

# Fill in the calculated float values
for i in range(-2147483519, 0):
    floating_map[i] = calculate_float(i)

with open('float_mapping', 'w') as f:
    json.dump(floating_map, f, indent=4)


def gen_chars() -> Generator[Tuple[str, str], None, None]:
    # skip 0 it gives a error in python (NULL byte)
    for i in range(1, 128):
        if i < 32 or i > 126:
            output = f'char: Non displayable\nint: {i}\nfloat: {i}.00f\ndouble: {i}.00'
        else:
            output = f"char: '{chr(i)}'\nint: {i}\nfloat: {i}.00f\ndouble: {i}.00"
        yield chr(i), output


# nanf +inff -inff nan +inf -inf
def gen_int_space() -> Generator[Tuple[int, str], None, None]:
    for nbr in range(-2147483648, 2147483648):
        if nbr < 32 or nbr > 126:
            output = f'char: Non displayable\nint: {nbr}\nfloat: {nbr if nbr not in floating_map else floating_map[nbr]}.00f\ndouble: {nbr}.00'
        else:
            output = f'char: {chr(nbr)}\nint: {nbr}\nfloat: {nbr}.00f\ndouble: {nbr}.00'

        yield nbr, output


def test_char_input() -> None:
    print('The char test.')

    for ch, output in gen_chars():
        if ch in ['"', '\\', '`']:
            cmd = f"./scalarConverter '{ch}'"
        else:
            cmd = f'./scalarConverter "{ch}"'

        result = subprocess.run(
            cmd, shell=True, capture_output=True, text=True)
        stdout = result.stdout.rstrip()
        stderr = result.stderr

        try:
            assert stdout == output
        except AssertionError:
            print(f'Expected:\n{output}\n\nGot:\n{stdout}')
            print(f'stderr: {stderr}')
            exit(1)

    print('The char test passed\n')


def test_int_input() -> None:
    print('The int test')

    for nbr, output in gen_int_space():
        result = subprocess.run(
            f'./scalarConverter {nbr}', shell=True, capture_output=True, text=True)
        stdout = result.stdout.rstrip()
        stderr = result.stderr

        try:
            assert stdout == output
        except AssertionError:
            print(nbr)
            print(f'Expected:\n{output}\n\nGot:\n{stdout}')
            print(f'stderr: {stderr}')
            exit(1)

    print('The char test passed\n')


def main():
    test_char_input()
    test_int_input()


if __name__ == '__main__':
    main()
