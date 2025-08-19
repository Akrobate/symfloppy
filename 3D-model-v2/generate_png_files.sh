#!/bin/bash

PIECES_PATH=./pieces/*.scad;
COMPONENTS_PATH=./components/*.scad;
PNG_FILES_PATH=./png_files;

if [ ! -d "$PNG_FILES_PATH" ]; then
    echo "Folder $PNG_FILES_PATH does not exist, creating"
    mkdir $PNG_FILES_PATH
fi

if [ ! -d "$PNG_FILES_PATH/pieces" ]; then
    echo "Folder $PNG_FILES_PATH/pieces does not exist, creating"
    mkdir "$PNG_FILES_PATH/pieces"
fi

if [ ! -d "$PNG_FILES_PATH/components" ]; then
    echo "Folder $PNG_FILES_PATH/components does not exist, creating"
    mkdir "$PNG_FILES_PATH/components"
fi

for filename in $PIECES_PATH; do 
    file=$(basename "$filename");
    piece="${file%.*}";
    echo "Generating PNG for piece: $piece";
    openscad --colorscheme="BeforeDawn" --view="axes,scales" -o png_files/pieces/$piece.png pieces/$piece.scad
done

for filename in $COMPONENTS_PATH; do 
    file=$(basename "$filename");
    component="${file%.*}";
    echo "Generating PNG for $piece";
    openscad --colorscheme="BeforeDawn" -o png_files/components/$component.png components/$component.scad
done

openscad --colorscheme="BeforeDawn" -o png_files/main.png main.scad

echo "PNG files generated in $PNG_FILES_PATH";
