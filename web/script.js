function printUsers()
{
    fetch('http://127.0.0.1/users.txt')
        .then(response => {
            if (!response.ok) 
                throw new Error("Could not fetch file");
            return response.text();
        })
        .then(data => {
            const display = document.getElementById('user-display');
            display.innerText = data; 
            console.log("User data injected successfully");
        })
        .catch(error => {
            console.error('Error:', error);
            document.getElementById('user-display').innerText = "Failed to load users.";
        });
}  