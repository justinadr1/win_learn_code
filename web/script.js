
let x = 0;
function clicked() {
    const colors = ["red", "green", "blue", "yellow", "black"]
    const el = document.getElementById("grade");
    el.style.color = colors[x];
    
    document.getElementById("clicked").textContent = x++;
}