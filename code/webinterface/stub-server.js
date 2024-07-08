'use strict'

// dd if=/dev/zero of=test.img bs=1024 count=0 seek=$[1024*10]

const http = require('http');
const fs = require('fs');
const server = http.createServer();
const busboy = require('busboy');



const webinterface_html_file = 'index.html';
// const webinterface_html_file = 'index.min.html';
const port = 8080;
let channel = 14;



server.on('request', (request, response) => {

    if(request.url === '/' && request.method == 'GET') {
        return response.end(fs.readFileSync(`${__dirname}/${webinterface_html_file}`))
    }


    if(request.url === '/channel' && request.method == 'GET') {
        response.writeHead(200, {"Content-Type": "text/plain"});
        response.write(`${channel}`);
        return response.end();
    }


    if(request.url === '/channel' && request.method == 'POST') {
        const body = {};
        request.pipe(
            busboy({ headers: request.headers })
                .on('field', (name, val, info) => {
                    body[name] = val;
                })
                .on('close', () => {
                    console.log("POST /channel - value: ", `"${body.channel}"`);
                    channel = parseInt(body.channel);
                })
        );
    }


    if(request.url=== '/upload' && request.method == 'POST') {
        let filename = '';
        const bb = busboy({ headers: request.headers });
        bb.on('file', (name, file, info) => {
            filename = info.filename;
            const file_name = __dirname + '/data/my_file.mid';
            file.pipe(fs.createWriteStream(file_name));
        });
        bb.on('close', () => {
            response.writeHead(200, { 'Content-Type': 'text/plain' });
            response.end(`upload success: ${filename}`);
        });
        request.pipe(bb);
    }


});


server.listen(port, () => {
    console.log(`Server running on port ${port}`)
})
