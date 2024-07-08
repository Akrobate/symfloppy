module centeredPaneSubPiece(x_size, y_size, z_size) {
    cube(
        [
            x_size,
            y_size,
            z_size,
        ],
        center = true
    );
}