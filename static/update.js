update_buttons = document.getElementsByClassName("update-button")
update_form = document.getElementById("update-form");

id_field = document.getElementById("updated-id");

function updateBirthday(bd)
{
    id_field.value = bd.value;
    update_form.style.visibility = "visible";
}


for (var i = 0, size = update_buttons.length; i < size; i++)
{
    update_buttons[i].addEventListener("click", function() { updateBirthday(this); }, true);
}



