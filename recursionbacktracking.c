#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#define MAX_N 16

long long count_permutations(size_t n, size_t depth, bool *used) {
    if (depth == n) return 1;
    long long total = 0;
    for (size_t index = 0; index < n; index++) {
        if (used[index]) continue;
        used[index] = true;
        total += count_permutations(n, depth + 1, used);
        used[index] = false;
    }
    return total;
}

long long count_subsets(size_t n, size_t start) {
    long long total = 1;
    for (size_t index = start; index < n; index++) {
        total += count_subsets(n, index + 1);
    }
    return total;
}

bool is_safe(size_t row, size_t column, const size_t *placed) {
    for (size_t previous_row = 0; previous_row < row; previous_row++) {
        size_t previous_column = placed[previous_row];
        size_t row_gap = row > previous_row ? row - previous_row : previous_row - row;
        size_t column_gap = column > previous_column ? column - previous_column : previous_column - column;
        if (previous_column == column || row_gap == column_gap) return false;
    }
    return true;
}

long long place_queens(size_t n, size_t row, size_t *placed) {
    if (row == n) return 1;
    long long total = 0;
    for (size_t column = 0; column < n; column++) {
        if (is_safe(row, column, placed)) {
            placed[row] = column;
            total += place_queens(n, row + 1, placed);
        }
    }
    return total;
}

long long n_queens_count(size_t n) {
    size_t placed[MAX_N];
    return place_queens(n, 0, placed);
}

int main(void) {
    bool used[MAX_N] = {false};
    assert(count_permutations(3, 0, used) == 6);
    assert(count_subsets(3, 0) == 8);
    assert(n_queens_count(4) == 2);
    assert(n_queens_count(8) == 92);
    puts("c: all checks passed");
    return 0;
}
