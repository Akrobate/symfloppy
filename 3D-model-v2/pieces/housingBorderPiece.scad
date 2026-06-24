include <../configurations/global.scad>;
include <../libraries/commons.scad>;

use <../openscad_modules/housing/housingBorder.scad>
use <../envelopes/usbConnectorThrowEnveloppe.scad>
use <../envelopes/buttonAssetThrow.scad>


module housingBorderPiece(
    x_size = symfloppy_box_x_size,
    y_size = symfloppy_box_y_size,
    z_size = symfloppy_box_z_size,
    round_edges_radius = facade_front_round_edges_radius,
    case_external_panes_thickness = symfloppy_box_pane_thickness,
    border_thickness = housingBorderPiece_border_thickness,
    insert_throw_diameter = insert_throw_diameter,
    insert_throw_length = insert_throw_length,
    facade_throws_margin = facade_throws_margin,
) {

    epsilon = 0.1;
    local_z_size = z_size - case_external_panes_thickness * 2;
    insert_holder_diameter = 10;

    difference() {

        housingBorder(
            x_size = x_size,
            y_size = y_size,
            z_size = local_z_size,
            round_edges_radius = round_edges_radius,
            border_thickness = border_thickness,
            insert_throw_diameter = insert_throw_diameter,
            insert_throw_length = insert_throw_length,
            insert_holder_diameter = insert_holder_diameter,
            facade_throws_margin = facade_throws_margin,
            _fn = 100
        )

        // usb connector throws
        translate([x_size / 2, y_size, local_z_size / 2])
            rotate([-90,0,0])
                usbConnectorThrowEnveloppe();

        // Buttons throws
        translate([x_size / 2 + button_x_center_offset, 0, local_z_size / 2]) {
            for (x_coord=[-button_x_spaces, 0, button_x_spaces])
                translate([-x_coord, 0, 0])
                    rotate([90,0,0])
                    buttonAssetThrow();
        }

    }

}




housingBorderPiece();
