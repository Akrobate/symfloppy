include <../configurations/global.scad> 


/**
 * holderPiece
 * @name holderPiece
 * @description holderPiece
 * @type piece
 * @parent
 */
module holderPiece(
    z_size = symfloppy_box_z_size - (symfloppy_box_pane_thickness * 2),
    y_size = 14,
    x_from_z_offset = holder_piece_x_from_z_offset,
    insert_throw_length = 6,
    _fn = 100
) {
    DEBUG_TROWS_CHECK = true;

    if (DEBUG_TROWS_CHECK) {
        translate([0, 0, -5])
            insertThrows(
                z_size = z_size + 10,
                x_from_z_offset = x_from_z_offset + 5,
                insert_throw_length = insert_throw_length * 2,
                insert_throw_diameter = 2
            );
    }

    diameter = y_size;  

    color("white", alpha = 0.31)

    difference() {
        hull() {
            difference() {
                cylinder(d = diameter, h = z_size, $fn = _fn);
                translate([0, -diameter / 2, -0.05])
                    cube([diameter, diameter, z_size + 0.1]);
            }
            translate([0, -diameter / 2, 0])
                cube([x_from_z_offset, diameter, z_size]);
        }
    
        insertThrows(
            z_size = z_size,
            x_from_z_offset = x_from_z_offset,
            insert_throw_length = insert_throw_length
        );
    }
}


module insertThrows(
    z_size = 20,
    x_from_z_offset = 10,
    insert_throw_diameter = 4.2,
    insert_throw_length = 6,
    throw_offset = 0.01,
) {

    translate([0,0, insert_throw_length / 2])
        insertThrow(
            insert_throw_diameter = insert_throw_diameter,
            insert_throw_length = insert_throw_length,
            throw_offset = throw_offset
        );

    translate([0,0, z_size-(insert_throw_length / 2)])
        insertThrow(
            insert_throw_diameter = insert_throw_diameter,
            insert_throw_length = insert_throw_length,
            throw_offset = throw_offset
        );

    translate([x_from_z_offset-(insert_throw_length / 2), 0, z_size / 2])
        rotate([0,90,0])
            insertThrow(
                insert_throw_diameter = insert_throw_diameter,
                insert_throw_length = insert_throw_length,
                throw_offset = throw_offset
            );
}


module insertThrow(
    insert_throw_diameter = 4.2,
    insert_throw_length = 6,
    throw_offset = 0.01,
    _fn = 100
) {
    cylinder(d = insert_throw_diameter, h = insert_throw_length + throw_offset, center = true, $fn = _fn);
}


holderPiece(
    _fn = 256
);
