#! /usr/bin/env python3

from datetime import datetime
from typing import List

DATE_FORMAT = '%Y-%m-%d'


def generate_invalid_dates() -> List[str]:
    """
    Generates various categories of invalid dates for testing purposes.
    Returns a dictionary with categories of invalid dates.
    """

    invalid_dates = {
        'impossible_days': [],
        'impossible_months': [],
        'invalid_leap_years': [],
        'malformed_dates': [],
        'out_of_range_dates': []
    }

    # Impossible days
    months_with_30_days = [4, 6, 9, 11]
    months_with_31_days = [1, 3, 5, 7, 8, 10, 12]

    # Add days that don't exist in specific months
    for month in months_with_30_days:
        invalid_dates['impossible_days'].append(f'2024-{month:02d}-31')

    # Add invalid days for months with 31 days (days > 31)
    for month in months_with_31_days:
        for day in range(32, 35):  # Add some days beyond 31
            invalid_dates['impossible_days'].append(
                f'2024-{month:02d}-{day:02d}')

    # February specific invalid dates
    invalid_dates['impossible_days'].extend([
        '2023-02-29',  # Invalid in non-leap year
        '2024-02-30',  # Invalid in any year
        '2024-02-31'   # Invalid in any year
    ])

    # Impossible months
    for month in range(13, 20):
        invalid_dates['impossible_months'].append(f'2024-{month:02d}-01')

    # Invalid leap year dates
    # Century years not divisible by 400
    non_leap_years = [1900, 2100, 2200, 2300]
    for year in non_leap_years:
        invalid_dates['invalid_leap_years'].append(f'{year}-02-29')

    # Malformed dates
    malformed_formats = [
        '2024/13/32',
        '2024.12.32',
        '24-13-32',
        '2024-0-0',
        '0000-00-00',
        'YYYY-MM-DD',
        '2024--01',
        '2024-01-',
        '-01-01',
        '-01',
        '-2024',
        '-2024-02',
        '-2024-02-',
        'hello',
        '',
    ]
    invalid_dates['malformed_dates'].extend(malformed_formats)

    # Out of range dates
    out_of_range = [
        '0000-01-01',
        '10000-01-01',
        '-2024-01-01',
        '2024-00-01',
        '2024-01-00'
    ]
    invalid_dates['out_of_range_dates'].extend(out_of_range)

    output = [f'{x} | 3' for _, v in invalid_dates.items() for x in v]
    return output


def validate_date(date_string: str) -> bool:
    """
    Validates if a given date string is valid.
    Returns True if valid, False if invalid.
    """

    try:
        datetime.strptime(date_string, DATE_FORMAT)
        return True
    except ValueError:
        return False
