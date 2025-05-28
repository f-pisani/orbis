#!/bin/bash

# Build script for Orbis game

echo "Orbis Build Script"
echo "=================="

# Function to check if a command exists
command_exists() {
    command -v "$1" >/dev/null 2>&1
}

# Build natively if dependencies are available
build_native() {
    echo "Building natively..."
    
    # Check for required tools
    if ! command_exists g++; then
        echo "Error: g++ not found. Please install build-essential."
        return 1
    fi
    
    if ! command_exists pkg-config; then
        echo "Error: pkg-config not found. Please install it."
        return 1
    fi
    
    # Check for SFML
    if ! pkg-config --exists sfml-all; then
        echo "Error: SFML not found. Please install libsfml-dev."
        echo "On Ubuntu/Debian: sudo apt-get install libsfml-dev"
        echo "On Fedora: sudo dnf install SFML-devel"
        echo "On Arch: sudo pacman -S sfml"
        return 1
    fi
    
    # Build the project
    make clean
    make release
    
    if [ $? -eq 0 ]; then
        echo "Build successful! Executable: release/Orbis"
        echo "Run with: ./release/Orbis"
    else
        echo "Build failed!"
        return 1
    fi
}

# Build using Docker
build_docker() {
    echo "Building with Docker..."
    
    if ! command_exists docker; then
        echo "Error: Docker not found. Please install Docker."
        return 1
    fi
    
    docker build -t orbis-game .
    
    if [ $? -eq 0 ]; then
        echo "Docker build successful!"
        echo "Run with: ./run-docker.sh"
    else
        echo "Docker build failed!"
        return 1
    fi
}

# Main script
case "${1:-native}" in
    native)
        build_native
        ;;
    docker)
        build_docker
        ;;
    both)
        build_native
        echo ""
        build_docker
        ;;
    *)
        echo "Usage: $0 [native|docker|both]"
        echo "  native - Build using system libraries (default)"
        echo "  docker - Build using Docker"
        echo "  both   - Try both build methods"
        exit 1
        ;;
esac