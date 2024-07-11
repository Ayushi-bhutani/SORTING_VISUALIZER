let steps = [];
let arraySize = 10;
let interval;

function loadSteps(algorithm) {
    fetch(`steps_${algorithm}.txt`)
        .then(response => response.text())
        .then(data => {
            steps = data.trim().split('\n').map(line => line.split(',').map(Number));
            startAnimation();
        });
}

function startSorting(algorithm) {
    fetch(`http://localhost:3000/sort?algorithm=${algorithm}`)
        .then(() => loadSteps(algorithm));
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
        bar.style.height = `${array[i]}px`;
        bar.style.width = '20px';
        bar.classList.add('array-bar');
        container.appendChild(bar);
    }
}

function resetArray() {
    generateArray();
}

function generateArray() {
    fetch('steps_reset.txt')
        .then(response => response.text())
        .then(data => {
            const array = data.trim().split(',').map(Number);
            displayArray(array);
        });
}

generateArray();
