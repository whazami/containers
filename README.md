# Containers

## Overview

This repository contains an implementation of various container classes from the C++98 Standard Library developed as part of the 42 Paris curriculum. The primary goal of this project is to gain a deeper understanding of data structures, their internal workings, and the underlying algorithms, while honing C++ programming skills.

The project includes the following container classes:
* Vector: A dynamic array that automatically manages its size
* Map: A sorted associative container that stores key-value pairs
* Stack: A container adapter that provides a last-in, first-out (LIFO) data structure

## Prerequisites

* A Unix-based operating system (e.g., Linux, macOS)
* GCC compiler
* GNU Make

## Installation

1. Clone this repository to your local machine:
```bash
git clone https://github.com/whazami/containers.git
```
2. Navigate to the cloned repository:
```bash
cd containers
```

## Usage

There are several make options available:
* `make [ft]` or `make std`: Compiles the main specified in the `SRCS` variable in the Makefile along with the containers from this repository or the standard library, respectively. Once compiled, you'll be able to run the output executable as follows: `./ft` or `./std`.
* `make test`: Executes both `make ft` and `make std`, runs the generated executables, compares the outputs and time taken by each executable to run, and prints the results.
* `make subject`: Similar to `make test`, but instead of compiling the main in the `SRCS` variable, it generates a random seed and compiles the main in the `SRCS_S` variable.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
