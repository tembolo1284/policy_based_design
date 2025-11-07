#!/bin/bash

# ===========================================================================
# Policy-Based Design Calculator - Build Script
# ===========================================================================
# This script provides a convenient interface to Bazel builds with various
# configurations including compiler selection, build modes, and targets.
# ===========================================================================

set -e  # Exit on any error

# ===========================================================================
# Color Codes
# ===========================================================================
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# ===========================================================================
# Default Values
# ===========================================================================
COMPILER="gcc"
BUILD_MODE="debug"
DO_CLEAN=0
DO_BUILD=0
DO_TEST=0
DO_PYTHON=0
DO_CPP=0
VERBOSE=0

# ===========================================================================
# Helper Functions
# ===========================================================================

print_header() {
    echo -e "${BLUE}========================================${NC}"
    echo -e "${BLUE}$1${NC}"
    echo -e "${BLUE}========================================${NC}"
}

print_success() {
    echo -e "${GREEN}✓ $1${NC}"
}

print_error() {
    echo -e "${RED}✗ $1${NC}"
}

print_info() {
    echo -e "${YELLOW}→ $1${NC}"
}

# ===========================================================================
# Usage Information
# ===========================================================================

show_help() {
    cat << EOF
Usage: ./build.sh [OPTIONS]

Build script for Policy-Based Design Calculator with Bazel.

OPTIONS:
  Actions:
    --clean              Clean all build artifacts
    --build              Build all targets
    --test               Run all tests
    --all                Build and test everything (equivalent to --build --test)
    --python             Build and run Python example
    --cpp                Build and run C++ main

  Compiler Selection:
    --compiler=gcc       Use GCC compiler (default)
    --compiler=clang     Use Clang compiler

  Build Mode:
    --debug              Debug build with symbols (default)
    --release            Optimized release build

  Other:
    --verbose            Show detailed Bazel output
    --help               Show this help message

EXAMPLES:
  # Clean and do full release build with GCC
  ./build.sh --clean --all --compiler=gcc --release

  # Quick debug build and test
  ./build.sh --build --test --debug

  # Run Python example with release build
  ./build.sh --python --release

  # Build with Clang in debug mode
  ./build.sh --all --compiler=clang --debug

  # Just clean everything
  ./build.sh --clean

  # Build C++ and Python, then test
  ./build.sh --build --test --python --cpp

NOTES:
  - Default compiler is GCC
  - Default build mode is debug
  - Multiple actions can be combined
  - Flags are applied in order: clean → build → test → run

EOF
}

# ===========================================================================
# Check Dependencies
# ===========================================================================

check_dependencies() {
    # Check for Bazel
    if ! command -v bazel &> /dev/null; then
        print_error "Bazel not found!"
        echo "Please install Bazel from: https://bazel.build/install"
        exit 1
    fi

    # Check for selected compiler
    if [[ "$COMPILER" == "gcc" ]]; then
        if ! command -v g++ &> /dev/null; then
            print_error "g++ not found!"
            echo "Please install GCC"
            exit 1
        fi
    elif [[ "$COMPILER" == "clang" ]]; then
        if ! command -v clang++ &> /dev/null; then
            print_error "clang++ not found!"
            echo "Please install Clang"
            exit 1
        fi
    fi
}

# ===========================================================================
# Parse Command Line Arguments
# ===========================================================================

if [[ $# -eq 0 ]]; then
    show_help
    exit 0
fi

for arg in "$@"; do
    case $arg in
        --clean)
            DO_CLEAN=1
            ;;
        --build)
            DO_BUILD=1
            ;;
        --test)
            DO_TEST=1
            ;;
        --all)
            DO_BUILD=1
            DO_TEST=1
            ;;
        --python)
            DO_PYTHON=1
            ;;
        --cpp)
            DO_CPP=1
            ;;
        --compiler=gcc)
            COMPILER="gcc"
            ;;
        --compiler=clang)
            COMPILER="clang"
            ;;
        --debug)
            BUILD_MODE="debug"
            ;;
        --release)
            BUILD_MODE="release"
            ;;
        --verbose)
            VERBOSE=1
            ;;
        --help)
            show_help
            exit 0
            ;;
        *)
            print_error "Unknown option: $arg"
            echo "Use --help for usage information"
            exit 1
            ;;
    esac
done

# ===========================================================================
# Build Configuration
# ===========================================================================

BAZEL_FLAGS="--config=$COMPILER --config=$BUILD_MODE"

if [[ $VERBOSE -eq 1 ]]; then
    BAZEL_FLAGS="$BAZEL_FLAGS --subcommands"
fi

# ===========================================================================
# Main Execution
# ===========================================================================

print_header "Policy-Based Design Calculator Build"
echo ""
print_info "Compiler: $COMPILER"
print_info "Build Mode: $BUILD_MODE"
print_info "Bazel Flags: $BAZEL_FLAGS"
echo ""

# Check dependencies
check_dependencies

# ===========================================================================
# Clean
# ===========================================================================

if [[ $DO_CLEAN -eq 1 ]]; then
    print_header "Cleaning Build Artifacts"
    print_info "Running: bazel clean --expunge"
    bazel clean --expunge
    print_success "Clean complete"
    echo ""
fi

# ===========================================================================
# Build
# ===========================================================================

if [[ $DO_BUILD -eq 1 ]]; then
    print_header "Building All Targets"
    print_info "Running: bazel build //... $BAZEL_FLAGS"
    
    if bazel build //... $BAZEL_FLAGS; then
        print_success "Build complete"
    else
        print_error "Build failed"
        exit 1
    fi
    echo ""
fi

# ===========================================================================
# Test
# ===========================================================================

if [[ $DO_TEST -eq 1 ]]; then
    print_header "Running Tests"
    print_info "Running: bazel test //... $BAZEL_FLAGS"
    
    if bazel test //... $BAZEL_FLAGS; then
        print_success "All tests passed"
    else
        print_error "Tests failed"
        exit 1
    fi
    echo ""
fi

# ===========================================================================
# Run Python Example
# ===========================================================================

if [[ $DO_PYTHON -eq 1 ]]; then
    print_header "Running Python Example"
    print_info "Running: bazel run //python:example $BAZEL_FLAGS"
    echo ""
    
    if bazel run //python:example $BAZEL_FLAGS; then
        echo ""
        print_success "Python example complete"
    else
        print_error "Python example failed"
        exit 1
    fi
    echo ""
fi

# ===========================================================================
# Run C++ Main
# ===========================================================================

if [[ $DO_CPP -eq 1 ]]; then
    print_header "Running C++ Main"
    print_info "Running: bazel run //src:Main $BAZEL_FLAGS"
    echo ""
    
    if bazel run //src:Main $BAZEL_FLAGS; then
        echo ""
        print_success "C++ main complete"
    else
        print_error "C++ main failed"
        exit 1
    fi
    echo ""
fi

# ===========================================================================
# Summary
# ===========================================================================

print_header "Build Script Complete"
print_success "All requested operations completed successfully!"
echo ""
