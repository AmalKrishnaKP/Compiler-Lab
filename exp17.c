/*
Excellent question 🔥 —
Let’s go step-by-step to understand **`sscanf`**, **`sprintf`**, and then deeply break down **`printeclose()`** with a clear example.

---

## 🧩 1. Understanding `sscanf()`

### Syntax:

```c
int sscanf(const char *str, const char *format, ...);
```

👉 It works **just like `scanf()`**, but instead of reading from the **keyboard**,
it reads from a **string**.

---

### Example:

```c
char s[] = "q12";
int n;
sscanf(s, "q%d", &n);
printf("%d", n);
```

**Output:**

```
12
```

🧠 Explanation:

* `"q%d"` means: look for a letter `q` followed by a number.
* It reads the number after `q` (i.e., `12`) and stores it in `n`.

---

### In your program:

```c
sscanf(transition, "q%d", &i);
```

If `transition` is `"q0#q1"`, this extracts the **left state number** → `i = 0`.

---

## 🧩 2. Understanding `sprintf()`

### Syntax:

```c
int sprintf(char *str, const char *format, ...);
```

👉 It’s like `printf()`, but instead of printing to the screen,
it **writes the formatted text into a string**.

---

### Example:

```c
char s[20];
sprintf(s, "q%d,", 3);
printf("%s", s);
```

**Output:**

```
q3,
```

🧠 Explanation:

* `"q%d,"` formats the integer `3` as `"q3,"` and stores it in `s`.
* `printf()` just displays it later.

---

### In your program:

```c
sprintf(tempstr, "q%d,", j);
```

→ Converts a state number `j` into a string like `"q0,"` or `"q1,"`
and stores it in `tempstr`.

Then:

```c
strcat(outstr, tempstr);
```

→ Adds this text to `outstr` (so the full closure list is built up).

---

## 🧩 3. Now, let’s fully explain `printeclose()`

Here’s the function again:

```c
void printeclose()
{
    for(int i = 0; i < numstates; i++)
    {
        bool visited[MAX] = {false};
        char outstr[MAX] = {'\0'}, tempstr[MAX] = {'\0'};
        findeclose(i, visited);

        printf("ε-closure(q%d)={", i);
        for(int j = 0; j < numstates; j++)
        {
            if(visited[j])
            {
                sprintf(tempstr, "q%d,", j);
                strcat(outstr, tempstr);
            }
        }
        outstr[strlen(outstr)-1] = '\0'; // remove last comma
        printf("%s}\n", outstr);
    }
}
```

Let’s decode it carefully 👇

---

### 🔹 Step 1: Loop through all states

```c
for(int i = 0; i < numstates; i++)
```

→ For every state (`q0`, `q1`, …), compute and print its ε-closure.

---

### 🔹 Step 2: Initialize helper arrays

```c
bool visited[MAX] = {false};
char outstr[MAX] = {'\0'}, tempstr[MAX] = {'\0'};
```

* `visited[]`: Keeps track of which states are reachable (marked as true by `findeclose()`).
* `outstr[]`: Final string to print (like `"q0,q1,q2"`).
* `tempstr[]`: Temporary string to hold one state name at a time (like `"q1,"`).

---

### 🔹 Step 3: Find ε-closure

```c
findeclose(i, visited);
```

This recursively fills the `visited[]` array.
For example, if `ε-closure(q0) = {q0, q1, q2}`,
then after this call:

```
visited = [true, true, true, false, ...]
```

---

### 🔹 Step 4: Build the output string

```c
for(int j = 0; j < numstates; j++)
{
    if(visited[j])
    {
        sprintf(tempstr, "q%d,", j);
        strcat(outstr, tempstr);
    }
}
```

What happens here:

* For each visited state (like `q0`, `q1`, `q2`):

  * Format `"q%d,"` (for example, `"q1,"`)
  * Append it to `outstr`

After the loop,
`outstr` might look like:

```
"q0,q1,q2,"
```

---

### 🔹 Step 5: Clean the trailing comma

```c
outstr[strlen(outstr) - 1] = '\0';
```

This removes the **last comma** so it becomes:

```
"q0,q1,q2"
```

---

### 🔹 Step 6: Print the final closure

```c
printf("%s}\n", outstr);
```

Prints:

```
ε-closure(q0)={q0,q1,q2}
```

---

## 🧠 Example in Action

Let’s say we have 3 states and these ε-transitions:

```
q0#q1
q1#q2
```

When program runs:

| State | Recursive Reachable States (visited[]) | Output                   |
| ----- | -------------------------------------- | ------------------------ |
| q0    | q0 → q1 → q2                           | ε-closure(q0)={q0,q1,q2} |
| q1    | q1 → q2                                | ε-closure(q1)={q1,q2}    |
| q2    | q2 only                                | ε-closure(q2)={q2}       |

---

## 🧭 Summary

| Function        | Meaning                                                                                                               |
| --------------- | --------------------------------------------------------------------------------------------------------------------- |
| `sscanf()`      | Reads **formatted data** from a string (used to extract numbers like q0 → 0).                                         |
| `sprintf()`     | Writes **formatted data into a string** (used to make "q0," text).                                                    |
| `printeclose()` | For each state, recursively finds all states reachable through ε-transitions and prints them in `{q0,q1,...}` format. |

---

Would you like me to draw a **visual flowchart** of how `findeclose()` and `printeclose()` work together (with arrows showing recursion and visited states)? It would make recursion much easier to grasp.


rogram to convert NFA with ε transition to NFA without ε transition
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 20
#define MAX_SYMBOLS 20

int n, m;                          // number of states, number of symbols
char symbols[MAX_SYMBOLS];         // input symbols
int transition[MAX_STATES][MAX_SYMBOLS][MAX_STATES];
int epsilon[MAX_STATES][MAX_STATES]; // epsilon transitions
int epsilonClosure[MAX_STATES][MAX_STATES];
int closureCount[MAX_STATES];

// Function to add element to closure
void addToClosure(int state, int s) {
    if (!epsilonClosure[state][s]) {
        epsilonClosure[state][s] = 1;
        closureCount[state]++;
        for (int t = 0; t < n; t++) {
            if (epsilon[s][t]) {
                addToClosure(state, t);
            }
        }
    }
}

// Compute epsilon closure for all states
void computeEpsilonClosures() {
    for (int i = 0; i < n; i++) {
        memset(epsilonClosure[i], 0, sizeof(epsilonClosure[i]));
        closureCount[i] = 0;
        addToClosure(i, i);
    }
}

int main() {
    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols: (other than epsilon) ");
    scanf("%d", &m);

    printf("Enter input symbols  (epsilon transitions are entered seperately):\n");
    for (int i = 0; i < m; i++) {
        scanf(" %c", &symbols[i]);
    }

    // Initialize transitions
    memset(transition, 0, sizeof(transition));
    memset(epsilon, 0, sizeof(epsilon));

    int num;
    printf("\nEnter transition table (for each state and symbol):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("\nFrom state q%d with symbol %c, number of next states: ", i, symbols[j]);
            scanf("%d", &num);
            if(num)
                printf("\nEnter next states: (only state numbers, q not needed)");
            for (int k = 0; k < num; k++) {
                int s;
                scanf("%d", &s);
                transition[i][j][s] = 1;
            }
        }
    }

    printf("\nEnter epsilon transitions (state -> state, -1 -1 to stop):\n");
    while (1) {
        int a, b;
        scanf("%d %d", &a, &b);
        if (a == -1 && b == -1) break;
        epsilon[a][b] = 1;
    }

    // Compute epsilon closures
    computeEpsilonClosures();

    // Build new transition table without epsilon
    printf("\nEquivalent NFA without epsilon moves:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int result[MAX_STATES] = {0};

            // For every state in epsilon-closure of i
            for (int k = 0; k < n; k++) {
                if (epsilonClosure[i][k]) {
                    // Follow symbol transition
                    for (int l = 0; l < n; l++) {
                        if (transition[k][j][l]) {
                            // Add epsilon closure of l
                            for (int p = 0; p < n; p++) {
                                if (epsilonClosure[l][p]) {
                                    result[p] = 1;
                                }
                            }
                        }
                    }
                }
            }
            printf("From state q%d with symbol %c -> { ", i, symbols[j]);
            for (int x = 0; x < n; x++) {
                if (result[x]) printf("q%d ", x);
            }
            printf("}\n");
        }
    }

    return 0;
}
