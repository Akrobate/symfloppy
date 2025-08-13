#!/bin/bash

PIECES_PATH=./pieces/*.scad;
STL_FILES_PATH=./stl_files;

if [ ! -d "$STL_FILES_PATH" ]; then
    echo "Folder $STL_FILES_PATH does not exist, creating"
    mkdir $STL_FILES_PATH
fi

for filename in $PIECES_PATH; do 
    file=$(basename "$filename");
    piece="${file%.*}";
    echo "Generating STL for $piece";
    openscad -o $STL_FILES_PATH/$piece.stl pieces/$piece.scad
done

echo "STL files generated in $STL_FILES_PATH";

