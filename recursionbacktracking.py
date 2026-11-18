def permutations(nums: list[int]) -> list[list[int]]:
    results: list[list[int]] = []
    used = [False] * len(nums)
    path: list[int] = []

    def build() -> None:
        if len(path) == len(nums):
            results.append(path.copy())
            return
        for index, value in enumerate(nums):
            if used[index]:
                continue
            used[index] = True
            path.append(value)
            build()
            path.pop()
            used[index] = False

    build()
    return results


def subsets(nums: list[int]) -> list[list[int]]:
    results: list[list[int]] = []
    path: list[int] = []

    def build(start: int) -> None:
        results.append(path.copy())
        for index in range(start, len(nums)):
            path.append(nums[index])
            build(index + 1)
            path.pop()

    build(0)
    return results


def is_safe(row: int, column: int, placed: list[int]) -> bool:
    for previous_row, previous_column in enumerate(placed):
        if previous_column == column or abs(row - previous_row) == abs(column - previous_column):
            return False
    return True


def place_queens(n: int, placed: list[int]) -> int:
    row = len(placed)
    if row == n:
        return 1
    total = 0
    for column in range(n):
        if is_safe(row, column, placed):
            placed.append(column)
            total += place_queens(n, placed)
            placed.pop()
    return total


def n_queens_count(n: int) -> int:
    return place_queens(n, [])


def main() -> None:
    perms = permutations([1, 2, 3])
    assert len(perms) == 6
    assert perms[0] == [1, 2, 3] and perms[-1] == [3, 2, 1]
    assert len(subsets([1, 2, 3])) == 8
    assert n_queens_count(4) == 2
    assert n_queens_count(8) == 92
    print("python: all checks passed")


if __name__ == "__main__":
    main()
