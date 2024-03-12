// wykonanie ruchu - wcisniecie guzika

// import { rvs } from "./reversi.js"; //nie dziala - 404 not found - dlaczego?
// let a = new rvs();

var player = 0;
function MakeMove(button) {
    // a.move(player, button.name); // import do naprawienia
    if (player % 2 == 0) {
        if (button.innerHTML != "X") {
            button.innerHTML = "O";
            button.style.color = 'white';
        }
        else return;
    }
    else {
        if (button.innerHTML != "O")
            button.innerHTML = "X";
        else return;
    }
    player = (player + 1) % 2;
}