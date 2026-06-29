use <../envelopes/floppyFixationThrows.scad>

use <../openscad_modules/housing/roundedPane.scad>
use <../openscad_modules/commons/forEachCoord.scad>

include <../configurations/global.scad>

/**
 * topPanePiece
 * @name topPanePiece
 * @description topPanePiece CNC piece
 * @type piece
 * @parent housingComponent
 */
module topPanePiece(
    x_size = symfloppy_box_x_size,
    y_size = symfloppy_box_y_size,
    pane_thickness = symfloppy_box_pane_thickness,
    button_y_front_offset = button_y_front_offset,
    button_x_spaces = button_x_spaces,
    button_x_center_offset = button_x_center_offset,
    holder_piece_x_from_z_offset = holder_piece_x_from_z_offset,
    floppy_y_offset = floppy_y_offset,
    round_edges_radius = facade_front_round_edges_radius,
    facade_throws_margin = facade_throws_margin,
    throws_diameter = wood_throw_m3_diameter,
    _fn = 100

) {

    floppy_cables_throws_round_radius = 3;
    floppy_cables_throws_main_coords = [x_size - 30, y_size - 10];
    floppy_cables_throws_main_size = [20, 6, 5];

    floppy_cables_throws_power_coords = [30, y_size - 10];
    floppy_cables_throws_power_size = [20, 6, 5];

    echo("topPanePiece", x_size=x_size, y_size=y_size);
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



        translate([0, floppy_y_offset, 0])
            floppyFixationThrows(
                z_size = pane_thickness * 4,
                throws_diameter = throws_diameter
            );

        translate([-x_size / 2, -y_size / 2])
            forEachCoord(throws_coords_list)
                cylinder(
                    d = throws_diameter,
                    h = pane_thickness * 4,
                    center = true,
                    $fn = 100
                );
        
        translate([
            -x_size / 2 + floppy_cables_throws_main_coords.x,
            -y_size / 2 + floppy_cables_throws_main_coords.y
        ])
            #roundedPane(
                floppy_cables_throws_main_size,
                r1 = floppy_cables_throws_round_radius,
                r2 = floppy_cables_throws_round_radius,
                center = true,
                $fn = _fn
            );

        translate([
            -x_size / 2 + floppy_cables_throws_power_coords.x,
            -y_size / 2 + floppy_cables_throws_power_coords.y
        ])
            #roundedPane(
                floppy_cables_throws_power_size,
                r1 = floppy_cables_throws_round_radius,
                r2 = floppy_cables_throws_round_radius,
                center = true,
                $fn = _fn
            );
        
    }
}





/**
 * @png
 * @colorscheme BeforeDawn
 */
topPanePiece();
