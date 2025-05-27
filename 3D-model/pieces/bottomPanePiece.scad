use <./subpieces/centeredPaneSubPiece.scad>
use <../envelopes/holdersPiecesThrows.scad>

include <../configurations/global.scad>

bottomPanePiece();

module bottomPanePiece(
    x_size = symfloppy_box_x_size,
    y_size = symfloppy_box_y_size,
    pane_thickness = symfloppy_box_pane_thickness,

    holder_piece_x_from_z_offset = holder_piece_x_from_z_offset,
) {
    echo("bottomPanePiece", x_size=x_size, y_size=y_size);

    difference() {
        centeredPaneSubPiece(x_size, y_size, pane_thickness);

        holdersPiecesThrows(
            symfloppy_box_x_size = x_size,
            holder_piece_x_from_z_offset = holder_piece_x_from_z_offset,
            symfloppy_box_pane_thickness = pane_thickness,
            throws_diameter = 3.5
        );
    }
}