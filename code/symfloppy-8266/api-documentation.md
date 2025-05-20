# API Documentation

## Endpoints

### `GET /files`

**Description:**
Returns all midi files

**Response:**
- `200 OK`: JSON object containing the information.

**Example Response:**
```json
{
    "file_list": [
        {
            "filename": "File 1.mid",
            "size": 13000
        },
        {
            "filename": "File 2.mid",
            "size": 13000
        },
    ]
}
```