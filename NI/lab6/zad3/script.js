function calculate() {
    // Input.
    const a = parseFloat(document.getElementById('a').value);
    const b = parseFloat(document.getElementById('b').value);
    const operations = document.getElementsByName('operation');

    // Check a and b inputs.
    if (isNaN(a) || isNaN(b)) { //  || isFinite(a) || isFinite(b)
        alert('Invalid data provided!');
        return;
    }

    // Output hook.
    const resultHook = document.getElementById('result');

    // Calculations.

    // Get chosen operation type.
    let currentOperation;

    for (let op of operations) {
        if (op.checked ) {
            currentOperation = op.value;
            break;
        }
    }

    let result;

    // Do calculations based on operation type.
    switch (currentOperation) {
        case '+': { result = a + b; break; }
        case '-': { result = a - b; break; }
        case '*': { result = a * b; break; }
        case '/': {
            if (Math.abs(b) < 1e-12) {
                alert("Can't divide by zero!");
                return;
            } else { result = a / b; break; }
        }
        default: {
            // There is no valid operation type on input.
            alert('Chose an operator!');
            return;
        }
    }

    // Set the output hook value.
    resultHook.value = result;
}
