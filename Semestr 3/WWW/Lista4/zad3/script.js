$(document).ready(function () {
    $('#pics').children().click(function () {
        if ($(this).data("marked")) {
            $(this).css("border", "")
            $(this).data("marked", false)
        } else {
            $(this).css("border", "3px solid red")
            $(this).data("marked", true)
        }
    });
});

function selectAll() {
    $('#pics').children().each(function () {
        $(this).css("border", "3px solid red")
        $(this).data("marked", true)
    });
}

function unselectAll() {
    $('#pics').children().each(function () {
        $(this).css("border", "")
        $(this).data("marked", false)
    });
}

function writeLog() {
    $('#log').html("");
    $('#pics').children().each(function () {
        if ($(this).data("marked")) {
            $('#log').append("Id: " + $(this).attr('id') + "\n")
        }
    });
}

$('#select_all').on('click', selectAll);
$('#unselect_all').on('click', unselectAll);
$('#write_log').on('click', writeLog);