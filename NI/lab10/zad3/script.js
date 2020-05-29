class Product {
    name
    price
    color
    amount

    constructor(name, price, color, amount) {
        this.name = name
        this.price = price
        this.color = color
        this.amount = amount
    }
}

function saveOne() {
    // Get data from user input.
    const name = document.getElementById('name').value
    const price = document.getElementById('price').value
    const color = document.getElementById('color').value
    const amount = document.getElementById('amount').value

    // Save values to helper class.
    const product = new Product(name, price, color, amount)

    // Get colors that have already been saved to local storage.
    let productList = JSON.parse(localStorage.getItem('product-list'))
    // If there was no any color in the local storage then initialize the list.
    if (productList === null) productList = []

    // Add or update Product.
    let updated = false
    // Check if the products already exist.
    for (const prod of productList) {
        if (prod.name === name) {
            const index = productList.indexOf(prod)

            if (index !== -1) {
                productList[index] = product
                updated = true
            }

            break
        }
    }

    // If there is no product to update then save new product.
    if (!updated) productList.push(product)

    // Update the list in the local storage.
    localStorage.setItem('product-list', JSON.stringify(productList))

    // Reshow all products.
    showAll()
}

function editOne(clickedProductName) {
    // Get hooks.
    const name = document.getElementById('name')
    const price = document.getElementById('price')
    const color = document.getElementById('color')
    const amount = document.getElementById('amount')

    const productList = JSON.parse(localStorage.getItem('product-list'))
    for (const product of productList) {
        if (product.name === clickedProductName) {
            const index = productList.indexOf(product)

            if (index !== -1) {
                const prod = productList[index]
                name.value = prod.name
                price.value = prod.price
                color.value = prod.color
                amount.value = prod.amount
            }

            break
        }
    }
}

function deleteOne(clickedProductName) {
    const productList = JSON.parse(localStorage.getItem('product-list'))
    for (const product of productList) {
        if (product.name === clickedProductName) {
            const index = productList.indexOf(product)

            if (index !== -1) {
                productList.splice(index, 1)
            }

            break
        }
    }

    // Update the list in the local storage.
    localStorage.setItem('product-list', JSON.stringify(productList))

    // Reshow all products.
    showAll()
}

function showAll() {
    // Get products form local storage.
    const productList = JSON.parse(localStorage.getItem('product-list'))
    // Check if product list is initialized and if not then don't show
    // anything, clear display and just return.
    if (productList === null) {
        document.getElementById('data-display').innerHTML = ''
        return
    }

    // Create hook to display data.
    const dataDisplay = document.getElementById('data-display')

    // Initialize variable for storing data-display div content.
    let productDivs = ''
    // Add products.
    for (const product of productList) {
        productDivs +=
            '<div class="product"' +
                '<p><strong>Product name:</strong> '+product.name+'</p>' +
                '<p>Price: '+product.price+'</p>' +
                '<p>Color: '+product.color+'</p>' +
                '<p>Number of items: '+product.amount+'</p>' +
                `<button onclick="editOne(\'${product.name}\')">Edit</button>` +
                `<button onclick="deleteOne(\'${product.name}\')">Delete</button>` +
            '</div>'
}

    // Save proper div content.
    dataDisplay.innerHTML = productDivs
}

function clearAll() {
    // Delete all objects form local storage.
    localStorage.clear()
    // Clear display.
    document.getElementById('data-display').innerHTML = ''
}

document.addEventListener('DOMContentLoaded', () => {
    // Add buttons click listeners.
    document.getElementById('save-one').addEventListener('click', saveOne)
    document.getElementById('show-all').addEventListener('click', showAll)
    document.getElementById('delete-all').addEventListener('click', clearAll)
})
