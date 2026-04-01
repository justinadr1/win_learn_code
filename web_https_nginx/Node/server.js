const https = require('https');
const express = require('express');
const fs = require('fs');
const path = require('path');
const mysql = require('mysql2');
const cors = require('cors');
const multer = require('multer');
const bcrypt = require('bcrypt');
const session = require('express-session');

const app = express();
const port = 3000;

app.use(session({
    secret: 'secret-key',
    resave: false,
    saveUninitialized: false
}));

const sslOptions = {
    key: fs.readFileSync('D:/nginx/conf/server.key'),
    cert: fs.readFileSync('D:/nginx/conf/server.crt')
};

app.use(cors());
app.use(express.urlencoded({ extended: true }));
app.use(express.json());
app.use(express.static(path.join(__dirname, 'public')));

const db = mysql.createConnection({
    host: '127.0.0.1',
    user: 'root',      
    password: '',
    database: 'learnweb'
});

const storage = multer.diskStorage({
    destination: (req, file, cb) => {
        const uploadPath = path.join(__dirname, '..', 'uploads');
    
        cb(null, uploadPath);
    },
    filename: (req, file, cb) => {
        cb(null, Date.now() + '-' + file.originalname);
    }
});
const upload = multer({ storage: storage });


app.post('/create-hacker', upload.single('avatar'), (req, res) => {
    const { name, expertise } = req.body;
    const avatarPath = req.file ? '/uploads/' + req.file.filename : null;

    if (!name || !expertise) 
        return res.status(400).send("Name and expertise are required");

    console.log(req.body);
    console.log(name);
    console.log(expertise);
    const sql = "INSERT INTO hackers (name_, expertise, avatar_url) VALUES (?, ?, ?)";  
    db.query(sql, [name, expertise, avatarPath], (err, result) => {
        if (err) {
            console.error(err);
            return res.status(500).send("Database error");
        }
        res.send(`Hacker ${name} registered with photo.`);
    });
});

app.get('/get-hacker/:name', (req, res) => {
    const name = req.params.name;
    db.query("SELECT * FROM hackers WHERE name_ = ?", [name], (err, results) => {
        if (err || results.length === 0) return res.status(404).send("Not found");
        res.json(results[0]); 
    });
});

app.get('/get-hackers', (req, res) => {
    const query = "SELECT name_ FROM hackers";
    db.query(query, (err, results) => {
        if (err) {
            console.error(err);
            return res.status(500).send("Database error");
        }
        res.json(results);
    });
});

app.delete('/delete-hacker/:name', (req, res) => {
    const name = req.params.name;
    const sql = "DELETE FROM hackers WHERE name_ = ?";
    db.query(sql, [name], (err, result) => {
        if (err) {
            console.error(err);
            return res.status(500).send("Database error during deleteing");
        }
        if (result.affectedRows === 0){
            return res.status(404).send("Hacker not found");
        }
        const stat = `Hacker ${name} has been removed`;
        res.send(stat);
        console.log(stat);
    });
});

app.post('/send', (req, res) => {
    // req.body.message must match the name attribute from <input>
    const msg = req.body.message;
    console.log(req.body);
    res.send(`Message ${msg} has been received by server`)
})


https.createServer(sslOptions, app).listen(port, () => {
    console.log(`Node HTTPS server running at https://127.0.0.1:${port}`);
});