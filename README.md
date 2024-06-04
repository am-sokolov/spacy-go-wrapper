# spacy-sentence-splitter

This package provides a Go wrapper for splitting sentences using spaCy and C++.

## Prerequisites

- Go 1.16+
- CMake
- Python 3
- spaCy and the `en_core_web_sm` model
- spacy-cpp

## Building

```bash
mkdir -p build && cd build
cmake ..
make
sudo make install
