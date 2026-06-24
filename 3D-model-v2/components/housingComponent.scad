use <../pieces/subpieces/centeredPaneSubPiece.scad>
use <../pieces/topPanePiece.scad>
use <../pieces/bottomPanePiece.scad>
use <../pieces/housingBorderPiece.scad>

include <../configurations/global.scad>


/**
 * housingComponent
 * @name housingComponent
 * @description housingComponent
 * @type component
 * @parent
 */
module housingComponent(
    x_size = symfloppy_box_x_size,
    y_size = symfloppy_box_y_size,
    z_size = symfloppy_box_z_size,
    pane_thickness = symfloppy_box_pane_thickness,
    center_z = false,
) {

    color_1 = "Chocolate";
    color_2 = "Peru";

    translate([-symfloppy_box_x_size / 2, -symfloppy_box_y_size / 2, pane_thickness])
    color(color_2)
        housingBorderPiece();

    translate([0, 0, (center_z ? 0 : z_size / 2)]) {
        color(color_1, alpha=1) {
            translate([0, 0, z_size / 2 - pane_thickness / 2])
                topPanePiece();

            
            #translate([0, 0, -(z_size / 2 - pane_thickness / 2) - 00])
                bottomPanePiece();
            
        }
    }
}


housingComponent();
