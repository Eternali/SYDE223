/**
 * @param {number[]} A
 * @return {boolean}
 */
function isMonotonic(A) {
  if (A.length <= 1) return true;
  let increasing = null;
  for (let i = 0; i < A.length - 1; i++) {
    if (A[i] === A[i+1]) continue;
    if (A[i] < A[i+1]) {
      if (increasing === null) increasing = true;
      if (increasing) continue;
    }
    if (A[i] > A[i+1]) {
      if (increasing === null) increasing = false;
      if (!increasing) continue;
    }
    return false;
  }
  return true;
  // return A
  //   .slice(0, A.length-1)
  //   .map((a, i) => {
  //     if (a < A[i+1]) return -1;
  //     if (a === A[i+1]) return 0;
  //     if (a > A[i+1]) return 1;
  //     throw TypeError()
  //   })
  //   .filter(a => a !== 0)
  //   .every((a, _, arr) => a === arr[0]);
};
