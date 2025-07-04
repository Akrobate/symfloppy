holderA8826D1SubPiece();

/**
 * holderA8826D1SubPiece
 * @name holderA8826D1SubPiece
 * @description One of two holder part
 * @type subPiece
 */
module holderA8826D1SubPiece(
    hole_3mm_correction = 0.35,
    encaps_width_correction = 0.4,

    part_holders_width = 7,
    board_width = 25.6,
    encaps_width = 23.36,
    encaps_height = 1,
    depth = 6,
    support_depth = 4.5,

    height = 4,
    throws_margin = 3,
    throws_diameter = 3,

    $fn = 100
) {

    width = board_width + (part_holders_width * 2);
    throws_diameter_with_correction = throws_diameter + hole_3mm_correction;
    encaps_width_with_correction = encaps_width + encaps_width_correction;

    difference() {
        union() {
            translate([0, 0, 0])
                cube([width, depth, height], center = true);

            translate([0, (depth / 2) + (support_depth / 2), 0])
                cube([14, support_depth, height], center = true);
        }

        translate([
            - (board_width - encaps_width_with_correction),
            0,
            height - encaps_height
        ])
            cube([
                encaps_width_with_correction,
                20,
                height
            ], center = true);

        translate([width / 2 - throws_margin, 0, 0])
            cylinder(h = height * 2, d = throws_diameter_with_correction, center = true, $fn = $fn);

        translate([- (width / 2) + throws_margin, 0, 0])
            cylinder(h = height * 2, d = throws_diameter_with_correction, center = true, $fn = $fn);

    }
}
