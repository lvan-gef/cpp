

import subprocess

for index in range(10000000000):
    result = subprocess.run('./identify', shell=True, capture_output=True)
    if result.returncode != 0:
        print('error!!!!', index)
        exit(100)
