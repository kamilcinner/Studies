// User class definition.
class User{
    constructor(email="", login="user", password="pass") {
        this.email = email
        this.login = login
        this.password = password
    }

    show() {
        return `User data - login: ${this.login}, email: ${this.email}`
    }

    static registrationForm() {
        // Returns registration form html.
        return '<p>' +
                   '<label for="email">Email:</label>' +
                   '<input id="email" type="email">' +
               '</p>' +
               '<p>' +
                   '<label for="login">Login:</label>' +
                   '<input id="login">' +
               '</p>' +
               '<p>' +
                   '<label for="password">Password:</label>' +
                   '<input id="password" type="password">' +
               '</p>' +
               '<button id="register-btn">Register</button>'
    }
}

document.addEventListener('DOMContentLoaded', () => {
    // Clear local storage.
    localStorage.clear()

    const user = new User()
    console.log(user)

    // Show form to user.
    document.getElementById('form').innerHTML = User.registrationForm()

    // Add register button functionality.
    document.getElementById('register-btn').addEventListener('click', () => {
        // Get user input.
        const email = document.getElementById('email').value
        const login = document.getElementById('login').value
        const password = document.getElementById('password').value

        document.getElementById('info').innerHTML = ''

        // Check if login already exist in local storage.
        if (localStorage.getItem(login)) {
            // User already exist.

            // Show proper information.
            document.getElementById('info').innerHTML =
                '<h2>User with given login already exist!</h2>'

            // End function.
            return
        }

        // Check if email is already taken by other user.
        for (let i = 0; i < localStorage.length; i++) {
            if (JSON.parse(localStorage.getItem(localStorage.key(i))).email === email) {
                // Email is already taken.

                // Show proper information.
                document.getElementById('info').innerHTML =
                    '<h2>User with given email already exist!</h2>'

                // End function.
                return
            }
        }

        // Set values to earlier created user.
        user.email = email
        user.login = login
        user.password = password

        // Save user to local storage.
        localStorage.setItem(login, JSON.stringify(user))
    })
})
