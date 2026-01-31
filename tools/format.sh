#!/bin/sh

set -e

# Check if clang-format is available
if ! command -v clang-format >/dev/null 2>&1; then
    echo "Error: clang-format not found in PATH."
    echo ""
    echo "Please install clang-format:"
    echo "  macOS:          brew install clang-format"
    echo "  Ubuntu/Debian:  sudo apt install clang-format"
    echo "  Other systems:  Install via your package manager or from https://releases.llvm.org/"
    echo ""
    exit 1
fi

# Check for --check flag
CHECK_MODE=false
if [ "$1" = "--check" ]; then
    CHECK_MODE=true
fi

echo "Running clang-format..."
echo ""

# Find all C++ source and header files in osc directory, excluding test files
FILES=$(find osc -name "*.cpp" -o -name "*.hpp" | grep -v "/test/")

if [ "$CHECK_MODE" = true ]; then
    echo "Checking format (no changes will be made)..."
    echo ""
    
    # Check if files need formatting
    NEEDS_FORMAT=false
    for file in $FILES; do
        if ! clang-format --dry-run --Werror "$file" 2>/dev/null; then
            echo "❌ $file needs formatting"
            NEEDS_FORMAT=true
        fi
    done
    
    if [ "$NEEDS_FORMAT" = true ]; then
        echo ""
        echo "Some files need formatting. Run './tools/format.sh' to fix."
        exit 1
    else
        echo "✅ All files are properly formatted!"
        exit 0
    fi
else
    echo "Formatting files..."
    echo ""
    
    for file in $FILES; do
        echo "Formatting: $file"
        clang-format -i "$file"
    done
    
    echo ""
    echo "Formatting completed!"
fi
