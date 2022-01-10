
var blocked = [false, false, false, false, false];
var sections = document.getElementsByClassName("section");
var answers = ["Sin'dorei", "Stormwind", "Orgrimmar", "Teldrassil", "Azeroth"];

// Adding eventListener to the buttons
for (var i = 0; i < sections.length - 1; i++)
{
    sections[i].getElementsByTagName("h4")[0].style.visibility = "hidden";
    var buttons = sections[i].getElementsByTagName("button");
    for (var j = 0; j < buttons.length; j++)
    {
        buttons[j].value = i.toString(10);
        buttons[j].addEventListener("click", function(){
        button_click(this)}, false);
    }
}

function button_click(el)
{
    var num = parseInt(el.value);
    if (blocked[num] == true)
    {
        return;
    }

    var buttons = sections[num].getElementsByTagName("button");
    var msg = sections[num].getElementsByTagName("h4")[0];

    if (el.innerHTML == answers[num])
    {
        blocked[num] = true;
        el.style.border = "3px solid #00FF00";
        msg.style.visibility = 'visible';
        msg.innerHTML = "Correct!";
        msg.style.color = "#00FF00";
        return;
    }

    blocked[num] = true;
    msg.style.visibility = 'visible';
    msg.innerHTML = "Incorrect!";
    msg.style.color = "#FF0000";
    for (var i = 0; i < buttons.length; i++)
    {
       if (buttons[i].innerHTML != answers[num])
       {
           buttons[i].style.border = "3px solid #FF0000";
       }
       else
       {
           buttons[i].style.border = "3px solid #00FF00";
       }
    }
}

function check_answer(num)
{
    if (blocked[num] == true)
    {
        return;
    }

    var msg = sections[num].getElementsByTagName("h4")[0];
    var user_answer = document.getElementById("user-answer");

    if ((user_answer.value) == answers[num])
    {
        blocked[num] = true;
        user_answer.style.border = "3px solid #00FF00";
        msg.style.visibility = 'visible';
        msg.innerHTML = "Correct!";
        msg.style.color = "#00FF00";
        user_answer.disabled = true;
        return;
    }

    msg.style.visibility = 'visible';
    msg.innerHTML = "Incorrect!";
    msg.style.color = "#FF0000";
    user_answer.style.border = "3px solid #FF0000";

    return;
}

