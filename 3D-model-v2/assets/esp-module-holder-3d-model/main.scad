use <./components/holder-8266-D1-component.scad>
use <./components/holder-8266-D1-component-with-external-fix.scad>
use <./components/holder-8266-D1-component-with-internal-fix.scad>


holder8266D1Component();

translate([-100,0,0])
    holder8266D1ComponentWithExternalFix();

translate([100,0,0])
    holder8266D1ComponentWithInternalFix();