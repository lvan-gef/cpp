#! /usr/bin/env python3

from typing import Generator, Tuple
import subprocess
import numpy
import struct


def to_float32(value):
    return struct.unpack('f', struct.pack('f', value))[0]


def gen_chars() -> Generator[Tuple[str, str], None, None]:
    # skip 0 it gives a error in python (NULL byte)
    for i in range(1, 128):
        if i < 32 or i > 126:
            output = f'char: Non displayable\nint: impossible\nfloat: impossible\ndouble: impossible'
        elif i >= 48 and i <= 57:
            output = f"char: Non displayable\nint: {i - 48}\nfloat: {i - 48}.00f\ndouble: {i - 48}.00"
        else:
            output = f"char: '{chr(i)}'\nint: impossible\nfloat: impossible\ndouble: impossible"

        yield chr(i), output


def gen_int_space() -> Generator[Tuple[int, str], None, None]:
    # for nbr in range(-2147483648, 2147483648):
    for nbr in range(-200, 201):
        if nbr < 0 or nbr > 127:
            output = f'char: impossible\nint: {nbr}\nfloat: {numpy.float32(nbr):.2f}f\ndouble: {nbr}.00'
        elif nbr < 32 or nbr == 127:
            output = f'char: Non displayable\nint: {nbr}\nfloat: {numpy.float32(nbr):.2f}f\ndouble: {nbr}.00'
        else:
            output = f"char: '{chr(nbr)}'\nint: {nbr}\nfloat: {numpy.float32(nbr):.2f}f\ndouble: {nbr}.00"

        yield nbr, output

    yield 12312313213123, f'char: impossible\nint: impossible\nfloat: {numpy.float32(12312313213123):.2f}f\ndouble: 12312313213123.00'
    yield 2147483648, f'char: impossible\nint: impossible\nfloat: {numpy.float32(2147483648):.2f}f\ndouble: {to_float32(2147483648):.2f}'
    yield -2147483649, f'char: impossible\nint: impossible\nfloat: {numpy.float32(-2147483649):.2f}f\ndouble: -2147483649.00'


def gen_nan_inf() -> Generator[Tuple[int, str], None, None]:
    yield 'nan', 'char: impossible\nint: impossible\nfloat: nanf\ndouble: nan'
    yield 'nanf', 'char: impossible\nint: impossible\nfloat: nanf\ndouble: nan'
    yield 'inf', 'char: impossible\nint: impossible\nfloat: inff\ndouble: inf'
    yield 'inff', 'char: impossible\nint: impossible\nfloat: inff\ndouble: inf'
    yield '+inf', 'char: impossible\nint: impossible\nfloat: inff\ndouble: inf'
    yield '+inff', 'char: impossible\nint: impossible\nfloat: inff\ndouble: inf'
    yield '-inf', 'char: impossible\nint: impossible\nfloat: -inff\ndouble: -inf'
    yield '-inff', 'char: impossible\nint: impossible\nfloat: -inff\ndouble: -inf'


def gen_edge_cases() -> Generator[Tuple[str, str], None, None]:
    # Extreme values
    yield 2147483647, 'char: impossible\nint: 2147483647\nfloat: 2147483648.00f\ndouble: 2147483647.00'
    yield -2147483648, 'char: impossible\nint: -2147483648\nfloat: -2147483648.00f\ndouble: -2147483648.00'
    yield 2147483648, 'char: impossible\nint: impossible\nfloat: 2147483648.00f\ndouble: 2147483648.00'
    yield -2147483649, 'char: impossible\nint: impossible\nfloat: -2147483648.00f\ndouble: -2147483649.00'

    # Float edge cases
    yield '340282346638528859811704183484516925440.0f', 'char: impossible\nint: impossible\nfloat: 340282346638528859811704183484516925440.00f\ndouble: 340282346638528859811704183484516925440.00'
    yield '-340282346638528859811704183484516925440.0f', 'char: impossible\nint: impossible\nfloat: -340282346638528859811704183484516925440.00f\ndouble: -340282346638528859811704183484516925440.00'

    # Special cases
    yield '+0', 'char: Non displayable\nint: 0\nfloat: 0.00f\ndouble: 0.00'
    yield '-0', 'char: Non displayable\nint: 0\nfloat: -0.00f\ndouble: -0.00'
    yield '0.0f', 'char: Non displayable\nint: 0\nfloat: 0.00f\ndouble: 0.00'
    yield '-0.0f', 'char: Non displayable\nint: 0\nfloat: -0.00f\ndouble: -0.00'

    # Floating point precision
    yield '0.1f', 'char: Non displayable\nint: 0\nfloat: 0.10f\ndouble: 0.10'
    yield '0.2f', 'char: Non displayable\nint: 0\nfloat: 0.20f\ndouble: 0.20'
    yield '0.3f', 'char: Non displayable\nint: 0\nfloat: 0.30f\ndouble: 0.30'

    # Scientific notation
    yield '1e-40', 'char: Non displayable\nint: 0\nfloat: 0.00f\ndouble: 0.00'
    yield '1e-40f', 'char: Non displayable\nint: 0\nfloat: 0.00f\ndouble: 0.00'
    yield '1e40', 'char: Non displayable\nint: impossible\nfloat: inff\ndouble: 10000000000000000303786028427003666890752.00'
    yield '3.14159e0', 'char: Non displayable\nint: 3\nfloat: 3.14f\ndouble: 3.14'
    yield '6.022e23', f'char: Non displayable\nint: impossible\nfloat: {numpy.float32("6.022e23"):.2f}f\ndouble: 602200000000000027262976.00'
    yield '5e-2', 'char: Non displayable\nint: 0\nfloat: 0.05f\ndouble: 0.05'
    yield '1e', 'char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible'
    yield '1e+', 'char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible'
    yield '1e-', 'char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible'

    yield '1e-45', 'char: Non displayable\nint: 0\nfloat: 0.00f\ndouble: 0.00'
    yield '-1e-45', 'char: impossible\nint: 0\nfloat: -0.00f\ndouble: -0.00'

    yield '42.0f', "char: '*'\nint: 42\nfloat: 42.00f\ndouble: 42.00"


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

    print('The int test passed\n')


def test_nan_inf_input():
    print('The nan and inf test')
    for inpt, output in gen_nan_inf():
        result = subprocess.run(
            f'./scalarConverter {inpt}', shell=True, capture_output=True, text=True)
        stdout = result.stdout.rstrip()
        stderr = result.stderr

        try:
            assert stdout == output
        except AssertionError:
            print(inpt)
            print(f'Expected:\n{output}\n\nGot:\n{stdout}')
            print(f'stderr: {stderr}')
            exit(1)

    print('The nan and inf test passed')


def test_edge_cases():
    print('The edge cases test')

    for input_value, expected_output in gen_edge_cases():
        result = subprocess.run(
            f'./scalarConverter {input_value}', shell=True, capture_output=True, text=True)
        stdout = result.stdout.rstrip()
        stderr = result.stderr

        try:
            assert stdout == expected_output
        except AssertionError:
            print(f'Input: {input_value}')
            print(f'Expected:\n{expected_output}\n\nGot:\n{stdout}')
            print(f'stderr: {stderr}')
            exit(1)

    print('The edge cases test passed\n')


def main():
    test_char_input()
    test_int_input()
    test_nan_inf_input()
    test_edge_cases()


if __name__ == '__main__':
    main()
