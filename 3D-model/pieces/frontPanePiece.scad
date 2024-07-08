use <./subpieces/centeredPaneSubPiece.scad>
include <../configuration.scad>

frontPanePiece();

module frontPanePiece(
    x_size = symfloppy_box_x_size,
    y_size = symfloppy_box_z_size - symfloppy_box_pane_thickness * 2,
    pane_thickness = symfloppy_box_pane_thickness
) {
    echo("frontPanePiece", x_size=x_size, y_size=y_size);
    centeredPaneSubPiece(x_size, y_size, pane_thickness);
}