include <../configurations/global.scad>;
include <../libraries/commons.scad>;
include <../libraries/electronics.scad>;

use <./subpieces/roundedPane.scad>

module housingBorderPiece(
    x_size = case_external_x_size,
    y_size = case_external_y_size,
    z_size = case_external_z_size,
    round_edges_radius = facade_front_round_edges_radius,
    case_external_panes_thickness = case_external_panes_thickness,
    border_thickness = housingBorderPiece_border_thickness,
    insert_throw_diameter = insert_throw_diameter,
    insert_throw_length = insert_throw_length,
    facade_throws_margin = facade_throws_margin,
    photoButton_position_coords = photoButton_position_coords,
    chargerConnector_position_coords = chargerConnector_position_coords,
    usb_connector_throw_diameter = usb_connector_throw_diameter,
    usb_connector_throw_fn = usb_connector_throw_fn,
    Battery_x_position = Battery_x_position,
    Battery_x_size = Battery_x_size,
    throw_m3_diameter = throw_m3_diameter,
    viewfinder_fixations_x_position_coords = viewfinder_fixations_x_position_coords,
) {

    epsilon = 0.1;

    nut_encaps_diameter = 6;
    nut_encaps_depth = 2.6; // 2.8 is the depth of the nut encapsulation

    local_z_size = z_size - case_external_panes_thickness * 2;

    throws_coords_list = [
        [facade_throws_margin, facade_throws_margin],
        [facade_throws_margin, y_size - facade_throws_margin],
        [x_size - facade_throws_margin, y_size - facade_throws_margin],
        [x_size - facade_throws_margin, facade_throws_margin],
    ];

    render() {
    difference() {
        union() {
            difference() {
                roundedPane(
                    [
                        x_size,
                        y_size,
                        local_z_size,
                    ],
                    round_edges_radius,
                    round_edges_radius,
                    center = false,
                    $fn = 100
                );

                translate([
                    border_thickness,
                    border_thickness,
                    -case_external_panes_thickness
                ])
                    roundedPane(
                        [
                            x_size - border_thickness * 2,
                            y_size - border_thickness * 2,
                            z_size + border_thickness * 2,
                        ],
                        round_edges_radius,
                        round_edges_radius,
                        center = false,
                        $fn = 100
                    );
            }

            translate([0, 0, 0])
                forEachCoord(throws_coords_list)
                    cylinder(
                        d = 10,
                        h = local_z_size,
                        center = false,
                        $fn = 100
                    );

            for(coord_x = viewfinder_fixations_x_position_coords)
                translate([coord_x, case_external_y_size, local_z_size / 2])
                    rotate([90, 0, 0])
                        cylinder(
                            d1 = insert_throw_diameter + 8,
                            d2 = insert_throw_diameter + 2,
                            h = insert_throw_length + 1,
                            center = false,
                            $fn = 100
                        );
        }

                
        // facade inserts throws
        translate([0, 0, -epsilon])
            forEachCoord(throws_coords_list)
                cylinder(
                    d = insert_throw_diameter,
                    h = insert_throw_length + epsilon,
                    center = false,
                    $fn = 100
                );

        translate([0, 0, local_z_size - insert_throw_length])
            forEachCoord(throws_coords_list)
                cylinder(
                    d = insert_throw_diameter,
                    h = insert_throw_length + epsilon,
                    center = false,
                    $fn = 100
                );
    }
    }
}


housingBorderPiece();
