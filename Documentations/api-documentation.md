# 🎵 API ESP32 MIDI File Manager

API REST pour interagir avec un ESP32 hébergeant des fichiers MIDI et contrôlant un canal MIDI.

---

## 🔗 Endpoints

### `GET /channel`

**Description :** Récupère la valeur actuelle du canal MIDI.  
**Réponse :**
- `200 OK` : retourne la valeur du canal sous forme de texte brut.

**Exemple de réponse :**
3



---

### `POST /channel`

**Description :** Met à jour la valeur du canal MIDI.  
**Paramètres (formulaire POST)** :
- `channel` (obligatoire) : entier représentant le canal MIDI.

**Réponses :**
- `200 OK` : `"OK"` si la mise à jour est réussie.
- `400 Bad Request` : `"Missing value"` si le paramètre est absent.

---

### `GET /files`

**Description :** Liste les fichiers MIDI disponibles.  
**Réponse :** JSON contenant la liste des fichiers avec leur nom et taille.

**Exemple de réponse :**
```json
{
  "file_list": [
    {
      "filename": "song1.mid",
      "size": 1234
    },
    {
      "filename": "song2.mid",
      "size": 4567
    }
  ]
}
```


### DELETE /files
**Description** : Supprime un fichier MIDI.
**Paramètres** (formulaire POST ou requête HTTP) :

- `filename` (obligatoire) : nom du fichier à supprimer.

Réponses :

200 OK : "OK" si suppression réussie, "NOK" si échec.

400 Bad Request : "Missing value" si le nom du fichier est absent.

### POST /upload
Description : Upload un fichier MIDI via formulaire multipart.
Upload multipart (chunked) :

Champ fichier attendu dans le corps de la requête.

Le fichier est enregistré dans LittleFS sous le nom donné.

Réponses :

200 OK : "FILE UPLOADED" une fois l’upload terminé.

### GET /info
Description : Retourne des informations sur le système de fichiers LittleFS.
Réponse :

```json
{
  "fs_total_bytes": 14680064,
  "fs_total_bytes": 352256,
  "fs_total_bytes": 14327808
}

```