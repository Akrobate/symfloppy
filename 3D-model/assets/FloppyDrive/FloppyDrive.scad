
module FloppyDrive() {


    x_throws_gap = 94;
    y_throws_gap = 70;

    x_size = 101.6;
    y_size = 150;
    z_size = 25.4;

    y_throw_facade_offset = 35;

    translate([
        0,
        y_size / 2 - y_throw_facade_offset - y_throws_gap / 2,
        z_size / 2
    ]) {

        facade_y_size = 4;

        translate([0,facade_y_size / 2, 0])
            cube(
                [
                    x_size,
                    y_size - facade_y_size,
                    z_size
                ],
                center = true
            );
        translate([0, -y_size / 2 + facade_y_size / 2, 0]) {
            color("DarkSlateGray") {
                difference() {
                    cube(
                        [
                            x_size,
                            facade_y_size,
                            z_size
                        ],
                        center = true
                    );

                    translate([0, -1, 3])
                    cube(
                        [
                            x_size - 5.4 * 2,
                            facade_y_size,
                            6.15
                        ],
                        center = true
                    );
                }
                button_x_size = 11.8;
                button_y_size = 6.2;
                button_z_size = 4.7;

                button_right_x_offest = 12;
                button_bottom_z_offest = 2.22;
                
                translate(
                    [
                        x_size / 2 - button_right_x_offest - button_x_size / 2,
                        -facade_y_size / 2 - button_y_size / 2,
                        -z_size / 2 + button_z_size / 2 + button_bottom_z_offest
                    ]
                )
                    cube(
                        [
                            button_x_size,
                            button_y_size,
                            button_z_size
                        ],
                        center = true
                    );
            }
        }
    }
}



FloppyDrive();