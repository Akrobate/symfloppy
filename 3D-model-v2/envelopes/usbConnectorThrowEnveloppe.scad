
include <../configurations/global.scad>
include <../assets/usb-connector/configurations.scad>


module usbConnectorThrowEnveloppe(
    usbConnector_bottom_part_diameter = usbConnector_bottom_part_diameter,
    usbConnector_bottom_part_flat_size = usbConnector_bottom_part_flat_size,
    margin = usbConnectorThrowEnveloppe_margin,
    length = 20,
    _fn = usbConnectorThrowEnveloppe_fn
) {

    intersection() {
        cylinder(
            d = usbConnector_bottom_part_diameter + (margin * 2), 
            h = length, 
            center = true, 
            $fn = _fn);
        cube([
            usbConnector_bottom_part_diameter + (margin * 2),
            usbConnector_bottom_part_flat_size + (margin * 2),
            length
        ], center = true);
    }

}

usbConnectorThrowEnveloppe();
