function highlightText() {
    clearText();
    var textToSearch = $("input[name=searchphrase]").val();
    if (textToSearch != " " && textToSearch.length >= 3) {
        $('#items').children().each(function () {
            $(this).css("background-color", "gray")
        });
        $('#items').children().each(function () {
            $(this).html($(this).html().replace(textToSearch, pattern =>
                $("<span>").addClass("highlight").html(pattern)[0].outerHTML
            ))
        })
    } else {
        $('#items').children().each(function () {
            $(this).css("background-color", "white")
        });
    }
}

function clearText() {
    $('.highlight').replaceWith(function () {
        return $(this).html();
    })
}

$("input[name=searchphrase]").on('input', highlightText);