include <../configuration.scad>
holdersPiecesThrows();

module holdersPiecesThrows(
    symfloppy_box_x_size = symfloppy_box_x_size,
    holder_piece_x_from_z_offset = holder_piece_x_from_z_offset,
    symfloppy_box_pane_thickness = symfloppy_box_pane_thickness,
    throws_diameter = 3.5,
    _fn = 100
) {


    translate([
        symfloppy_box_x_size / 2 - holder_piece_x_from_z_offset - symfloppy_box_pane_thickness,
        holder_piece_y_centered_holder_piece_gap / 2,
        0
    ])
        cylinder(d=throws_diameter, h=symfloppy_box_pane_thickness * 2, center=true, $fn=_fn);


    translate([
        symfloppy_box_x_size / 2 - holder_piece_x_from_z_offset - symfloppy_box_pane_thickness,
        -holder_piece_y_centered_holder_piece_gap / 2,
        0
    ])
        cylinder(d=throws_diameter, h=symfloppy_box_pane_thickness * 2, center=true, $fn=_fn);

    translate([
        - symfloppy_box_x_size / 2 + holder_piece_x_from_z_offset + symfloppy_box_pane_thickness,
        holder_piece_y_centered_holder_piece_gap / 2,
        0
    ])
        cylinder(d=throws_diameter, h=symfloppy_box_pane_thickness * 2, center=true, $fn=_fn);
    
    translate([
        - symfloppy_box_x_size / 2 + holder_piece_x_from_z_offset + symfloppy_box_pane_thickness,
        -holder_piece_y_centered_holder_piece_gap / 2,
        0
    ])
        cylinder(d=throws_diameter, h=symfloppy_box_pane_thickness * 2, center=true, $fn=_fn);
}