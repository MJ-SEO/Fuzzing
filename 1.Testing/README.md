# Introduction to Software Testing

[Reference Site](https://www.fuzzingbook.org/html/Intro_Testing.html)

## Exercise2: Testing Shellsort

### - Shellsort

``` python
def shellsort(elems):
    sorted_elems = elems.copy()
    gaps = [701, 301, 132, 57, 23, 10, 4, 1]
    for gap in gaps:
        for i in range(gap, len(sorted_elems)):
            temp = sorted_elems[i]
            j = i
            while j >= gap and sorted_elems[j - gap] > temp:
                sorted_elems[j] = sorted_elems[j - gap]
                j -= gap
            sorted_elems[j] = temp

    return sorted_elems
```

### Part1: Manual Test Cases

### Part2: Random Inputs


## Exercise3: Quadratic Solver

### - Quadratic_solver

``` python
def quadratic_solver(a, b, c):
    q = b * b - 4 * a * c
    solution_1 = (-b + my_sqrt_fixed(q)) / (2 * a)
    solution_2 = (-b - my_sqrt_fixed(q)) / (2 * a)
    return (solution_1, solution_2)
```

### Part1: Find bug-triggering inputs

### Part2: Fix the problem

### Part3: Odds and Ends
