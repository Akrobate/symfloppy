#!/bin/bash

# Pieces Image generation
openscad -o render_files/facade-holder-8266-D1-piece.png pieces/facade-holder-8266-D1-piece.scad
openscad -o render_files/fixation-holder-8266-D1-piece.png pieces/fixation-holder-8266-D1-piece.scad
openscad -o render_files/throws-holder-external-fix.png pieces/throws-holder-external-fix.scad
openscad -o render_files/throws-holder-internal-fix.png pieces/throws-holder-internal-fix.scad

# Components Image generation
openscad -o render_files/holder-8266-D1-component.png components/holder-8266-D1-component.scad
openscad -o render_files/holder-8266-D1-component-with-external-fix.png components/holder-8266-D1-component-with-external-fix.scad
openscad -o render_files/holder-8266-D1-component-with-internal.png components/holder-8266-D1-component-with-internal.scad