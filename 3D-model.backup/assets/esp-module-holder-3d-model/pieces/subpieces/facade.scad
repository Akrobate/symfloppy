facadeSubPiece();

/**
 * facadeSubPiece
 * @name facadeSubPiece
 * @description Facade with usb throws
 * @type subPiece
 */
module facadeSubPiece(
    height = 20,
    width = 50,
    thickness = 2,
    
    hole_3mm_correction = 0.5,
    throws_diameter = 3,
    _fn = 200
) {

    throws_diameter_with_correction =  throws_diameter + hole_3mm_correction;

    difference() {    
        hull() {
            translate([- width / 2, 0, 0])
                cylinder(h = thickness, d = height, center = true, $fn = _fn);

            translate([width / 2, 0, 0])
                cylinder(h = thickness, d = height, center = true, $fn = _fn);
        }

        translate([width / 2, 0, 0])
            cylinder(h = height * 2, d = throws_diameter_with_correction, center = true, $fn = _fn);

        translate([-width / 2, 0, 0])
            cylinder(h = height * 2, d = throws_diameter_with_correction, center = true, $fn = _fn);

    }
}
