// wykonanie ruchu - wcisniecie guzika

// import { cn4 } from "./connect4.js"; //nie dziala - 404 not found - dlaczego?
// let a = new cn4();

var player = 0;
function MakeMove(button) {
    // a.move(player, button.name); // import do naprawienia
    if (player % 2 == 0) {
        if (button.innerHTML != "X") {
            button.innerHTML = "O";
            button.style.color = 'red';
        }
        else return;
    }
    else {
        if (button.innerHTML != "O") {
            button.innerHTML = "X";
            button.style.color = 'yellow';
        }
        else return;
    }
    player = (player + 1) % 2;
}