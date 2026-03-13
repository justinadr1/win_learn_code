const express = require('express');
const fs = require('fs');
const path = require('path');
const mysql = require('mysql2');
const cors = require('cors');
const app = express();
const port = 3000;

app.use(cors());
app.use(express.urlencoded({ extended: true }));
app.use(express.json());

const usersFile = path.join(__dirname, 'users.txt');

const db = mysql.createConnection({
    host: '127.0.0.1',
    user: 'root',      
    password: '',
    database: 'learnweb'
});

app.post('/add_user_node', (req, res) => {
    const username = req.body.user;
     
    console.log(username);

    if (username) {
        fs.appendFile(usersFile, username + '\n', (err) => {
            res.send("New user added");
        });
    } else {
        res.status(400).send("No user provided");
    } 
});



app.get('/get_users_mysql_node', (req, res) => {
    const query = "SELECT username FROM users";
    db.query(query, (err, results) => {
        if (err) 
            return res.status(500).send(err);
        res.json(results);
    });
});

app.post('/add_user_mysql_node', (req, res) => {
    const username = req.body.user;
    if (username) {
        db.query("INSERT INTO users (username) VALUES (?)", [username], (err) => {
            if (err) return res.status(500).send(err);
            res.send("User added to MySQL");
        });
    } else {
        res.status(400).send("Empty username");
    }
});



app.listen(port, () => {
    console.log(`Node server running at http://localhost:${port}`);
});


