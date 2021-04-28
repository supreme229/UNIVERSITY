def source_check(matrix):
    iterator, result = 0, True
    for i in range(len(matrix[iterator])):
        if matrix[iterator][i] == 0 and iterator != i:
            iterator = i

    for i in range(len(matrix[iterator])):
        if matrix[iterator][i] != 1 and iterator != i:
            result = False
        if matrix[i][iterator] != 0 and iterator != i:
            result = False

    return result


print(
    source_check(
        [
            [0, 1, 0, 0, 1],
            [0, 0, 0, 1, 1],
            [1, 1, 0, 1, 1],
            [1, 0, 0, 0, 1],
            [0, 0, 0, 0, 0],
        ]
    )
)

print(
    source_check(
        [
            [0, 1, 1, 1],
            [0, 0, 0, 1],
            [0, 0, 0, 1],
            [0, 0, 0, 0],
        ]
    )
)


print(
    source_check(
        [
            [0, 1, 0, 1],
            [0, 0, 0, 1],
            [1, 1, 0, 0],
            [0, 0, 1, 0],
        ]
    )
)
