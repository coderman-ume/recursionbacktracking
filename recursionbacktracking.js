const assert = require("assert");

function permutations(nums) {
  const results = [];
  const used = new Array(nums.length).fill(false);
  const path = [];

  function build() {
    if (path.length === nums.length) {
      results.push([...path]);
      return;
    }
    for (let index = 0; index < nums.length; index++) {
      if (used[index]) continue;
      used[index] = true;
      path.push(nums[index]);
      build();
      path.pop();
      used[index] = false;
    }
  }

  build();
  return results;
}

function subsets(nums) {
  const results = [];
  const path = [];

  function build(start) {
    results.push([...path]);
    for (let index = start; index < nums.length; index++) {
      path.push(nums[index]);
      build(index + 1);
      path.pop();
    }
  }

  build(0);
  return results;
}

function isSafe(row, column, placed) {
  for (let previousRow = 0; previousRow < placed.length; previousRow++) {
    const previousColumn = placed[previousRow];
    if (previousColumn === column || Math.abs(row - previousRow) === Math.abs(column - previousColumn)) {
      return false;
    }
  }
  return true;
}

function placeQueens(n, placed) {
  const row = placed.length;
  if (row === n) return 1;
  let total = 0;
  for (let column = 0; column < n; column++) {
    if (isSafe(row, column, placed)) {
      placed.push(column);
      total += placeQueens(n, placed);
      placed.pop();
    }
  }
  return total;
}

function nQueensCount(n) {
  return placeQueens(n, []);
}

function main() {
  const perms = permutations([1, 2, 3]);
  assert.strictEqual(perms.length, 6);
  assert.deepStrictEqual(perms[0], [1, 2, 3]);
  assert.deepStrictEqual(perms[5], [3, 2, 1]);
  assert.strictEqual(subsets([1, 2, 3]).length, 8);
  assert.strictEqual(nQueensCount(4), 2);
  assert.strictEqual(nQueensCount(8), 92);
  console.log("javascript: all checks passed");
}

main();
