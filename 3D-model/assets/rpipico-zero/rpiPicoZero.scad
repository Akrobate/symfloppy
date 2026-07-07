use <../../openscad_modules/breadboard/breadboard.scad>
use <../../openscad_modules/he14/he14.scad>
use <../../openscad_modules/usb-connector/usb-c-female-connector/onBoardUsbCFemaleConnector.scad>
include <../../openscad_modules/usb-connector/usb-c-female-connector/configurations.scad>


module rpiPicoZero() {

    board_z_size = 1.5;
    usb_port_y_size = 7.39;

    epsilon = 0.01;

    x_points = 7;
    y_points = 9;

    translate([0,0, getPointSize()]) {
        color("RoyalBlue")
            genericModule(
                x_points = x_points,
                y_points = y_points,
                z_size = board_z_size
            );

        translateBreadboard(1, 1)
            he14maleAndPadn(x = 1, y = y_points, board_z_size = board_z_size);
        
        translateBreadboard(7, 1)
            he14maleAndPadn(x = 1, y = y_points, board_z_size = board_z_size);

        translateBreadboard(2, y_points)
            translate([0, 0, board_z_size + epsilon])
                he14padn(x = 5, y = 1);

        
        translate([getSizeFromPointCount(x_points) / 2, 0, board_z_size])
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
rpiPicoZero();
