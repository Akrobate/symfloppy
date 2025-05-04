#include <Arduino.h>

const char symfloppy_server_static_index_html[] PROGMEM = R"rawliteral(
<html>
    <head>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <script src="index.js"></script>
        <link rel="stylesheet" href="style.css">
    </head>

    <body>
        <h1 class="block-position">
            <span style="color:red">S</span><span style="color:grey">ym</span>floppy
        </h1>

        <div class="block block-position">
            <div class="title">
                Bienvenue
            </div>
            <p>
                Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor
                incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud
                exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.
            </p>
        </div>


        <div class="block block-position">
            <div class="title">
                Midi input channel
            </div>
            <div class="content">
                <select name="channel" id="select_channel_save">
                </select>
            </div>
            <div class="content">
                <span id="span_channel_help"></span>
            </div>
            <div class="content center">
                <button type="button" id="button_channel_save" >
                    Save
                </button>
            </div>
        </div>


        <div class="block block-position">
            <div class="title">
                Fichier Music box
            </div>
            <div class="content">
                <input type="file" id="input_file" accept=".mid,.midi">
            </div>
            <div class="content">
                <span id="span_upload_help"></span>
            </div>

            <div class="content center">
                <button type="button" id="button_upload">
                    Upload
                </button>
            </div>
        </div>

        <p class="block-position" style="text-align: right;" id="corporate_mention">
            Software version: v1.0
        </p>
    </body>
</html>
)rawliteral";

