use <./subpieces/facade.scad>
use <./subpieces/holder-a-8266-D1.scad>
use <./subpieces/shift-support-holder-a-8266-D1.scad>
use <../envelopes/usb-hole-envelope.scad>

rotate([90,0,0])
    facadeHolder8266D1Piece();


/**
 * facadeHolder8266D1Piece
 * @name facadeHolder8266D1Piece
 * @description Facade with board holder
 * @type piece
 * @parent holder8266D1Component
 * @stl
 */
module facadeHolder8266D1Piece(
    board_width = 25.6,
    encaps_width = 23.36,
    encaps_height = 1,

    facade_height = 20,
    facade_width = 50,
    facade_thickness = 2,
    facade_hole_3mm_correction = 0.5,
    facade_throws_diameter = 3,

    usb_hole_height = 6.5,
    usb_hole_width = 12,
    usb_hole_thickness = 10,

    holder_a_hole_3mm_correction = 0.35,
    holder_a_encaps_width_correction = 0.4,
    holder_a_part_holders_width = 7,
    holder_a_depth = 6,
    holder_a_support_depth = 4.5,
    holder_a_height = 4,
    holder_a_throws_margin = 3,
    holder_a_throws_diameter = 3,

    holder_a_facade_shift_size = 0.1,

    holder_positionning_z = 0,
    
    fn_facade = 200,
    fn_holder_a = 100
) {

    width = board_width + (holder_a_part_holders_width * 2);
    encaps_width_with_correction = encaps_width + holder_a_encaps_width_correction;

    holder_positionning_x = 0;
    holder_positionning_y = holder_a_depth / 2 + facade_thickness / 2;
    holder_from_center_shift_z = -3.25;

    // Facade piece
    rotate([90,0,0])
        difference() {
            facadeSubPiece(
                height = facade_height,
                width = facade_width,
                thickness = facade_thickness,
                
                hole_3mm_correction = facade_hole_3mm_correction,
                throws_diameter = facade_throws_diameter,
                _fn = fn_facade
            );
            translate(
                [
                    0,
                    holder_positionning_z,
                    0
                ]
            )
                usbHoleEnvelope(
                    height = usb_hole_height,
                    width = usb_hole_width,
                    thickness = usb_hole_thickness
                );
        }

    // Shift support
    color("yellow")
        translate(
            [
                0,
                holder_a_facade_shift_size / 2 + facade_thickness / 2,
                holder_from_center_shift_z + holder_positionning_z
            ]
        ) 
            shiftSupportHolderA8266D1(
                shift_size = holder_a_facade_shift_size,
                width = width,
                holder_a_height = holder_a_height,
                board_width = board_width,
                encaps_width_with_correction = encaps_width_with_correction,
                encaps_height = encaps_height
            );

    translate([0, holder_a_facade_shift_size, 0])
        // Bottom piece
        translate(
            [
                holder_positionning_x,
                holder_positionning_y,
                holder_from_center_shift_z + holder_positionning_z
            ]
        )
            holderA8826D1SubPiece(
                hole_3mm_correction = holder_a_hole_3mm_correction,
                encaps_width_correction = holder_a_encaps_width_correction,

                part_holders_width = holder_a_part_holders_width,
                board_width = board_width,
                encaps_width = encaps_width,
                encaps_height = encaps_height,
                depth = holder_a_depth,
                support_depth = holder_a_support_depth,

                height = holder_a_height,
                throws_margin = holder_a_throws_margin,
                throws_diameter = holder_a_throws_diameter,

                $fn = fn_holder_a
            );
}

