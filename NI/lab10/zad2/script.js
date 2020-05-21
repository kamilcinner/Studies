class Color {
    rgbValue
    name

    constructor(rgbValue, name) {
        this.rgbValue = rgbValue
        this.name = name
    }
}

function saveOne() {
    // Get data from user input.
    const rgbValue = document.getElementById('rgb-value').value
    const name = document.getElementById('name').value

    // Save values to helper class.
    const color = new Color(rgbValue, name)

    // Get colors that have already been saved to local storage.
    let colorList = JSON.parse(localStorage.getItem('color-list'))
    // If there was no any color in the local storage then initialize the list.
    if (colorList === null) colorList = []

    // Add new Color to the list.
    colorList.push(color)
    // Update the list in the local storage.
    localStorage.setItem('color-list', JSON.stringify(colorList))
}

function showAll() {
    // Get colors form local storage.
    const colorList = JSON.parse(localStorage.getItem('color-list'))
    // Check if color list is initialized and if not then don't show
    // anything, clear display and just return.
    if (colorList === null) {
        document.getElementById('data-display').innerHTML = ''
        return
    }

    // Create hook to display data.
    const dataDisplay = document.getElementById('data-display')

    let colorParagraphs = ''

    for (const color of colorList) {
        colorParagraphs +=
            '<p style="background-color: #' + color.rgbValue + '">' +
                color.rgbValue + ' - ' + color.name +
            '</p>'
    }

    dataDisplay.innerHTML = colorParagraphs
}

function clearAll() {
    // Delete all objects form local storage.
    localStorage.clear()
    // Clear display.
    document.getElementById('data-display').innerHTML = ''
}

function addRGBColors() {
    // Clear local storage to prevent duplicates.
    clearAll()

    // Initialize list of colors.
    let colorList = []
    // Initialize list of RGB color values.
    const rgbValues = ['FF0000', '00FF00', '0000FF']
    // Initialize list of color names.
    const names = ['Red', 'Green', 'Blue']
    // Add Color objects to color list.
    for (let i = 0; i < 3; i++) {
        colorList.push(new Color(rgbValues[i], names[i]))
    }
    // Save color list to the local storage.
    localStorage.setItem('color-list', JSON.stringify(colorList))
}

function addListenersAndColors() {
    document.getElementById('save-one').addEventListener('click', saveOne)
    document.getElementById('show-all').addEventListener('click', showAll)
    document.getElementById('clear-all').addEventListener('click', clearAll)

    addRGBColors()
}

document.addEventListener('DOMContentLoaded', addListenersAndColors)
