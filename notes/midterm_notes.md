### Strings
#### Methods
- str.insert(pos, str2)
- str.remove(pos, length)
- str.substr(pos, length)
- str.empty() -> returns whether or not the string is empty
- str.find(str1)
- str.find(str1, pos) -> search starts at position pos
- str.find_first_of(str1, pos) -> index of first instance in str of any character in str1,  starting at position pos
- str.find_first_not_of(str1, pos) -> index of the first instance in str of any character not in str1

#### I/O and File Access: See [Review Digital Computation Basics - Slide 56](https://learn.uwaterloo.ca/d2l/le/content/442067/viewContent/2462791/View)

### Primitive Datatypes
```
char              1 byte
unsigned char     1 byte
signed char       1 byte
int               4 bytes
unsigned int      4 bytes
short             2 bytes
unsigned short    2 bytes
long              4 bytes
unsigned long     4 bytes
float             4 bytes
double            8 bytes
long double       10 bytes
```

### List ADT
`Constructor`
- Sequential: allocate continuous block of memory (data, capacity, size)

`void insert(T value, int pos)`
- Sequential: 

`void delete(int pos)`
- Sequential:

`T select(int pos)`
- Sequential

`void replace(int pos, T value)`
- Sequential: 

`int size()`
- Sequential: 

### Algorithmic Analysis
- Common heuristics classes: $O(1), O(log(n)), O(n), O(N log(n)), O(n^2), O(n^3), O(2^n), O(10^n), O(n!), O(n^n)$
- Big-O ($O$): Worst case runtime
- Big-Omega ($\Omega$): Lower-bound runtime
    - $f(n)$ is classified as $\Omega(g(n))$ if there exists two positive constants $K$ and $n_0$ such that $|f(n)| >= K|g(n)|$ for all $n >= n_0$
- Big-Theta ($\Theta$): Tight-bound runtime
    - $f(n)$ is classified as $\Theta(g(n))$ if there exists positive constants $K_1, K_2, n_0$ such that $|f(n)| <= K_1|g(n)|$ and $|f(n)| >= K_2|g(n)|$ for all $n >= n_0$
- Comparing function growth:
    - Compute $\lim_{n->\infty} \frac{f(n)}{g(n)}$
    - If value is $0$, then $f(n)$ grows slower than $g(n)$; that is, $f(n) = O(g(n))$
    - If value is a constant, $f(n)$ grows as fast as $g(n)$; that is, $f(n) = O(g(n))$
    - IF value is $\infty$, $f(n)$ grows faster than $g(n)$; that is, $g(n) = O(f(n))$
- Big-O from source code:
    - Express each loop as summation $\sum$
    - Segments of code repeated on each iteration, use a constant (e.g. $a$)
    - e.g.
    ```
    for i in range(n-2):
        for j in range(i+1, n-1):
            for k in range(i, n):
                pass # constant steps
    ```
    - $f(n) = \sum_{i=0}^{n-2}\sum_{j=i+1}^{n-1}\sum_{k=i}^{n}a$
    - $= a\sum_{i=0}^{n-2}\sum_{j=i+1}^{n-1}(n-i+1)$
    - $= a\sum_{i=0}^{n-2}(n-i-1)(n-i+1)$
    - $= a()(n-i-1)(n-i+1)$

### Algorithm Design
- Bottom-up: cover base case -> analyze it runs correctly -> expand to cover general cases
- Top-down: cover general case -> analyze it runs correctly -> ensure reach base case + terminates
- Divide-and-conquer: decide on # of segments and compute segment boundaries -> cover general case -> ensure reach base case + terminates
- Write test cases: boundary cases, cases where algorithm may never terminate, etc.

### Testing
- Closed-box testing: input/output behavior
    - boundary-value analysis (BVA): select test cases on or just to one side of the boundary
- Open-box testing: internal logic of module or subsystem
    - statement coverage: cases cause every line of code to be executed
    - branch coverage: cases cause every decision point to be executed
    - condition coverage: cases cause each condition option to be executed
    - path coverage: cases cause every independent code path to be executed
- Unit Testing Frameworks: provide own assertion structure and simplify:
    - Catch, Boost.Test, Google Test, CppTest, ...
