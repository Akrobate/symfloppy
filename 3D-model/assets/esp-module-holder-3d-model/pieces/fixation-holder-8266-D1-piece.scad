use <./subpieces/holder-b-8266-D1.scad>

fixationHolder8266D1Piece();

/**
 * facadeHolder8266D1Piece
 * @name facadeHolder8266D1Piece
 * @description Fixation board holder
 * @type piece
 * @parent holder8266D1Component
 * @stl
 */
module fixationHolder8266D1Piece(
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
    holderB8826D1SubPiece(
        hole_3mm_correction,

        part_holders_width,
        part_holders_height,

        board_width,
        depth,
        height,
        throws_margin,
        throws_diameter,

        $fn = _fn
    );
}
