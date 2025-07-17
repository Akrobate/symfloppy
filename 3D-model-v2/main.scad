use <./components/symfloppyBoxComponent.scad>
use <./assets/buttonAsset.scad>
use <./assets/usb-connector/usbConnector.scad>
use <./assets/FloppyDrive/FloppyDrive.scad>
use <./assets/esp-module-holder-3d-model/components/holder-8266-D1-component.scad>

include <./configurations/global.scad>


*translate([0, symfloppy_box_y_size / 2 + 1, symfloppy_box_z_size / 2])
    rotate([0,0,180])
        holder8266D1Component();    

translate([0, symfloppy_box_y_size / 2, symfloppy_box_z_size / 2])
    rotate([-90,0,0])
        usbConnector();

if (SHOW_FLOPPY_DRIVE)
    translate([0, 0 + floppy_y_offset, symfloppy_box_z_size])
        FloppyDrive();


if (SHOW_BUTTON_ON_TOP_ASSETS)
    translate([
        button_x_center_offset,
        -symfloppy_box_y_size / 2 + button_y_front_offset,
        symfloppy_box_z_size
    ])
        for (x_coord=[-button_x_spaces, 0, button_x_spaces])
            translate([x_coord, 0, 0])
                buttonAsset();


if (SHOW_BUTTON_ASSETS)
    translate([
        button_x_center_offset,
        -symfloppy_box_y_size / 2,
        symfloppy_box_z_size / 2
    ])
        for (x_coord=[-button_x_spaces, 0, button_x_spaces])
            translate([x_coord, 0, 0])
                rotate([90,0,0])
                buttonAsset();

symfloppyBoxComponent();
