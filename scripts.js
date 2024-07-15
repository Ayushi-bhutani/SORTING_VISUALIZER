let steps = [];
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
    } else if (algorithm === 'mergeSort') {
        file = 'merge_steps.txt';
    } else if (algorithm === 'quickSort') {
        file = 'quick_steps.txt';
    }
    loadSteps(file);
}

function startAnimation() {
    let stepIndex = 0;
    interval = setInterval(() => {
        if (stepIndex >= steps.length) {
            clearInterval(interval);
            // Change bars color to intense lavender after sorting completes
            const bars = document.querySelectorAll('.bar');
            bars.forEach(bar => {
                bar.style.backgroundColor = '#8A2BE2'; // Intense lavender color
            });
            return;
        }
        displayArray(steps[stepIndex]);
        stepIndex++;
    }, 500);
}

function displayArray(array) {
    const container = document.getElementById('array-container');
    container.innerHTML = '';
    const maxHeight = Math.max(...array) * 20; // Adjust multiplier for bar height
    for (let i = 0; i < array.length; i++) {
        const bar = document.createElement('div');
        bar.style.height = array[i] * 20 + 'px'; // Adjust height multiplier as needed
        bar.className = 'bar';
        bar.style.width = 'calc(100% / ' + array.length + ')';
        container.appendChild(bar);
    }
}

function resetArray() {
    clearInterval(interval);
    displayArray([5, 3, 8, 4, 2, 7, 1, 10, 6, 9]);
}

resetArray();  // Initialize the array display on page load
