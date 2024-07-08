include <../configuration.scad> 

// insert sizes
// * diam = 4.6
// * length = 5.7


holderPiece();



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



/*
module holderPiece(

    insert_throw_diameter = 4.2,
    insert_throw_length = 6,

    _fn = 500
) {

    half_size_x = size_x / 2;
    half_size_y = size_y / 2;
    half_size_z = size_z / 2;

    insert_z_offset_x = 10;
    insert_z_offset_y = 10;
    insert_x_offset = 10;
    insert_y_offset = 10;

    half_size_x_without_radius = half_size_x - round_border_radius;
    half_size_y_without_radius = half_size_y - round_border_radius;

    if (false) {
        insertThrows(
            half_size_x = half_size_x,
            half_size_y = half_size_y,
            half_size_z = half_size_z,
            insert_throw_diameter = insert_throw_diameter,
            insert_throw_length = insert_throw_length,

            insert_x_offset = insert_x_offset,
            insert_y_offset = insert_y_offset,

            insert_z_offset_x = insert_z_offset_x,
            insert_z_offset_y = insert_z_offset_y,
            _fn = _fn
        );
    }

    difference() {
        color(alpha = 0.1)
            hull() {
                translate([-(half_size_x - round_corner_radius), -(half_size_y - round_corner_radius), 0])
                    cylinder(r = round_corner_radius, h = size_z, center = true, $fn = _fn);

                translate([-half_size_x_without_radius, half_size_y_without_radius, 0])
                    cylinder(r = round_border_radius, h = size_z, center = true, $fn = _fn);
                
                translate([half_size_x_without_radius, -half_size_y_without_radius, 0])
                    cylinder(r = round_border_radius, h = size_z, center = true, $fn = _fn);
            }
        
        if (true) {
            insertThrows(
                half_size_x = half_size_x,
                half_size_y = half_size_y,
                half_size_z = half_size_z,
                insert_throw_diameter = insert_throw_diameter,
                insert_throw_length = insert_throw_length,

                insert_x_offset = insert_x_offset,
                insert_y_offset = insert_y_offset,

                insert_z_offset_x = insert_z_offset_x,
                insert_z_offset_y = insert_z_offset_y,

                _fn = _fn
            );
        }
    }

}





module insertThrows(
    half_size_x,
    half_size_y,
    half_size_z,
    insert_throw_diameter,
    insert_throw_length,
    insert_x_offset,
    insert_y_offset,
    insert_z_offset_x,
    insert_z_offset_y,
    _fn
) {
    throw_offset = 0.01;

    // Y throw
    translate(
        [
            -half_size_x + insert_y_offset,
            (insert_throw_length / 2) - half_size_y - (throw_offset / 2),
            0
        ]
    )
        rotate([90, 0, 0])
            cylinder(d = insert_throw_diameter, h = insert_throw_length + throw_offset, center = true, $fn = _fn);

    // X throw
    translate(
        [
            (insert_throw_length / 2) - half_size_x - (throw_offset / 2),
            -half_size_y + insert_x_offset,
            0
        ]
    )
        rotate([0, 90, 0])
            cylinder(d = insert_throw_diameter, h = insert_throw_length + throw_offset, center = true, $fn = _fn);

    // Z throw
    translate(
        [
            -half_size_x + insert_z_offset_x,
            -half_size_y + insert_z_offset_y,
            -(insert_throw_length / 2) + half_size_z + (throw_offset / 2)
        ]
    )
        rotate([0, 0, 90])
            cylinder(d = insert_throw_diameter, h = insert_throw_length + throw_offset, center = true, $fn = _fn);
}

*/