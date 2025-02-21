#!/bin/bash

BUILD_DIR="build"
ASSETS_SOURCE_DIR="assets"
ASSETS_OUTPUT_DIR="${BUILD_DIR}/assets"
SFML_DIR="lib/SFML" # Path to SFML directory (relative to the project root)

# Create the build directory if it doesn't exist
mkdir -p ${BUILD_DIR}
mkdir -p ${ASSETS_OUTPUT_DIR}

# Function to check if SFML is installed system-wide
check_system_sfml() {
    echo "Checking for system-wide SFML installation..." >&2

    # Check for SFML headers
    if [ -d "/usr/include/SFML" ] || [ -d "/usr/local/include/SFML" ]; then
        echo "SFML headers found."
        return 0
    fi

    # Check for SFML libraries
    if ldconfig -p 2>/dev/null | grep -q "libsfml"; then
        echo "SFML libraries found."
        return 0
    fi

    # macOS (Homebrew)
    if [ -d "/usr/local/Cellar/sfml" ]; then
        echo "SFML found (macOS Homebrew)."
        return 0
    fi

    # Windows
    if [ -d "C:/SFML" ]; then
        echo "SFML found (Windows)."
        return 0
    fi

    echo "SFML not found system-wide." >&2
    return 1
}

# Check if SFML directory exists in the project
if [ -d "${SFML_DIR}" ]; then
    echo "Using SFML from ${SFML_DIR}."
    SFML_INCLUDE="-I${SFML_DIR}/include"
    SFML_LIB="-L${SFML_DIR}/lib"
elif check_system_sfml; then
    echo "Using system-wide SFML installation." >&2
    SFML_INCLUDE=""
    SFML_LIB=""
else
    echo "Error: SFML not found in ${SFML_DIR} or system-wide." >&2
    echo "Please download SFML and place it in the lib directory or install it system-wide." >&2
    echo "install it here: https://www.sfml-dev.org/download/"
    echo "if you are on Linux, try building SFML yourself https://www.sfml-dev.org/tutorials/3.0/getting-started/build-from-source/"
    exit 1
fi

# Compile the project
if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "cygwin" ]]; then
    # Windows (MinGW)
    echo "Compiling for Windows..." >&2
    g++ -std=c++17 -o ${BUILD_DIR}/dondolagame_recreation.exe \
        main.cpp src/GameManager.cpp src/Player.cpp src/Enemy.cpp src/EnemyManager.cpp \
        -Iinclude ${SFML_INCLUDE} \
        ${SFML_LIB} \
        -lsfml-graphics -lsfml-window -lsfml-system

    # Copy SFML DLLs to the build directory (Windows only)
    if [ -d "${SFML_DIR}/bin" ]; then
        cp ${SFML_DIR}/bin/*.dll ${BUILD_DIR}/
    elif [ -d "C:/SFML/bin" ]; then
        cp C:/SFML/bin/*.dll ${BUILD_DIR}/
    fi
else
    # Linux/macOS
    echo "Compiling for Linux/macOS..." >&2
    g++ -std=c++17 -o ${BUILD_DIR}/dondolagame_recreation \
        main.cpp src/GameManager.cpp src/Player.cpp src/Enemy.cpp src/EnemyManager.cpp \
        -Iinclude ${SFML_INCLUDE} \
        ${SFML_LIB} \
        -lsfml-graphics -lsfml-window -lsfml-system
fi

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful!"

    # Copy assets to the build directory
    cp -r ${ASSETS_SOURCE_DIR}/* ${ASSETS_OUTPUT_DIR}/

    echo "Assets copied successfully!"
    echo "running app"
    sh ${BUILD_DIR}/dondolagame_recreation

else
    echo "Compilation failed!" >&2
    echo "Make sure you're using the correct SFML version" >&2
    echo "(3.0.0 - GCC 14.2.0 MinGW (SEH) (UCRT) 64-bit)" >&2
    exit 1
fi