// Set background to content.
$('#content').css('background-color', 'gray')

// Set weight bold to input text.
$('input').css('font-weight', 'bold')

// Change outputs background to light green by adding proper css class.
$('input[disabled]').addClass('result')

$('#calculateButton').click(function () {
    // Input.
    // const amount = document.getElementById('amount').value
    // const installmentsCount = document.getElementById('installments-count').value
    // const percent = document.getElementById('percent').value

    const amount = parseFloat($('#amount').val())
    const installmentsCount = parseFloat($('#installments-count').val())
    const percent = parseFloat($('#percent').val())

    // Check if input is NaN or Infinite.
    if (!isFinite(amount) || !isFinite(installmentsCount) || !isFinite(percent)) {
        alert('Invalid data provided!')
    } else {

        // Output hooks.
        // const monthlyInstallment = document.getElementById('monthly-installment')
        // const amountWithInterest = document.getElementById('amount-with-interest')

        const monthlyInstallment = $('#monthly-installment')
        const amountWithInterest = $('#amount-with-interest')

        // Calculations.
        const interestRatePerMonth = percent / 1200.0

        const numerator = amount * interestRatePerMonth
        const denominator = 1.0 - (1.0 / Math.pow((1.0 + interestRatePerMonth), installmentsCount))

        const result = numerator / denominator

        // monthlyInstallment.value = result / installmentsCount
        // amountWithInterest.value = result

        monthlyInstallment.val(Math.ceil((result + Number.EPSILON) * 100) / 100)
        amountWithInterest.val(Math.ceil((result * installmentsCount + Number.EPSILON) * 100) / 100)
    }
})
