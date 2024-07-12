
let steps = [];
let arraySize = 10;
let interval;

function loadSteps(file) {
    fetch(file)
        .then(response => response.text())
        .then(data => {
            steps = data.trim().split('\n').map(line => line.split(',').map(Number));
            startAnimation();
        });
}

function startSorting(algorithm) {
    let file;
    if (algorithm === 'bubbleSort') {
        file = 'bubble_steps.txt';
    } else if (algorithm === 'selectionSort') {
        file = 'selection_steps.txt';
    } else if (algorithm === 'insertionSort') {
        file = 'insertion_steps.txt';
    }
    loadSteps(file);
}

function startAnimation() {
    let stepIndex = 0;
    interval = setInterval(() => {
        if (stepIndex >= steps.length) {
            clearInterval(interval);
            return;
        }
        displayArray(steps[stepIndex]);
        stepIndex++;
    }, 500);
}

function displayArray(array) {
    const container = document.getElementById('array-container');
    container.innerHTML = '';
    for (let i = 0; i < array.length; i++) {
        const bar = document.createElement('div');
        bar.style.height = array[i] * 10 + 'px';
        bar.className = 'bar';
        container.appendChild(bar);
    }
}

function resetArray() {
    clearInterval(interval);
    displayArray([5, 3, 8, 4, 2, 7, 1, 10, 6, 9]);
}
