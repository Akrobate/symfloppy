floppyFixationThrows();

module floppyFixationThrows(
    _fn = 100,
    z_size = 40,
    throws_diameter = 3.5
) {

    x_gap = 94;
    y_gap = 70;

    translate([
        x_gap / 2,
        y_gap / 2,
        0
    ])
        cylinder(d=throws_diameter, h=z_size, center=true, $fn=_fn);

    translate([
        -x_gap / 2,
        y_gap / 2,
        0
    ])
        cylinder(d=throws_diameter, h=z_size, center=true, $fn=_fn);

    translate([
        -x_gap / 2,
        -y_gap / 2,
        0
    ])
        cylinder(d=throws_diameter, h=z_size, center=true, $fn=_fn);

    translate([
        x_gap / 2,
        -y_gap / 2,
        0
    ])
        cylinder(d=throws_diameter, h=z_size, center=true, $fn=_fn);


}