use <./subpieces/centeredPaneSubPiece.scad>
use <../envelopes/din5.scad>
use <../assets/esp-module-holder-3d-model/pieces/throws-holder-external-fix.scad>

include <../configurations/global.scad>

/**
 * backPanePiece
 * @name backPanePiece
 * @description backPanePiece
 * @type piece
 * @parent
 */
module backPanePiece(
    x_size = symfloppy_box_x_size,
    y_size = symfloppy_box_z_size - symfloppy_box_pane_thickness * 2,
    pane_thickness = symfloppy_box_pane_thickness
) {
    echo("backPanePiece", x_size=x_size, y_size=y_size);

    x_din_center_offsets = 51;

    difference() {

        
        centeredPaneSubPiece(x_size, y_size, pane_thickness);

        translate([0,0,-4])
            throwsHolderExternalFix(
                throws_dephs = 8,
                facade_width = 50,
                facade_throws_diameter = 3,
                facade_hole_3mm_correction = 0.8,
                holder_from_center_shift_z = -3.25,

                part_holders_width = 7,
                board_width = 25.6,

                hodler_throw_scale_x = 1.07,
                hodler_throw_scale_z = 1.0,

                hodler_throw_z_margin_top = 3.6,
                hodler_throw_z_margin_bottom = 2.6,

                // Heighs elements configurations
                holderA8826D1ThrowsSubPiece_height = 4,
                holderB8826D1ThrowsSubPiece_height = 2.5,
                holderB8826D1ThrowsSubPiece_part_holders_height = 2,

                _fn = 200
            );

        translate([-x_din_center_offsets, 0, 0])
            throws_din5(
                throws_height = 8
            );

        translate([x_din_center_offsets, 0, 0])
            throws_din5(
                throws_height = 8
            );   
    }
}


backPanePiece();