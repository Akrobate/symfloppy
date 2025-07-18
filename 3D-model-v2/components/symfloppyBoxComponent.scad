use <../pieces/subpieces/centeredPaneSubPiece.scad>
use <../pieces/topPanePiece.scad>
use <../pieces/bottomPanePiece.scad>

use <../pieces/housingBorderPiece.scad>

include <../configurations/global.scad>


/**
 * symfloppyBoxComponent
 * @name symfloppyBoxComponent
 * @description symfloppyBoxComponent
 * @type component
 * @parent
 */
module symfloppyBoxComponent(
    x_size = symfloppy_box_x_size,
    y_size = symfloppy_box_y_size,
    z_size = symfloppy_box_z_size,
    pane_thickness = symfloppy_box_pane_thickness,
    center_z = false,
) {

    color_1 = "Chocolate";
    color_2 = "Peru";
    color_3 = "SaddleBrown";


    translate([-symfloppy_box_x_size / 2, -symfloppy_box_y_size / 2, pane_thickness])
    color(color_2)
        housingBorderPiece();

    translate([0, 0, (center_z ? 0 : z_size / 2)]) {

        *color(color_2) {
            translate([0, -(y_size / 2 - pane_thickness / 2), 0])
                rotate([90,0,0])
                    frontPanePiece();

            translate([0, (y_size / 2 - pane_thickness / 2), 0])
                rotate([90,0,0])
                    backPanePiece();
        }

        *color(color_3) {
            translate([-(x_size / 2 - pane_thickness / 2), 0, 0])
                rotate([90,0,90])
                    leftPanePiece();


            translate([(x_size / 2 - pane_thickness / 2), 0, 0])
                rotate([90,0,90])
                    rightPanePiece();
        }

        color(color_1, alpha=1) {
            translate([0, 0, z_size / 2 - pane_thickness / 2])
                topPanePiece();

            
            #translate([0, 0, -(z_size / 2 - pane_thickness / 2) - 00])
                bottomPanePiece();
            
        }
    }
}
