#! /usr/bin/env python3

import subprocess

def gen_input():
    data = [
        ['a', "char: 'a'\nint: 97\nfloat: 97.0f\ndouble: 97.0\n"],
    ]
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

    for d in data:
        yield d

def main():
    for gi in gen_input():
        result = subprocess.run(f'./scalarConverter {gi[0]}', shell=True, capture_output=True)
        print(result.stdout.decode())

if __name__ == '__main__':
    main()
