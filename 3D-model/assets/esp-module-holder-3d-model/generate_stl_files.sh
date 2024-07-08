#!/bin/bash

declare -g PIECES=(
facade-holder-8266-D1-piece
fixation-holder-8266-D1-piece
throws-holder-external-fix
throws-holder-internal-fix
)

# Model generation
openscad -o stl_files/facade-holder-8266-D1-piece.stl pieces/facade-holder-8266-D1-piece.scad
openscad -o stl_files/fixation-holder-8266-D1-piece.stl pieces/fixation-holder-8266-D1-piece.scad
openscad -o stl_files/throws-holder-external-fix.stl pieces/throws-holder-external-fix.scad
openscad -o stl_files/throws-holder-internal-fix.stl pieces/throws-holder-internal-fix.scad
