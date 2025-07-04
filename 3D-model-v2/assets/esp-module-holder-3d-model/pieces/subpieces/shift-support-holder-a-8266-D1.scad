/**
 * shiftSupportHolderA8266D1
 * @name shiftSupportHolderA8266D1
 * @description Shift holder component
 * @type subPiece
 */
module shiftSupportHolderA8266D1(
    shift_size,
    width,
    holder_a_height,
    board_width,
    encaps_width_with_correction,
    encaps_height
) {
    difference() {
        cube(
            [
                width,
                shift_size,
                holder_a_height
            ],
            center = true
        );

        translate([
            - (board_width - encaps_width_with_correction),
            0,
            holder_a_height - encaps_height
        ])
            cube(
                [
                    encaps_width_with_correction,
                    shift_size * 1.1,
                    holder_a_height
                ],
                center = true
            );
    }
}

