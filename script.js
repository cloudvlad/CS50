var blocked = false;
var sections = document.getElementsByClassName("section");
var buttons = sections[0].getElementsByTagName("button");
var msg1 = sections[0].getElementsByTagName("h4")[0];
msg1.style.visibility = "hidden";

for (var i = 0; i < buttons.length; i++)
{
    buttons[i].addEventListener("click", function(){
        button_click(this)}, false);
    console.log(i);
}

function button_click(el)
{
    if (blocked == true)
    {
        return;
    }

    if (el.innerHTML == "China")
    {
        blocked = true;
        el.style.border = "3px solid #00FF00";
        msg1.style.visibility = 'visible';
        msg1.innerHTML = "Correct!";
        msg1.style.color = "#00FF00";
        return;
    }

    blocked = true;
    msg1.style.visibility = 'visible';
    msg1.innerHTML = "Incorrect!";
    msg1.style.color = "#FF0000";
    for (var i = 0; i < buttons.length; i++)
    {
       if (buttons[i].innerHTML != "China")
       {
           buttons[i].style.border = "3px solid #FF0000";
       }
       else
       {
           buttons[i].style.border = "3px solid #00FF00";
       }
    }
}

var user_answer = document.getElementById("user-answer");
var msg2 = sections[1].getElementsByTagName("h4")[0];
var blocked2 = false;


function check_answer()
{
    if (blocked2 == true)
    {
        return;
    }


    if ((user_answer.value) == "Jane Austen")
    {
        blocked2 = true;
        user_answer.style.border = "3px solid #00FF00";
        msg2.style.visibility = 'visible';
        msg2.innerHTML = "Correct!";
        msg2.style.color = "#00FF00";
        user_answer.disabled = true;
        return;
    }

    msg2.style.visibility = 'visible';
    msg2.innerHTML = "Incorrect!";
    msg2.style.color = "#FF0000";
    user_answer.style.border = "3px solid #FF0000";

    return;
}

