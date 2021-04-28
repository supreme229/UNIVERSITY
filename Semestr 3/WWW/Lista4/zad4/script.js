var id = 0;
var idToDelete;

$(function () {
    var dialog, form,
        name = $("#name"),
        surname = $("#surname"),
        city = $("#city"),
        postCode = $("#post-code"),
        dateOfBirth = $("#date-of-birth")
    allFields = $([]).add(name).add(surname).add(city).add(postCode).add(dateOfBirth),
        tips = $(".validateTips");

    function updateTips(t) {
        tips
            .text(t)
            .addClass("ui-state-highlight");
        setTimeout(function () {
            tips.removeClass("ui-state-highlight", 1500);
        }, 500);
    }

    function checkRegexp(o, regexp, n) {
        if (!(regexp.test(o.val()))) {
            o.addClass("ui-state-error");
            updateTips(n);
            return false;
        } else {
            return true;
        }
    }

    function checkIfFieldEmpty(o, n) {
        if (o.val().length < 1) {
            o.addClass("ui-state-error");
            updateTips(n);
            return false;
        }
        return true;
    }

    function addUser() {
        var valid = true;
        allFields.removeClass("ui-state-error");

        valid = valid && checkIfFieldEmpty(name, "Write your name!");
        valid = valid && checkIfFieldEmpty(surname, "Write your surname!");
        valid = valid && checkIfFieldEmpty(city, "Write name of city you live in!");
        valid = valid && checkIfFieldEmpty(postCode, "Write your city post code!");
        valid = valid && checkIfFieldEmpty(dateOfBirth, "Write your date of birth!");
        valid = valid && checkRegexp(postCode, /^[0-9]{2}-[0-9]{3}$/, "Post code should be in format: xx-xxx!");

        if (valid) {
            $("#users tbody").append("<tr>" +
                "<td>" + name.val() + "</td>" +
                "<td>" + surname.val() + "</td>" +
                "<td>" + city.val() + "</td>" +
                "<td>" + postCode.val() + "</td>" +
                "<td>" + dateOfBirth.val() + "</td>" +
                "<td>" + "<a id=\"" + id.toString() + "\">Delete</a>" + "</td>" +
                "</tr>");
            dialog.dialog("close");
            dialogDeleteCreate();
            id++;
        }
        return valid;
    }

    dateOfBirth.datepicker();
    dateOfBirth.datepicker("option", "dateFormat", "dd-mm-yy")

    dialog = $("#dialog-form").dialog({
        autoOpen: false,
        height: 400,
        width: 350,
        modal: true,
        buttons: {
            "Create an account": addUser,
            Cancel: function () {
                dialog.dialog("close");
            }
        },
        close: function () {
            form[0].reset();
            allFields.removeClass("ui-state-error");
        }
    });

    form = dialog.find("form").on("submit", function (event) {
        event.preventDefault();
        addUser();
    });

    $("#create-user").button().on("click", function () {
        dialog.dialog("open");
    });

    var dialog2 = $("#dialog-delete-confirmation").dialog({
        autoOpen: false,
        height: 400,
        width: 350,
        modal: true,
        buttons: {
            "Delete user": function () {
                dialog2.dialog("close");
                $("#" + idToDelete).parent().parent().remove();
            },
            Cancel: function () {
                dialog2.dialog("close");
            }
        }
    });

    $("#users").on("click", "a", function (event) {
        event.preventDefault();
        idToDelete = $(this).attr('id');
        dialog2.dialog("open");
    });
});