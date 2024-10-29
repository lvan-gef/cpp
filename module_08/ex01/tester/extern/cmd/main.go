package main

import (
	"bufio"
	"fmt"
	"log"
	"math"
	"os"
	"os/exec"
	"sort"
	"strconv"
	"strings"
)

func findShortestSpan(sortedData []int) uint64 {
	if len(sortedData) < 2 {
		return math.MaxUint64
	}

	shortestSpan := uint64(math.MaxUint64)

	// Since the data is sorted, the shortest span must be between some adjacent numbers
	for i := 1; i < len(sortedData); i++ {
		span := uint64(sortedData[i] - sortedData[i-1]) // No abs needed since data is sorted
		if span < shortestSpan {
			shortestSpan = span
		}
	}

	return shortestSpan
}

func run(spanPath string, many int) error {
	cmd := exec.Command(spanPath, strconv.Itoa(many))

	stdout, err := cmd.StdoutPipe()
	if err != nil {
		return fmt.Errorf("failed to get stdout pipe: %v", err)
	}

	stderr, err := cmd.StderrPipe()
	if err != nil {
		return fmt.Errorf("failed to get stderr pipe: %v", err)
	}

	if err := cmd.Start(); err != nil {
		return fmt.Errorf("failed to start command: %v", err)
	}

	var data []int
	scanner := bufio.NewScanner(stderr)
	for scanner.Scan() {
		line := strings.TrimSpace(scanner.Text())
		if line == "" {
			continue
		}

		num, err := strconv.Atoi(line)
		if err != nil {
			return fmt.Errorf("failed to convert string to int: %v", err)
		}
		data = append(data, num)
	}

	if !sort.IntsAreSorted(data) {
		return fmt.Errorf("data is not sorted")
	}

	outScanner := bufio.NewScanner(stdout)
	var outputLines []string
	for outScanner.Scan() {
		outputLines = append(outputLines, outScanner.Text())
	}

	if err := cmd.Wait(); err != nil {
		return fmt.Errorf("command failed: %v", err)
	}

	shortestSpan := findShortestSpan(data)

	if shortestSpan == math.MaxUint64 {
		return fmt.Errorf("shortest_span == unsigned int max so something went wrong")
	}

	longestSpan := uint64(data[len(data)-1] - data[0])

	expectedOutput := fmt.Sprintf("%d\n%d\n", shortestSpan, longestSpan)
	actualOutput := strings.Join(outputLines, "\n") + "\n"

	if expectedOutput != actualOutput {
		f, err := os.Create("error_list.txt")
		if err != nil {
			return fmt.Errorf("failed to create error file: %v", err)
		}
		defer f.Close()

		for _, num := range data {
			fmt.Fprintf(f, "%d\n", num)
		}

		return fmt.Errorf("output mismatch\nexpected:\n%sgot:\n%s", expectedOutput, actualOutput)
	}

	return nil
}

func main() {
	spanPath := "./span"
	if len(os.Args) > 1 {
		spanPath = os.Args[1]
	}

	if _, err := os.Stat(spanPath); os.IsNotExist(err) {
		log.Fatalf("Span executable not found at: %s", spanPath)
	}

	fmt.Printf("Using span executable: %s\n", spanPath)
    // 100000000, takes 04:30 minutes to create and find it (cpp code) and 4.84 GiB (ryzen 5 5600x)  golang 2.47 GIB
    // 100000000, takes 15:33 minutes to create and find it (cpp code) and 4.84 GiB (rpi cortex A72) golang 2.47 GIB


    // 10000000, takes 00:21 minutes to create and find it (cpp code) and 499 MIB (ryzen 5 5600x)  golang 210 MIB
    // 10000000, takes 01:18 minutes to create and find it (cpp code) and 499 MIB (rpi cortex A72) golang 211 MIB
	inputs := []int{1, 10, 100, 1000, 10000, 100000, 1000000, 10000000}
	for _, ip := range inputs[1:] {
		fmt.Printf("Start test with: %d numbers\n", ip)

		if err := run(spanPath, ip); err != nil {
			log.Fatalf("Failed test with %d numbers: %v", ip, err)
		}

		fmt.Printf("Pass test with : %d numbers\n", ip)
	}
}
