## Recursive thinking: types of recursive functions

* Structural
  * Params are incldec or fixed 
* Accumulative
  * Params are incldec, fixed, or collections
* Generative
  * Parameters are not constrained, structure follows the problem itself

## Memoization with recursion (caching identical function calls)

```
int init(int n) {
  int F[MAX_SIZE];
  F[0] = 0;
  F[1] = 1;
  for (int i = 2; i <= n; i++) {
    F[i] = 1;
  }
  return fib(n);
}

int fib(int n) {
  if (F[n] == 1) {
    F[n] = F[n-2] + F[n-1];
  }
  return F[n];
}
```
