#!/usr/bin/env bash

src_path=$(realpath "src/main.cpp")

insert_after_headers() {
    awk -v insert="$1" '
    BEGIN {
        found_last_include = 0
        last_include_line = 0
    }

    # Track the last #include line
    /^[[:space:]]*#[[:space:]]*include/ {
        last_include_line = NR
        found_last_include = 1
    }

    # Store all lines
    {
        lines[NR] = $0
    }

    END {
        # If we found includes, insert after the last one
        if (found_last_include) {
            for (i = 1; i <= NR; i++) {
                print lines[i]
                if (i == last_include_line) {
                    print ""  # Empty line for better formatting
                    print insert
                }
            }
        } else {
            # If no includes found, insert at the beginning
            print insert
            for (i = 1; i <= NR; i++) {
                print lines[i]
            }
        }
    }' "$2"
}

find_missing() {
    awk -v pat="$1" '
    BEGIN {
        split(pat, patterns, " ");
        for (i in patterns) {
            not_found[patterns[i]] = 1;
        }
    }

    {
        for (i in patterns) {
            if (index($0, patterns[i])) {
                delete not_found[patterns[i]];
            }
        }
    }

    END {
        for (p in not_found) {
            print "    " p;
        }
    }' "$2"
}

if [ ! -f "$src_path" ]; then
    echo "No file main.cpp to swap"
    exit 1
fi

user_input="$1"
filters=('#include "../tester/include/tester.hpp"' 'testEasyFind();')

if [ "$user_input" == "build" ]; then
    sed_string=''
    for element in "${filters[@]}"; do
        sed_string+="/${element//\//\\/}/d;"
    done
    sed -i "$sed_string" "$src_path"
    exit 0
fi

if [ "$user_input" == "test" ]; then
    if ! grep -qF -- "${filters[0]}" "$src_path"; then
        tmp=$(insert_after_headers "${filters[0]}" "$src_path")
        echo "$tmp" > tmp_cpp
        found_include=1
    fi

    testers=$(printf "%s " "${filters[@]:1}")
    missing_testers=$(find_missing "$testers" "$src_path")
    if [ "$missing_testers" == "" ] && [ -z ${found_include+x} ]; then
        exit 0
    fi

    if [ "$missing_testers" != "" ]; then
        if [ -z ${found_include+x} ]; then
            cat "$src_path" > tmp_cpp
        fi

        tmp=$(insert_above "$missing_testers" "tmp_cpp")
        if [ "$tmp" != "" ]; then
            echo "$tmp" > tmp_cpp
        fi
    fi

    if [ -f "tmp_cpp" ]; then
        mv tmp_cpp "$src_path"
    fi

    exit 0
fi

exit 1
