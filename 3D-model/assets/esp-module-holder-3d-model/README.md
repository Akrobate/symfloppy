# ESP Module Holder 3D Model

https://gitlab.com/Akrobate/esp-module-holder-3d-model

# Facade holder

```
facadeHolder8266D1Piece(
    board_width = 25.6,
    encaps_width = 23.36,
    encaps_height = 1,

    facade_height = 20,
    facade_width = 50,
    facade_thickness = 2,
    facade_hole_3mm_correction = 0.5,
    facade_throws_diameter = 3,

    usb_hole_height = 6.5,
    usb_hole_width = 12,
    usb_hole_thickness = 10,

    holder_a_hole_3mm_correction = 0.35,
    holder_a_encaps_width_correction = 0.4,
    holder_a_part_holders_width = 7,
    holder_a_depth = 6,
    holder_a_support_depth = 4.5,
    holder_a_height = 4,
    holder_a_throws_margin = 3,
    holder_a_throws_diameter = 3,

    holder_a_facade_shift_size = 0.1,

    holder_positionning_z = 0,

    fn_facade = 200,
    fn_holder_a = 100
)
```

# ESP Module Holder 3D Model

## Bottom holder

```
fixationHolder8266D1Piece(
    hole_3mm_correction = 0.35,

    part_holders_width = 7,
    part_holders_height = 2,

    board_width = 25.6,
    depth = 6,
    height = 2.5,
    throws_margin = 3,
    throws_diameter = 3,

    _fn = 100
)
```

# Throws, models for CNC cutting

throws-holder-external-fix.scad and throws-holder-internal-fix.scad are not pieces for 3D printing, they are forms for CNC cutting.

Holder can be placed inside the box or outside. In these cases holes are different.

## throwsHolderExternalFix
```
module throwsHolderExternalFix(
    throws_dephs = 4,
    facade_width = 50,
    facade_throws_diameter = 3,
    facade_hole_3mm_correction = 0.5,
    holder_from_center_shift_z = -3.25,

    part_holders_width = 7,
    board_width = 25.6,

    hodler_throw_scale_x = 1.05,
    hodler_throw_scale_z = 1.0,

    hodler_throw_z_margin_top = 2.5,
    hodler_throw_z_margin_bottom = 2.5,

    // Heighs elements configurations
    holderA8826D1ThrowsSubPiece_height = 4,
    holderB8826D1ThrowsSubPiece_height = 2.5,
    holderB8826D1ThrowsSubPiece_part_holders_height = 2,

    _fn = 200
)
```
## throwsHolderInternalFix
```
module throwsHolderInternalFix(
    throws_dephs = 4,
    facade_width = 50,
    facade_throws_diameter = 3,
    facade_hole_3mm_correction = 0.5,

    _fn = 100
)
```


# Usage

* Customize dimentions
* Generate stl files
```sh
sh generate_stl_files.sh
```
* (Optional) Generate preview files
```sh
sh generate_png_files.sh
```