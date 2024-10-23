#!/usr/bin/env bash

src_path=$(realpath "src/main.cpp")

insert_above() {
	awk -v insert="$1" -v target="return" -- '
	{ lines[NR] = $0 }

	$0 ~ target {
		last_match = NR
	}

	END {
		for (i = 1; i <= NR; i++) {
			if (i == last_match) {
				print insert
			}
			print lines[i]
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
filters=('#include "../tester/include/tester.hpp"' 'testMax();')

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
		echo "${filters[0]}" > tmp_cpp
	fi

	testers=$(printf "%s " "${filters[@]:1}")
	missing_testers=$(find_missing "$testers" "$src_path")
	if [ "$missing_testers" == "" ]; then
		exit 0
	fi
	tmp=$(insert_above "$missing_testers" "$src_path")
	if [ "$tmp" != "" ]; then
		echo "$tmp" >> tmp_cpp
	else
		cat "$src_path" >> tmp_cpp
	fi

	if [ -f "tmp_cpp" ]; then
		mv tmp_cpp "$src_path"
	fi

	exit 0
fi

exit 1
