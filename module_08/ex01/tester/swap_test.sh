#!/usr/bin/env bash

src_path=$(realpath "src/main.cpp")

# Function to add test code
add_test_code() {
    local file="$1"
    local main_content
    main_content=$(cat "$file")

    # Add include if it's not there
    if ! grep -q '#include "../tester/include/tester.hpp"' "$file"; then
        sed -i '1i\#include "../tester/include/tester.hpp"\n' "$file"
    fi

    # Add test code in main if it's not there
    if ! grep -q 'randomVector(amount)' "$file"; then
        # Insert after main's opening brace while preserving everything else
        awk '/int main\(int argc, char \*\*argv\).*{/ {
            print
            print "    if (argc != 2) {"
            print "        std::cerr << \"Expect 1 argument got: \" << argc << std::endl;"
            print "        return 1;"
            print "    }"
            print ""
            print "    int amount = std::atoi(argv[1]);"
            print ""
            print "    auto start = std::chrono::high_resolution_clock::now();"
            print "    std::vector<int> rv = randomVector(amount);"
            print "    auto end = std::chrono::high_resolution_clock::now();"
            print "    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);"
            print "    std::cout << \"Create random data<\" << amount << \"> duration: \" << duration.count() << \" milliseconds\" << '\\n';"
            print ""
            print "    start = std::chrono::high_resolution_clock::now();"
            print "    Span x = Span(rv.begin(), rv.end());"
            print "    end = std::chrono::high_resolution_clock::now();"
            print "    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);"
            print "    std::cout << \"Add           data<\" << amount << \"> duration: \" << duration.count() << \" milliseconds\" << '\\n';"
            print ""
            print "    start = std::chrono::high_resolution_clock::now();"
            print "    x.printer();"
            print "    end = std::chrono::high_resolution_clock::now();"
            print "    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);"
            print "    std::cout << \"Print         data<\" << amount << \"> duration: \" << duration.count() << \" milliseconds\" << '\\n';"
            print ""
            print "    start = std::chrono::high_resolution_clock::now();"
            print "    unsigned int shortes = x.shortestSpan();"
            print "    end = std::chrono::high_resolution_clock::now();"
            print "    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);"
            print "    std::cout << \"Shortes       span<\" << amount << \"> duration: \" << duration.count() << \" milliseconds\" << '\\n';"
            print ""
            print "    start = std::chrono::high_resolution_clock::now();"
            print "    unsigned int longest = x.longestSpan();"
            print "    end = std::chrono::high_resolution_clock::now();"
            print "    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);"
            print "    std::cout << \"Longest       span<\" << amount << \"> duration: \" << duration.count() << \" milliseconds\" << \\'\\n\\';"
            next
        }
        { print }' "$file" > "${file}.tmp" && mv "${file}.tmp" "$file"
    fi
}

# Function to remove test code
remove_test_code() {
    local file="$1"

    # Create a temporary file
    local tmp_file="${file}.tmp"

    # Remove the include line while preserving newlines
    sed '/#include "\.\.\/tester\/include\/tester\.hpp"/d' "$file" > "$tmp_file"

    # Remove the test code lines while preserving structure
    awk '
    /if \(argc != 2\)/ { skip = 1; next }
    /std::cout << longest << std::endl;/ { skip = 0; next }
    !skip { print }
    ' "$tmp_file" > "${tmp_file}.2"

    # Move the cleaned file back
    mv "${tmp_file}.2" "$file"
    rm -f "$tmp_file"
}

if [ ! -f "$src_path" ]; then
    echo "No file main.cpp to swap"
    exit 1
fi

case "$1" in
    "test")
        add_test_code "$src_path"
        sed -i s/subject_test\(true\)/subject_test\(false\)/g "$src_path"
        ;;
    "build")
        remove_test_code "$src_path"
        sed -i s/subject_test\(false\)/subject_test\(true\)/g "$src_path"
        ;;
    *)
        exit 1
        ;;
esac

exit 0
