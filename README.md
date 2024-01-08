# SmartCalculator

A Python Calculator Application utilizing C++ for calculations with Qt/QML interface. The program follows the MVVM or MVP pattern, adheres to Google Code Style, and separates business logic appropriately.

## Overview

This project is a calculator application written in Python 3.12 with a Qt/QML interface. The calculation logic is implemented in C++17 using a dynamic library, and the integration between Python and C++ is achieved using ctypes. The project structure also includes a CMake build system for the C++ component.

## Prerequisites

- Python 3.12
- C++17 compiler
- Qt/QML

## Installation

### Build C++ Library

To build the C++ calculation library, run the following commands:

```bash
make build
```

### Python Environment

Create a virtual environment and install the required Python dependencies:

```bash
make environment
```

## Arithmetic Operators

| Operator            | Infix Notation (Classic) | Prefix Notation (Polish) | Postfix Notation (Reverse Polish) |
|---------------------|--------------------------|--------------------------|-----------------------------------|
| Parentheses         | (a + b)                  | (+ a b)                  | a b +                             |
| Addition            | a + b                    | + a b                    | a b +                             |
| Subtraction         | a - b                    | - a b                    | a b -                             |
| Multiplication      | a * b                    | * a b                    | a b *                             |
| Division            | a / b                    | / a b                    | a b \                             |
| Raising to the Power | a ^ b                    | ^ a b                    | a b ^                             |
| Remainder of Division| a mod b                  | mod a b                  | a b mod                           |
| Unary Plus          | +a                       | +a                       | a+                                |
| Unary Minus         | -a                       | -a                       | a-                                |

## Mathematical Functions

| Function            | Notation                 |
|---------------------|--------------------------|
| Cosine              | cos(x)                   |
| Sine                | sin(x)                   |
| Tangent             | tan(x)                   |
| Arc Cosine          | acos(x)                  |
| Arc Sine           | asin(x)                  |
| Arc Tangent        | atan(x)                  |
| Square Root        | sqrt(x)                  |
| Natural Logarithm  | ln(x)                    |
| Decimal Logarithm  | log(x)                   |

## Usage

Run the calculator application:

```bash
make run
```

This will start the Qt/QML interface with the calculator.

## Build Targets

- `make all` (default): Build the project.
- `make build`: Build the C++ calculation library.
- `make rebuild`: Clean and rebuild the C++ library.
- `make uninstall`: Remove build artifacts.
- `make clean`: Clean the project directory.
- `make environment`: Create Python virtual environment and install dependencies.
- `make run`: Run the calculator application.

## Project Structure

- `lib/calculation`: C++ calculation library source code.
- `view`: Qt/QML interface files.
- `main.py`: Python script for running the calculator.
- `requirements.txt`: Python dependencies.

## C++ Calculation Library

The C++ calculation library (`calculation.h`, `calculation.cc`) provides the core logic for parsing and evaluating mathematical expressions. It supports basic operations, functions, and constants.

## Qt/QML Interface

The Qt/QML interface is defined in the `view/main.qml` file, and the Python script (`main.py`) handles the integration between Python and C++.

## Cleaning Up

To remove build artifacts and Python cache files, run:

```bash
make clean
```

## LICENSE
This project is licensed under the [MIT License](LICENSE). Feel free to modify and distribute it as per the terms of the license.