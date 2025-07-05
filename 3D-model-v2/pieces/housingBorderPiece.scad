include <../configurations/global.scad>;
include <../libraries/commons.scad>;

use <./subpieces/roundedPane.scad>


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

    throws_coords_list = [
        [facade_throws_margin, facade_throws_margin],
        [facade_throws_margin, y_size - facade_throws_margin],
        [x_size - facade_throws_margin, y_size - facade_throws_margin],
        [x_size - facade_throws_margin, facade_throws_margin],
    ];

    //render()
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


housingBorderPiece();
