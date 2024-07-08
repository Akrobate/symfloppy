const express = require('express');
const bodyParser = require('body-parser');
const fs = require('fs');
const multer = require('multer');

const upload = multer({
    storage: multer.diskStorage({
        destination: (_, __, callback) => {
            callback(null, './data');
        },
        filename: (_, file, callback) => {
            callback(null, file.originalname);
        },
    })
});

const port = 8080;
// const webinterface_html_file = 'index.min.html';
const webinterface_html_file = 'index.html';

const app = express();
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true })); 


let channel = 13;

app.get('/', (request, response) => {
    response.sendFile(webinterface_html_file, {root: __dirname })
});

app.get('/channel', (request, response) => {
    response.status(200).send(`${channel}`);
});

app.post('/channel', upload.array(), (request, response) => {
    console.log(request.body.channel);
    channel = request.body.channel;
    response.status(200).send(`OK`);
});

app.post('/upload', upload.single("file"), (request, response) => {
    console.log(request.body);
    response.status(200).send(`OK`);
});

app.get('/files', (request, response) => {
    const file_list = fs.readdirSync('./data');
    const formated_file_list = file_list.map((file) => ({
       filename: file,
       size: 123, 
    }));
    response.status(200).json({
        file_list: formated_file_list
    });
});

app.delete('/files', upload.array(), (request, response) => {
    const filename = request.body.filename;
    fs.unlinkSync('./data/' + filename);
    response.status(200).send(`OK`);
});


app.listen(port, () => {
  console.log(`Example app listening on port ${port}`)
})