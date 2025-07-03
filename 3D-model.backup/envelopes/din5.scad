
color("Yellow")
    throws_din5();

color(alpha = 0.5)
    din5();



module din5() {

    $fn = 100;
    thickness = 1.85;

    hull() {
        translate([-11, 0, 0])
            cylinder(r = ((3.3 / 2) + 1.5), h = thickness, center=true, $fn = $fn);

        cylinder(d = 19.14, h = thickness, center=true, $fn = $fn);

        translate([11, 0, 0])
            cylinder(r = ((3.3 / 2) + 1.5), h = thickness, center=true, $fn = $fn);
    };
}


module throws_din5(
    facade_throws_diameter = 3,
    facade_hole_3mm_correction = 0.8,
    main_diameter_correction = 1,
    throws_height = 4,
    center = true,
    $fn = 100
) {    

    fixation_diameter = facade_throws_diameter + facade_hole_3mm_correction;
    translate([-11, 0, 0])
        cylinder(d = fixation_diameter, h = throws_height, center = center, $fn = $fn);

    cylinder(d = 15 + main_diameter_correction, h = throws_height, center = center, $fn = $fn);

    translate([11, 0, 0])
        cylinder(d = fixation_diameter, h = throws_height, center = center, $fn = $fn);
}