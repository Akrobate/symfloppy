#ifndef SymfloppyServer_h
#define SymfloppyServer_h

#include <ESPAsyncWebServer.h>

#include "AsyncJson.h"
#include "ArduinoJson.h"

#include <LittleFS.h>


#include "static/symfloppy_server_static_index_html.h"
#include "static/symfloppy_server_static_style_css.h"
#include "static/symfloppy_server_static_index_js.h"
// #include "static/round_timer_server_static_repository_js.h"


// const char index_html[] PROGMEM = R"rawliteral(
// <meta name=viewport content="width=device-width,initial-scale=1"><style>.block-position{max-width:500px;margin-left:auto;margin-right:auto}body{font-family:Arial,Helvetica}.block{border:1px solid grey;border-radius:10px;padding:20px;margin-bottom:20px}.block .title{font-weight:700}.block .content{margin:20px}span{font-style:italic}.valid{color:#060}.error{color:red}button{width:140px;height:30px;border:1px solid grey;border-radius:10px}.center{text-align:center}</style><h1 class=block-position><span style=color:red>S</span><span style=color:grey>ym</span>floppy</h1><div class="block block-position"><div class=title>Bienvenue</div><p>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.</div><div class="block block-position"><div class=title>Midi input channel</div><div class=content><select name=channel id=select_channel_save></select></div><div class=content><span id=span_channel_help></span></div><div class="content center"><button type=button id=button_channel_save>Save</button></div></div><div class="block block-position"><div class=title>Fichier Music box</div><div class=content><input type=file id=input_file></div><div class=content><span id=span_upload_help></span></div><div class="content center"><button type=button id=button_upload>Upload</button></div></div><p class=block-position style=text-align:right id=corporate_mention>Software version: v1.0</p><script>const button_channel_save=document.getElementById("button_channel_save"),select_channel_save=document.getElementById("select_channel_save"),input_file=document.getElementById("input_file"),button_upload=document.getElementById("button_upload"),span_upload_help=document.getElementById("span_upload_help"),span_channel_help=document.getElementById("span_channel_help"),corporate_mention=document.getElementById("corporate_mention");function message(e,n,a=""){e.classList.remove("valid"),e.classList.remove("error"),a&&e.classList.add(a),e.innerText=n}for(let e=1;e<17;e++){const n=document.createElement("option");n.innerText="channel "+e,n.value=e,select_channel_save.appendChild(n)}fetch("/channel").then((e=>e.json())).then((e=>select_channel_save.value=e)),button_channel_save.addEventListener("click",(async()=>{const e=select_channel_save.value;try{let n=new FormData;n.append("channel",e),await fetch("/channel",{body:n,method:"POST"}),message(span_channel_help,"Channel saved","valid")}catch(e){message(span_channel_help,"Error occured","error")}})),button_upload.addEventListener("click",(async()=>{const e=input_file.files[0];if(void 0===e)return void message(span_upload_help,"Please select file first","error");if(e.size>1e5)return void message(span_upload_help,`File size is too large (${Math.ceil(e.size/1e3)}kb), max file size is 100kb`,"error");message(span_upload_help,"Uploading...");const n=new FormData;n.append("file",input_file.files[0]),console.log(n);try{await fetch("/upload",{method:"POST",body:n})}catch(e){message(span_upload_help,"Error occured","error")}message(span_upload_help,"File uploaded","valid")}))</script>
// )rawliteral";


class SymfloppyServer {

    public:

        int channel;

        AsyncWebServer * server;

        SymfloppyServer(int port);
        void init();
        void begin();
};

#endif
