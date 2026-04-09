# CS 118 Spring 2026 Project 1

This repository contains the starter code for Project 1.

Read the spec for the full project specification, requirements, grading policy, and submission instructions.

## Files

- `src/proxy.c`: starter code with TODOs
- `src/Makefile`: builds the proxy executable
- `helper`: runs the local autograder

## Build

```bash
cd src
make
```

## Run

```bash
cd src
./proxy
```

Default settings:

- listen on port `18443`
- backend address `127.0.0.1`
- backend port `18444`

You can also run with custom settings:

```bash
./proxy -b 8080 -r 127.0.0.1 -p 8000
```

## Test

```bash
./helper run
```
