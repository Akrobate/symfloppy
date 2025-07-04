use <../envelopes/usb-hole-envelope.scad>

throwsHolderInternalFix();


/**
 * throwsHolderInternalFix
 * @name throwsHolderInternalFix
 * @description Throws for internal holder fix
 * @type throws
 * @parent
 * @stl
 */
module throwsHolderInternalFix(
    throws_dephs = 4,
    facade_width = 50,
    facade_throws_diameter = 3,
    facade_hole_3mm_correction = 0.5,

    _fn = 100
) {

    throws_diameter_with_correction = facade_throws_diameter + facade_hole_3mm_correction;

    translate([facade_width / 2, 0, 0])
        cylinder(h = throws_dephs, d = throws_diameter_with_correction, center = false, $fn = _fn);

    translate([-facade_width / 2, 0, 0])
        cylinder(h = throws_dephs, d = throws_diameter_with_correction, center = false, $fn = _fn);


    usbHoleEnvelope(
        thickness = throws_dephs,
        center = false
    );

}