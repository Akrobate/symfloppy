use <./subpieces/centeredPaneSubPiece.scad>
use <./subpieces/roundedPane.scad>

include <../configurations/global.scad>


/**
 * bottomPanePiece
 * @name bottomPanePiece
 * @description bottomPanePiece
 * @type piece
 * @parent
 */
module bottomPanePiece(
    x_size = symfloppy_box_x_size,
    y_size = symfloppy_box_y_size,
    pane_thickness = symfloppy_box_pane_thickness,
    holder_piece_x_from_z_offset = holder_piece_x_from_z_offset,
    round_edges_radius = facade_front_round_edges_radius,
    _fn = 100
) {
    echo("bottomPanePiece", x_size=x_size, y_size=y_size);

    difference() {
        roundedPane(
            [x_size, y_size, pane_thickness],
            r1 = round_edges_radius,
            r2 = round_edges_radius,
            center = true,
            $fn = _fn
        );
    }
}

bottomPanePiece();
