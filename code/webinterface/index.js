function $(selector, element = document) {
    return element.querySelector(selector)
}


// INIT
document.addEventListener('DOMContentLoaded', async () => {

    const button_channel_save = document.getElementById('button_channel_save')

    const input_file = document.getElementById('input_file')
    const button_upload = document.getElementById('button_upload')
    const span_upload_help = document.getElementById('span_upload_help')
    const span_channel_help = document.getElementById('span_channel_help')

    const corporate_mention = document.getElementById('corporate_mention')

    await loadSongsList();

    function message(el, txt, add_class='') {
        el.classList.remove('valid')
        el.classList.remove('error')
        if (add_class)
            el.classList.add(add_class)
        el.innerText = txt
    }


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

async function serverGetSongList() {
    try {
        const result = await fetch('/files',
            {
                method: 'GET',
            }
        )
        const data = await result.json()
        return data.file_list
    } catch (error) {
        console.log('serverGetSongList - Error:', error)
        return []
    }
}

async function loadSongsList() {
    const _el = $('#song-list')
    await loadList(
        _el,
        $('#template-song-list-item'),
        $('#template-list-loader'),
        () => serverGetSongList()
    )
}


async function loadList(
    _list_el,
    list_item_el,
    template_el,
    data_function
) {
    _list_el.innerHTML = template_el.innerHTML
    const data_list = await data_function()
    _list_el.innerHTML = ''
    const template_html = list_item_el.innerHTML
    data_list.forEach((data, index) => {
        let html = template_html
        Object.keys(data).forEach((key) => {
            html = html.replaceAll(`{{ ${key} }}`, data[key])
        })
        html = html.replaceAll('{{ index }}', index)
        const _new_el = document.createElement("div")
        _new_el.innerHTML = html
        _list_el.appendChild(_new_el.firstElementChild)
    })
}


async function removeSong(element) {
    console.log('removeSong', element)
}