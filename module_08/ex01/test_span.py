#! /usr/bin/python3

import subprocess


def run(many: int):
    result = subprocess.run(
        f'./span {many}',
        shell=True,
        capture_output=True,
        text=True)

    assert result.returncode == 0
    assert result.stdout != ''
    assert result.stderr != ''

    data = [
        int(nbr)
        for nbr in result.stderr.split('\n')
        if nbr
    ]

    print(data)
    spans = [abs(data[i + 1]) - abs(data[i]) for i in range(len(data) - 1)]
    shortest_span = min(spans)
    longest_span = max(spans)

    try:
        assert result.stdout == f'{shortest_span}\n{longest_span}\n'
    except AssertionError:
        print(f'except:\n{shortest_span}\n{
              longest_span}\n\ngot:\n{result.stdout}')


run(100)
