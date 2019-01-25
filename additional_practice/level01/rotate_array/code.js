/**
 * @param {number[]} nums
 * @param {number} k
 * @return {void} Do not return anything, modify nums in-place instead.
 */
function rotate(nums, k) {
  const tmp = nums.map(n => n)
  tmp.forEach((n, i) => {
    nums[(i + k) % tmp.length] = n
  })
}