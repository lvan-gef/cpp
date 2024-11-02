package main

import (
	"bufio"
	"fmt"
	"log"
	"math"
	"os"
	"os/exec"
	"runtime"
	"strconv"
	"strings"
	"sync"
)

func findSpans(data []int) (int64, int64) {
	if len(data) < 2 {
		return math.MaxInt64, 0
	}

	numWorkers := runtime.NumCPU()

	dataLen := len(data)
	minChunkSize := 1000
	chunkSize := dataLen / numWorkers
	if chunkSize < minChunkSize {
		chunkSize = minChunkSize
		numWorkers = (dataLen + minChunkSize - 1) / minChunkSize
	}

	type result struct {
		min, max int64
	}
	results := make(chan result, numWorkers)

	var wg sync.WaitGroup

	for i := 0; i < numWorkers; i++ {
		wg.Add(1)
		start := i * chunkSize
		end := start + chunkSize
		if end > dataLen {
			end = dataLen
		}

		go func(start, end int) {
			defer wg.Done()

			localMin := int64(math.MaxInt64)
			localMax := int64(math.MinInt64)

			for i := start; i < end; i++ {
				val1 := data[i]
				for j := i + 1; j < dataLen; j++ {
					diff := val1 - data[j]
					if diff < 0 {
						diff = -diff
					}

					span := int64(diff)

					if span < localMin {
						localMin = span
					} else if span > localMax {
						localMax = span
					}
				}
			}

			results <- result{localMin, localMax}
		}(start, end)
	}

	go func() {
		wg.Wait()
		close(results)
	}()

	shortestSpan := int64(math.MaxInt64)
	longestSpan := int64(math.MinInt64)

	for r := range results {
		if r.min < shortestSpan {
			shortestSpan = r.min
		}
		if r.max > longestSpan {
			longestSpan = r.max
		}
	}

	return shortestSpan, longestSpan
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

	outScanner := bufio.NewScanner(stdout)
	var outputLines []string
	for outScanner.Scan() {
		txt := outScanner.Text()
		if strings.Contains(txt, "duration") {
			fmt.Printf("%s\n", txt)
			continue
		}

		outputLines = append(outputLines, "    "+txt)
	}

	if err := cmd.Wait(); err != nil {
		return fmt.Errorf("command failed: %v", err)
	}

	fmt.Printf("Go is verifying if the result is correct. This can take a long time.\n")
	shortestSpan, longestSpan := findSpans(data)

	if shortestSpan == math.MaxInt64 {
		return fmt.Errorf("shortest_span == int64 max so something went wrong")
	}

	if longestSpan < 0 {
		return fmt.Errorf("longest_span < 0 so something went wrong")
	}

	expectedOutput := fmt.Sprintf("    %d\n    %d\n", shortestSpan, longestSpan)
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

		fmt.Fprintf(f, "%s\n", expectedOutput)
		fmt.Fprintf(f, "%s\n", actualOutput)

		return fmt.Errorf("\nexpected:\n%sgot:\n%s", expectedOutput, actualOutput)
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

	fmt.Printf("Using span executable: %s\n\n", spanPath)

	// 10_000_000 takes to long
	// inputs := []int{1, 10, 100, 1000, 10000, 100000, 1000000, 10000000}
	inputs := []int{1, 10, 100, 1000, 10000, 100000, 1000000}
	for _, ip := range inputs[1:] {
		if err := run(spanPath, ip); err != nil {
			log.Fatalf("Failed test with %d numbers: %v", ip, err)
		}

		fmt.Printf("\n")
	}
}
