#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <vector>

void buildPermutations(const std::vector<int>& nums, std::vector<bool>& used, std::vector<int>& path,
                       std::vector<std::vector<int>>& results) {
    if (path.size() == nums.size()) {
        results.push_back(path);
        return;
    }
    for (std::size_t index = 0; index < nums.size(); ++index) {
        if (used[index]) continue;
        used[index] = true;
        path.push_back(nums[index]);
        buildPermutations(nums, used, path, results);
        path.pop_back();
        used[index] = false;
    }
}

std::vector<std::vector<int>> permutations(const std::vector<int>& nums) {
    std::vector<std::vector<int>> results;
    std::vector<bool> used(nums.size(), false);
    std::vector<int> path;
    buildPermutations(nums, used, path, results);
    return results;
}

void buildSubsets(const std::vector<int>& nums, std::size_t start, std::vector<int>& path,
                  std::vector<std::vector<int>>& results) {
    results.push_back(path);
    for (std::size_t index = start; index < nums.size(); ++index) {
        path.push_back(nums[index]);
        buildSubsets(nums, index + 1, path, results);
        path.pop_back();
    }
}

std::vector<std::vector<int>> subsets(const std::vector<int>& nums) {
    std::vector<std::vector<int>> results;
    std::vector<int> path;
    buildSubsets(nums, 0, path, results);
    return results;
}

bool isSafe(std::size_t row, std::size_t column, const std::vector<std::size_t>& placed) {
    for (std::size_t previousRow = 0; previousRow < placed.size(); ++previousRow) {
        std::size_t previousColumn = placed[previousRow];
        std::size_t rowGap = row > previousRow ? row - previousRow : previousRow - row;
        std::size_t columnGap = column > previousColumn ? column - previousColumn : previousColumn - column;
        if (previousColumn == column || rowGap == columnGap) return false;
    }
    return true;
}

std::size_t placeQueens(std::size_t n, std::vector<std::size_t>& placed) {
    std::size_t row = placed.size();
    if (row == n) return 1;
    std::size_t total = 0;
    for (std::size_t column = 0; column < n; ++column) {
        if (isSafe(row, column, placed)) {
            placed.push_back(column);
            total += placeQueens(n, placed);
            placed.pop_back();
        }
    }
    return total;
}

std::size_t nQueensCount(std::size_t n) {
    std::vector<std::size_t> placed;
    return placeQueens(n, placed);
}

int main() {
    auto perms = permutations({1, 2, 3});
    assert(perms.size() == 6);
    assert(perms.front() == (std::vector<int>{1, 2, 3}));
    assert(perms.back() == (std::vector<int>{3, 2, 1}));
    assert(subsets({1, 2, 3}).size() == 8);
    assert(nQueensCount(4) == 2);
    assert(nQueensCount(8) == 92);
    std::cout << "cpp: all checks passed\n";
    return 0;
}
