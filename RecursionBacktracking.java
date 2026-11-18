package com.mahatab.algo;

import java.util.ArrayList;
import java.util.List;

public final class RecursionBacktracking {

    private RecursionBacktracking() {
    }

    public static List<List<Integer>> permutations(int[] nums) {
        List<List<Integer>> results = new ArrayList<>();
        boolean[] used = new boolean[nums.length];
        buildPermutations(nums, used, new ArrayList<>(), results);
        return results;
    }

    private static void buildPermutations(int[] nums, boolean[] used, List<Integer> path, List<List<Integer>> results) {
        if (path.size() == nums.length) {
            results.add(new ArrayList<>(path));
            return;
        }
        for (int index = 0; index < nums.length; index++) {
            if (used[index]) {
                continue;
            }
            used[index] = true;
            path.add(nums[index]);
            buildPermutations(nums, used, path, results);
            path.remove(path.size() - 1);
            used[index] = false;
        }
    }

    public static List<List<Integer>> subsets(int[] nums) {
        List<List<Integer>> results = new ArrayList<>();
        buildSubsets(nums, 0, new ArrayList<>(), results);
        return results;
    }

    private static void buildSubsets(int[] nums, int start, List<Integer> path, List<List<Integer>> results) {
        results.add(new ArrayList<>(path));
        for (int index = start; index < nums.length; index++) {
            path.add(nums[index]);
            buildSubsets(nums, index + 1, path, results);
            path.remove(path.size() - 1);
        }
    }

    private static boolean isSafe(int row, int column, int[] placed) {
        for (int previousRow = 0; previousRow < row; previousRow++) {
            int previousColumn = placed[previousRow];
            if (previousColumn == column || Math.abs(row - previousRow) == Math.abs(column - previousColumn)) {
                return false;
            }
        }
        return true;
    }

    private static int placeQueens(int n, int row, int[] placed) {
        if (row == n) {
            return 1;
        }
        int total = 0;
        for (int column = 0; column < n; column++) {
            if (isSafe(row, column, placed)) {
                placed[row] = column;
                total += placeQueens(n, row + 1, placed);
            }
        }
        return total;
    }

    public static int nQueensCount(int n) {
        return placeQueens(n, 0, new int[n]);
    }

    private static void require(boolean condition, String name) {
        if (!condition) {
            throw new AssertionError(name);
        }
    }

    public static void main(String[] args) {
        List<List<Integer>> perms = permutations(new int[] {1, 2, 3});
        require(perms.size() == 6, "permutation count");
        require(perms.get(0).equals(List.of(1, 2, 3)), "first permutation");
        require(perms.get(5).equals(List.of(3, 2, 1)), "last permutation");
        require(subsets(new int[] {1, 2, 3}).size() == 8, "subset count");
        require(nQueensCount(4) == 2, "4 queens");
        require(nQueensCount(8) == 92, "8 queens");
        System.out.println("java: all checks passed");
    }
}
