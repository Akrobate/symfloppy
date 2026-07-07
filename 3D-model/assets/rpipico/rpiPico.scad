use <../../openscad_modules/breadboard/breadboard.scad>
use <../../openscad_modules/he14/he14.scad>
use <../../openscad_modules/usb-connector/usb-c-female-connector/onBoardUsbCFemaleConnector.scad>
include <../../openscad_modules/usb-connector/usb-c-female-connector/configurations.scad>

module rpiPico() {

    board_z_size = 1.5;
    usb_port_y_size = 7.39;

    translate([0, 0, getPointSize()]) {
        color("Green")
            genericModule(
                x_points = 8,
                y_points = 20,
                z_size = board_z_size
            );

        translateBreadboard(1, 1)
            he14maleAndPadn(x = 1, y = 20, board_z_size = board_z_size);
        
        translateBreadboard(8, 1)
            he14maleAndPadn(x = 1, y = 20, board_z_size = board_z_size);

        translate([getSizeFromPointCount(8) / 2, 0, board_z_size])
            onBoardUsbCFemaleConnector(
                usb_port_size = [
                    usb_c_connector_board_size.x,
                    usb_port_y_size,
                    usb_c_connector_board_size.z
                ],
                center_x = true,
                center_z = false,
                $fn = 20
            );
    }
}


/**
 * @png
 * @colorscheme BeforeDawn
 */
rpiPico();
