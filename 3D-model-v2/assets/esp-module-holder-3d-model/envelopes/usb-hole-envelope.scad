usbHoleEnvelope();

module usbHoleEnvelope(
    height = 6.5,
    width = 12,
    thickness = 10,
    center = true,
    $fn = 200
) {
    hull() {
        translate([- width / 2, 0, 0])
            cylinder(h = thickness, d = height, center = center, $fn = $fn);

        translate([width / 2, 0, 0])
            cylinder(h = thickness, d = height, center = center, $fn = $fn);
    }
}