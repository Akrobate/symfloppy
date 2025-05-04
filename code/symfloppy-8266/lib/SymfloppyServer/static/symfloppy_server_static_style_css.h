#include <Arduino.h>

const char symfloppy_server_static_style_css[] PROGMEM = R"rawliteral(
.block-position {
    max-width: 500px;
    margin-left: auto;
    margin-right: auto;
}
body {
    font-family:Arial, Helvetica;
}
.block {
    border: 1px solid grey;
    border-radius: 10px;
    padding: 20px;
    
    margin-bottom: 20px;
}
.block .title {
    font-weight: bold;
}
.block .content {
    margin: 20px;
}
span {
    font-style: italic;  
}
.valid {
    color: #006600;
}
.error {
    color: red;
}
button {
    width: 140px;
    height: 30px;
    border: 1px solid grey;
    border-radius: 10px;
}
.center {
    text-align: center;
}
)rawliteral";

