holderB8826D1SubPiece();

/**
 * holderB8826D1SubPiece
 * @name holderB8826D1SubPiece
 * @description One of two holder part
 * @type subPiece
 */
module holderB8826D1SubPiece(
    hole_3mm_correction = 0.5,

    part_holders_width = 7,
    part_holders_height = 2,

    board_width = 25.6,
    depth = 6,
    height = 2.5,
    throws_margin = 3,
    throws_diameter = 3,

    _fn = 100
) {

    throws_diameter_with_correction = throws_diameter + hole_3mm_correction;
    width = board_width + (part_holders_width * 2);
    translate_usb_from_center = ((board_width / 2) - (4 + 9.4));

    increase_usb_fixation_x = 4;
    increase_usb_fixation_y = 1.5;

    difference() {
        union() {
            translate([0, 0, 0])
                cube([width, depth, height], center = true);

            color("green")
            translate([translate_usb_from_center, 4, -0.5])
                cube(
                    [
                        10 + increase_usb_fixation_x,
                        2 + increase_usb_fixation_y,
                        height+1
                    ], center = true);

            translate([- (width / 2) + (6 / 2), 0, -(height / 2) - (part_holders_height / 2)])
                color("red")
                cube([6, depth, part_holders_height], center = true);
 
            translate([(width / 2) - (6 / 2), 0, -(height / 2) - (part_holders_height / 2)])
                color("red")
                cube([6, depth, part_holders_height], center = true);
        }

        translate([width / 2 - throws_margin, 0, 0])
            cylinder(h = (height + part_holders_height) * 2, d = throws_diameter_with_correction, center = true, $fn = _fn);

        translate([- (width / 2) + throws_margin, 0, 0])
            cylinder(h = (height + part_holders_height) * 2, d = throws_diameter_with_correction, center = true, $fn = _fn);

        translate([translate_usb_from_center, 0 + 0.25 -0.5, -2])
            cube([8, 7.5, height], center = true);
    }
}
