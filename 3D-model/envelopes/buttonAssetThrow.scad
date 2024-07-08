buttonAssetThrow();


module buttonAssetThrow(
    z_size = 40,
    diameter_correction = 1,
    _fn = 100
) {
    
    diameter = 11.83 + diameter_correction;

    cylinder(
        d = diameter,
        h = z_size,
        center = true,
        $fn = _fn
    );

}