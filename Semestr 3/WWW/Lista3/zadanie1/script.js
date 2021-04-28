const inputAccountNumber = document.getElementById('numer_konta');
const inputEmail = document.getElementById('e-mail');
const inputPesel = document.getElementById('pesel');
const inputDate = document.getElementById('data_urodzenia');
const error = document.getElementById('blad');
const button = document.getElementById('wyslij');
error.style = "color: rgb(255, 0, 0);";

var validateRules = {};
validateRules['acc_nr'] = /^(?:[0-9]{11}|[0-9]{2}-[0-9]{3}-[0-9]{6})$/;
validateRules['email'] = /^[a-zA-Z0-9._-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,4}$/;
validateRules['pesel'] = /^[0-9]{11}$/;
var errors = {}
errors['acc_nr'] = "Błędny numer konta!";
errors['email'] = "Błędny adres E-mail!";
errors['pesel'] = "Błędny numer pesel!";
errors['date'] = "Błędna data!";
var working = {}
working['acc_nr'] = false;
working['email'] = false;
working['date'] = false;
working['pesel'] = false;
//console.log(validateRules['acc_nr'].test('24567029021'));
//console.log(validateRules[1].test('pewien.uzytkownik@onet.pl'));
//console.log(validateRules[2].test('20122862379'));

function validateRule(rule, object) {
    if (validateRules[rule].test(object.value)) {
        object.style.backgroundColor = "#66FF99";
        error.innerHTML = null;
        working[rule] = true;
    } else {
        object.style.backgroundColor = "rgb(255, 0, 0)";
        error.innerHTML = errors[rule];
        working[rule] = false;
    }
}

function validateThing(to_validate) {
    switch (to_validate) {
        case 'acc_nr':
            validateRule('acc_nr', inputAccountNumber);
            break;
        case 'email':
            validateRule('email', inputEmail);
            break;
        case 'pesel':
            validateRule('pesel', inputPesel);
            break;
        case 'date':
            if (inputDate.value != "") {
                inputDate.style.backgroundColor = "#66FF99";
                error.innerHTML = null;
                working["date"] = true;
            } else {
                inputDate.style.backgroundColor = "rgb(255, 0, 0)"
                error.innerHTML = errors['date'];
                working["date"] = false;
            }
            break;
    }
}

function eventListeners() {
    inputEmail.addEventListener('focusout', () => {
        validateThing('email')
    });
    inputAccountNumber.addEventListener('focusout', () => {
        validateThing('acc_nr')
    });
    inputPesel.addEventListener('focusout', () => {
        validateThing('pesel')
    });
    inputDate.addEventListener('focusout', () => {
        validateThing('date')
    });
    button.addEventListener('click', event => {
        if (!checkIfAlright()) {
            event.preventDefault();
        }
    });
}

function checkIfAlright() {
    if (working['acc_nr'] ==true && working['date'] ==true && working['pesel'] ==true && working['email'] ==true)
    {
        return true;
    }
    return false;
}

eventListeners();