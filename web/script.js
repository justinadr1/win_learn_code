function printUsers()
{
    fetch('http://127.0.0.1/users.txt?v=3')
        .then(response => {
            return response.text();
        })
        .then(data => {
            const display = document.getElementById('user-display');
            display.innerText = data; 
            console.log("scriptjs: User data injected successfully");
        })
        .catch(error => {
            console.error('Error:', error);
            document.getElementById('user-display').innerText = "Failed to load users.";
        });
}

function addUserPHP() {
    const input = document.getElementById('user-input-php');
    const name = input.value;

    const params = new URLSearchParams();
    params.append('user', name);

    fetch('add_user_php.php', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded',
        },
        body: params
    })
    .then(response =>
        response.text()
    )
    .then(data => {
        console.log("PHP response:", data);
        input.value = '';
        printUsers();
    })
    .catch(error =>
        console.error('Error:', error)
    );
}

function addUserNode() {
    const input = document.getElementById('user-input-node');
    const name = input.value;

    const params = new URLSearchParams();
    params.append('user', name);

    fetch('http://127.0.0.1:3000/add_user_node', {
        method: 'POST',
        body: params
    })
    .then(response => response.text())
    .then(data => {
        console.log("Node response:", data);
        input.value = '';
        printUsers();
    })
    .catch(error => console.error('Error:', error));
}



function printUsersMySQLNode() {
    fetch('http://127.0.0.1:3000/get_users_mysql_node')
        .then(response => 
            response.json()
        )
        .then(data => {
            const display = document.getElementById('user-display-mysql');
            
            display.innerText = data.map(u => u.username).join('\n'); 
            
            console.log("Fetched directly from MySQL");
        })
        .catch(error => console.error('Error:', error));
}

function printUsersMySQLPHP() {
    fetch('print_users_mysql_php.php')
        .then(response => {
            return response.json(); 
        })
        .then(data => {
            const display = document.getElementById('user-display-mysql');
            display.innerText = data.map(u => u.username).join('\n'); 
            console.log("Fetched from MySQL via PHP");
        })
        .catch(error => {
            console.error('Error:', error);
            document.getElementById('user-display-mysql').innerText = "Failed to load PHP users.";
        });
}

function addUserMySQLNode() {
    const input = document.getElementById('user-input-mysql-node');
    const name = input.value;

    fetch('http://127.0.0.1:3000/add_user_mysql_node', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ user: name })
    })
    .then(response => response.text())
    .then(data => {
        console.log(data);
        input.value = '';
        printUsersMySQLNode();
    })
    .catch(error => console.error('Error:', error));
}