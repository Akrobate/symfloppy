use <./subpieces/centeredPaneSubPiece.scad>
use <../envelopes/floppyFixationThrows.scad>
use <../envelopes/buttonAssetThrow.scad>
use <../envelopes/holdersPiecesThrows.scad>

include <../configurations/global.scad>


topPanePiece();


module topPanePiece(
    x_size = symfloppy_box_x_size,
    y_size = symfloppy_box_y_size,
    pane_thickness = symfloppy_box_pane_thickness,

    button_y_front_offset = button_y_front_offset,
    button_x_spaces = button_x_spaces,
    button_x_center_offset = button_x_center_offset,

    holder_piece_x_from_z_offset = holder_piece_x_from_z_offset,
) {
    throws_z_size = 40;
    throws_diameter = 3.5;

    echo("topPanePiece", x_size=x_size, y_size=y_size);
    difference() {
        centeredPaneSubPiece(x_size, y_size, pane_thickness);
        floppyFixationThrows(
            z_size = throws_z_size,
            throws_diameter = throws_diameter
        );

        translate(
            [
                button_x_center_offset,
                -y_size / 2 + button_y_front_offset,
                0
            ]
        ) {
            translate([-button_x_spaces, 0, 0])
                buttonAssetThrow();
            translate([0, 0, 0])
                buttonAssetThrow();
            translate([button_x_spaces, 0, 0])
                buttonAssetThrow();
        }

        holdersPiecesThrows(
            symfloppy_box_x_size = x_size,
            holder_piece_x_from_z_offset = holder_piece_x_from_z_offset,
            symfloppy_box_pane_thickness = pane_thickness,
            throws_diameter = 3.5
        );        
    }

}