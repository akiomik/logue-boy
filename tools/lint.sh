#!/bin/sh

set -e

# Check if clang-tidy is available
if ! command -v clang-tidy >/dev/null 2>&1; then
    echo "Error: clang-tidy not found in PATH."
    echo ""
    echo "Please install clang-tidy:"
    echo "  macOS:          brew install llvm"
    echo "  Ubuntu/Debian:  sudo apt install clang-tidy"
    echo "  Other systems:  Install via your package manager or from https://releases.llvm.org/"
    echo ""
    exit 1
fi

echo "Running clang-tidy..."
echo ""

# Find all C++ header files in osc directory, excluding test files
# Note: .cpp files are skipped because they require SDK headers that clang-tidy cannot find
find osc -name "*.hpp" | grep -v "/test/" | while read -r file; do
    echo "Checking: $file"
    clang-tidy "$file" -- \
        -std=c++11 \
        -Ilibs/logue-sdk-stub/platform/minilogue-xd/inc \
        -Ilibs/logue-sdk-stub/platform/minilogue-xd/inc/utils \
        -I"$(dirname "$file")" \
        -DSTM32F446xE \
        -DARM_MATH_CM4 \
        || true
done

echo ""
echo "Linting completed!"
