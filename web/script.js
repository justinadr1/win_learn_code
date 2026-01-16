
let x = 0;
let i = 0;
function clicked() {
    const colors = ["red", "green", "blue", "yellow", "black"]
    if (i == 5) {
        i = 0;
    }
    const el = document.getElementById("clicked");
    el.style.color = colors[i];
    document.getElementById("clicked").textContent = ++x;
    console.log(i++);
}

function mysteryButton() {
    window.alert("hello world");
    window.setTimeout(() =>
        {
            const el = document.getElementById("clicked").textContent = "mystery text";
            console.log("faahhh");
        }, 
        2000 // milliseconds
    );
    console.log("Viewport width", window.innerWidth);
    
}

function goToWiki() {
    window.location.href = "https://wikipedia.com";

}

function epicButton() {
    window.alert("epic alert");
    
}