#include <Arduino.h>

const char symfloppy_server_static_index_js[] PROGMEM = R"rawliteral(


// INIT
document.addEventListener('DOMContentLoaded', async () => {

    const button_channel_save = document.getElementById('button_channel_save')
    const select_channel_save = document.getElementById('select_channel_save')

    const input_file = document.getElementById('input_file')
    const button_upload = document.getElementById('button_upload')
    const span_upload_help = document.getElementById('span_upload_help');
    const span_channel_help = document.getElementById('span_channel_help');

    const corporate_mention = document.getElementById('corporate_mention');


    function message(el, txt, add_class='') {
        el.classList.remove('valid')
        el.classList.remove('error')
        if (add_class)
            el.classList.add(add_class)
        el.innerText = txt
    }

    for(let i = 1; i < 17; i++) {
        const option = document.createElement('option');
        option.innerText = 'channel ' + i
        option.value = i
        select_channel_save.appendChild(option)
    }

    fetch('/channel')
        .then((response) => response.json())
        .then((value) => select_channel_save.value = value);


    button_channel_save.addEventListener('click', async () => {
        const data = select_channel_save.value
        try {
            let formData = new FormData()
            formData.append('channel', data)
            await fetch('/channel',
                {
                    body: formData,
                    method: 'POST',
                }
            )
            message(span_channel_help, 'Channel saved', 'valid')
        } catch (error) {
            message(span_channel_help, 'Error occured', 'error')
        }
    })


    button_upload.addEventListener('click', async () => {
        const file = input_file.files[0]
        if (file === undefined) {
            message(span_upload_help, 'Please select file first', 'error')
            return
        }
        if (file.size > 100000) {
            message(span_upload_help, `File size is too large (${Math.ceil(file.size / 1000)}kb), max file size is 100kb`, 'error')
            return
        }
        message(span_upload_help, 'Uploading...')

        const form_data = new FormData()
        form_data.append('file', input_file.files[0])

        console.log(form_data)
        try {
            await fetch('/upload', {
                method: 'POST',
                body: form_data,
                //headers: {
                //    "Content-Type": "multipart/form-data"
                //}
            })
        } catch (error) {
            message(span_upload_help, 'Error occured', 'error')
        }
        
        message(span_upload_help, 'File uploaded', 'valid')

    })


})
)rawliteral";

