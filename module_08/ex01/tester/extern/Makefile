BINARY_NAME=spanTest

# Go related variables
GOBASE=$(shell pwd)
GOBIN=$(GOBASE)/bin
GOFILES=$(wildcard ./cmd/*.go)

# Make is verbose in Linux. Make it silent.
MAKEFLAGS += --silent

build:
	GOAMD64=v3 CGO_ENABLED=0 go build -ldflags="-w -s" -gcflags="-B -l=4" -o $(GOBIN)/$(BINARY_NAME) ./cmd/main.go
	@echo "Binary built! You can find it in $(GOBIN)/$(BINARY_NAME)"

run: build
	./bin/spanTest ../../test

clean:
	@echo "Cleaning build cache..."
	go clean
	rm -rf $(GOBIN)

fmt:
	@echo "Formatting..."
	go fmt ./...

vet:
	@echo "Running go vet..."
	go vet ./...

lint:
	@echo "Running linter..."
	golangci-lint run

.PHONY: build run clean fmt vet lint
