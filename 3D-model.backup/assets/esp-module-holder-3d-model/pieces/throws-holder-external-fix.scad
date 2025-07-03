use <../envelopes/usb-hole-envelope.scad>
use <./subpieces/holder-a-8266-D1.scad>
use <./subpieces/shift-support-holder-a-8266-D1.scad>

throwsHolderExternalFix();

/**
 * throwsHolderExternalFix
 * @name throwsHolderExternalFix
 * @description Throws for external holder fix
 *    WARNING: For better results only on method
 *    hodler_throw_scale_z or hodler_throw_z_margin_top hodler_throw_z_margin_bottom
 *    should be used for better positionning of throws
 * @type throws
 * @parent
 * @stl
 */
module throwsHolderExternalFix(
    throws_dephs = 4,
    facade_width = 50,
    facade_throws_diameter = 3,
    facade_hole_3mm_correction = 0.8,
    holder_from_center_shift_z = -3.25,

    part_holders_width = 7,
    board_width = 25.6,

    hodler_throw_scale_x = 1.07,
    hodler_throw_scale_z = 1.0,

    hodler_throw_z_margin_top = 3.6,
    hodler_throw_z_margin_bottom = 2.6,

    // Heighs elements configurations
    holderA8826D1ThrowsSubPiece_height = 4,
    holderB8826D1ThrowsSubPiece_height = 2.5,
    holderB8826D1ThrowsSubPiece_part_holders_height = 2,

    _fn = 200
) {

    throws_diameter_with_correction = facade_throws_diameter + facade_hole_3mm_correction;

    translate([facade_width / 2, 0, 0])
        cylinder(h = throws_dephs, d = throws_diameter_with_correction, center = false, $fn = _fn);

    translate([-facade_width / 2, 0, 0])
        cylinder(h = throws_dephs, d = throws_diameter_with_correction, center = false, $fn = _fn);


    width = board_width + (part_holders_width * 2);

    theorical_holder_enveloppe_z_center = holder_from_center_shift_z - (holderA8826D1ThrowsSubPiece_height / 2)
            + (
                holderA8826D1ThrowsSubPiece_height
                + holderB8826D1ThrowsSubPiece_part_holders_height
                + holderB8826D1ThrowsSubPiece_height
            ) / 2;

    theorical_holder_enveloppe_height = holderA8826D1ThrowsSubPiece_height
        + holderB8826D1ThrowsSubPiece_part_holders_height
        + holderB8826D1ThrowsSubPiece_height;

    translate([
        0,
        theorical_holder_enveloppe_z_center,
        (throws_dephs / 2)
    ])
        rotate([-90,0,0]) {
            scale([hodler_throw_scale_x, 1, hodler_throw_scale_z]) {

                hull() {
                    translate([
                        0,
                        0,
                        (theorical_holder_enveloppe_height / 2) + (hodler_throw_z_margin_top / 2)
                    ])
                        cube([
                            width,
                            throws_dephs,
                            hodler_throw_z_margin_top
                        ], center = true);


                    cube([
                        width,
                        throws_dephs,
                        theorical_holder_enveloppe_height
                    ], center = true);

                    translate([
                        0,
                        0,
                        -(theorical_holder_enveloppe_height / 2) - (hodler_throw_z_margin_bottom / 2)
                    ])
                        cube([
                            width,
                            throws_dephs,
                            hodler_throw_z_margin_bottom
                        ], center = true);
                }
            }
        }
}
