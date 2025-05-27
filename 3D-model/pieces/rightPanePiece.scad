use <./subpieces/centeredPaneSubPiece.scad>
include <../configurations/global.scad>

rightPanePiece();

module rightPanePiece(
    x_size = symfloppy_box_y_size - (symfloppy_box_pane_thickness * 2),
    y_size = symfloppy_box_z_size - (symfloppy_box_pane_thickness * 2),
    pane_thickness = symfloppy_box_pane_thickness,
    holder_piece_y_centered_holder_piece_gap = holder_piece_y_centered_holder_piece_gap
) {
    echo("rightPanePiece", x_size=x_size, y_size=y_size);
    throws_diameter = 3.5;
    _fn = 100;

    difference() {
        centeredPaneSubPiece(x_size, y_size, pane_thickness);

        translate([
            holder_piece_y_centered_holder_piece_gap / 2,
            0,
            0
        ])
            cylinder(d=throws_diameter, h=pane_thickness * 2, center=true, $fn=_fn);

        translate([
            -holder_piece_y_centered_holder_piece_gap / 2,
            0,
            0
        ])
            cylinder(d=throws_diameter, h=pane_thickness * 2, center=true, $fn=_fn);
    }
}
