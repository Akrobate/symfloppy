buttonAsset();


module buttonAsset(
    _fn = 100
) {
    
    diameter = 11.83;
    head_diameter = 13.84;
    head_z_size = 1.9;
    button_without_head_z_size = 15.8;
    button_diameter = 8.5;
    button_border_diameter = 11;

    color("DarkGray") {
        translate([0, 0, -button_without_head_z_size])
            cylinder(
                d = diameter,
                h = button_without_head_z_size,
                center = false,
                $fn = _fn
            );

        difference() {
            cylinder(
                d1 = head_diameter,
                d2 = button_border_diameter,
                h = head_z_size,
                center=false,
                $fn = _fn
            );

            translate([0,0,-0.05])
                cylinder(
                    d = button_diameter + 0.7,
                    h = head_z_size + 0.1,
                    center=false,
                    $fn = _fn
                );
        }

        cylinder(
            d = button_diameter,
            h = head_z_size,
            center=false,
            $fn = _fn
        );
    }
}
