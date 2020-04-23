function calculate(number) {
    // Input.
    const amount = document.getElementById('amount').value;
    const installmentsCount = document.getElementById('installments-count').value;
    const percent = document.getElementById('percent').value;

    // Check if input is Nan or Infinite.
    if (isNaN(amount) || isNaN(installmentsCount) || isNaN(percent) ||
            isFinite(amount) || isFinite(installmentsCount) || isFinite(percent)) {
        alert('Invalid data provided!')
    } else {

        // Output hooks.
        const monthlyInstallment = document.getElementById('monthly-installment');
        const amountWithInterest = document.getElementById('amount-with-interest');

        // Calculations.
        const interestRatePerMonth = percent / 12.0;

        const numerator = amount * interestRatePerMonth;
        const denominator = 1.0 - (1.0 / Math.pow((1.0 + interestRatePerMonth), installmentsCount));

        const result = numerator / denominator;
        alert(result);
        monthlyInstallment.value = result / installmentsCount;
        amountWithInterest.value = result;
    }
}
