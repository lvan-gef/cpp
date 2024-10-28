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

    assert data == list(sorted(data))

    spans = []
    for i in range(len(data[:-2])):
        for j in range(i + 1, len(data[:-2])):
            span = abs(data[j] - data[i])
            spans.append(span)

    shortest_span = min(spans)

    lowest = min(data)
    highest = max(data)

    longest_span = abs(highest - lowest)
    # print(f"Shortest span: {shortest_span}")
    # print(f"Longest span: {longest_span}")
    # print(f"Between numbers: {lowest} and {highest}")

    try:
        assert result.stdout == f'{shortest_span}\n{longest_span}\n'
    except AssertionError:
        print(f'except:\n{shortest_span}\n{ longest_span}\n\ngot:\n{result.stdout}')
        with open('error_list.txt', 'w') as f:
            f.write('\n'.join((str(x) for x in data)))
        exit(1)


inputs = [1, 10, 100, 1_000, 10_000, 100_000, 1_000_000]
for ip in inputs[1:]:
    print(f'Start test with: {ip} numbers')
    run(ip)
    print(f'Pass test with: {ip} numbers')
