use <./subpieces/centeredPaneSubPiece.scad>
use <./subpieces/roundedPane.scad>
include <../libraries/commons.scad>;


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
    throws_diameter = 3.5; // @todo: wood throw diameter to add to global config

    throws_coords_list = [
        [facade_throws_margin, facade_throws_margin],
        [facade_throws_margin, y_size - facade_throws_margin],
        [x_size - facade_throws_margin, y_size - facade_throws_margin],
        [x_size - facade_throws_margin, facade_throws_margin],
    ];

    difference() {
        roundedPane(
            [x_size, y_size, pane_thickness],
            r1 = round_edges_radius,
            r2 = round_edges_radius,
            center = true,
            $fn = _fn
        );

        translate([-x_size / 2, -y_size / 2])
            forEachCoord(throws_coords_list)
                cylinder(
                    d = throws_diameter,
                    h = pane_thickness * 4,
                    center = true,
                    $fn = 100
                );
        
    }
}

bottomPanePiece();
