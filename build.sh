#!/bin/bash

## Change this to change where inside the repository you want the output
## Must be a directory inside the directory with CMakeList.txt
## Requires CMake

BUILD_DIR="build"

echo "building to $BUILD_DIR DIRECTORY USING CMAKE"
echo "Copying assets directory automatically"
mkdir -p build
cd build || ( echo "Failed to change directory to build (couldn't move to the build folder) " ; exit 3 )

cmake ..
if [ $? -eq 0 ] ; then
  echo "Build succeeded, now compiling and running game"
else
  echo "Build failed, check output!"
  exit 1
fi

make
if [ $? -eq 0 ] ; then
  echo "Compiling succeeded, now running game"
else
  echo "Compilation failed, check output!"
  exit 2
fi
echo "Use alt-F4 to stop game"

chmod +x ./dondolagame_recreation

./dondolagame_recreation