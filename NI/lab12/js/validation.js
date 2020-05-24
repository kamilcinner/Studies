function checkFieldByRegExp(id, regexp) {
    const fieldValue = document.getElementById(id).value
    return regexp.test(fieldValue)
}

function checkRadio(name){
    const radio = document.getElementsByName(name)
    
    for (let i = 0; i < radio.length; i++) {
        if (radio[i].checked) return true
    }
    
    return false
}

function validate() {
    // Assume that everything is ok at first.
    let ok = true

    // Initialize regular expressions for text fields.
    let surnameRegExp = /^[a-zA-Z]{2,20}$/
    let ageRegExp = /^[1-9][0-9]{1,2}$/
    let emailRegExp = /^([a-zA-Z0-9])+([.a-zA-Z0-9_-])*@([a-zA-Z0-9_-])+(.[a-zA-Z0-9_-]+)+/

    // Check lastname.
    const lastnameError = document.getElementById("lastname-error")
    if (!checkFieldByRegExp('id_lastname', surnameRegExp)) {
        ok = false
        // Show error.
        lastnameError.innerHTML = 'Surname is invalid!'
    } else {
        // Clean error.
        lastnameError.innerHTML = ''
    }

    // Check age.
    const ageError = document.getElementById('age-error')
    if (!checkFieldByRegExp('id_age', ageRegExp)) {
        ok = false
        // Show error.
        ageError.innerHTML = 'Age is invalid!'
    } else {
        // Clean error.
        ageError.innerHTML = ''
    }

    // Check country.
    // TODO: how to check country?
    
    // Check email.
    const emailError = document.getElementById('email-error')
    if (!checkFieldByRegExp('id_email', emailRegExp)) {
        ok = false
        // Show error.
        emailError.innerHTML = 'Email is invalid!'
    } else {
        // Clean error.
        emailError.innerHTML = ''
    }

    // Check checkbox.
    const languageError = document.getElementById('language-error')
    let atLeastOneChecked = false
    const languageCheckboxes = document.getElementsByName('language')
    for (const checkbox of languageCheckboxes) {
        if (checkbox.checked) {
            atLeastOneChecked = true
            break
        }
    }
    if (!atLeastOneChecked) {
        ok = false
        // Show error.
        languageError.innerHTML = 'Check at least one programming language :)'
    } else {
        // Clean error.
        languageError.innerHTML = ''
    }

    // Check radio.
    const paymentError = document.getElementById('payment-error')
    if (!checkRadio('payment')) {
        ok = false
        // Show error.
        paymentError.innerHTML = 'Check payment option :)'
    } else {
        // Clean error.
        paymentError.innerHTML = ''
    }

    // Show confirmation dialog if user input is correct.
    if (ok) {
        const lastname = document.getElementById('id_lastname').value
        const age = document.getElementById('id_age').value
        const country = document.getElementById('id_country').value
        const email = document.getElementById('id_email').value

        const formData =
            `User input data:
             Lastname: ${lastname}
             Age: ${age}
             Country: ${country}
             Email: ${email}
             Languages: ${getCheckedCheckboxesValues()}
             Payment: ${getRadioValue()}
            `

        if (!confirm(formData)) {
            return false
        }
    }

    // Return the result of validation.
    return ok
}

function getCheckedCheckboxesValues() {
    const checkboxes = document.getElementsByName('language')
    let values = ''
    for (const checkbox of checkboxes) {
        if (checkbox.checked) {
            values += checkbox.value + ' '
        }
    }
    return values
}

function getRadioValue() {
    const radios = document.getElementsByName('payment')
    for (const radio of radios) {
        if (radio.checked) {
            return radio.value
        }
    }
}
