include <configurations.scad>


module usbConnector(
    total_z_size = usbConnector_total_z_size,
    head_z_size = usbConnector_head_z_size,
    head_diameter = usbConnector_head_diameter,
    bottom_part_diameter = usbConnector_bottom_part_diameter,
    bottom_part_flat_size = usbConnector_bottom_part_flat_size
) {

    epsilon = 0.01;
    
    // Head
    color("Grey")
        difference() {

            union() {
                cylinder(d = head_diameter, h = head_z_size, $fn = 60);

                // Bottom part
                bottom_part_z_size = total_z_size - head_z_size;
                    translate([0, 0, -bottom_part_z_size])
                        intersection() {
                            cylinder(d = bottom_part_diameter, h = bottom_part_z_size, $fn = 60);
                            
                            translate([-bottom_part_diameter / 2, -bottom_part_flat_size / 2, 0])
                                cube([bottom_part_diameter, bottom_part_flat_size, bottom_part_z_size]);

                        }
            }

            x_size_total = 8.33;
            u_diam = 2.65;

            hull() {
                translate([-x_size_total / 2 + u_diam / 2, 0, -head_z_size + epsilon])
                    cylinder(d = u_diam, h = head_z_size * 2, $fn = 60);

                translate([x_size_total / 2 - u_diam / 2, 0, -head_z_size + epsilon])
                    cylinder(d = u_diam, h = head_z_size * 2, $fn = 60);

            }
        
        }



}

usbConnector();