_MU = 3
_DELTA = 2


def swa(v: str, w: str):
    max_len = max(len(v), len(w))
    matrix = [[0] * (len(w) + 1) for _ in range(len(v) + 1)]
    max_val_coords = [0, 0]
    for j in range(1, len(matrix[0])):
        for i in range(1, len(matrix)):
            to_check = [matrix[i][j - 1] - _DELTA, matrix[i - 1][j] - _DELTA,
                        (matrix[i - 1][j - 1] + 3) if v[i - 1] == w[j - 1] else (matrix[i - 1][j - 1] - _MU)]
            matrix[i][j] = max(max(to_check), 0)
            if matrix[i][j] > matrix[max_val_coords[0]][max_val_coords[1]]:
                max_val_coords = [i, j]
    i, j = max_val_coords
    stack = [max_val_coords[:]]
    while i > 1 or j > 1:
        good = list()
        to_compare = list()
        if stack[-1][0] > 1 and stack[-1][1] > 1:
            good = [i - 1, j - 1, [-1, -1]]
        if stack[-1][0] > 1:
            to_compare.append([i - 1, j, [-1, 0]])
        if stack[-1][1] > 1:
            to_compare.append([i, j - 1, [0, -1]])
        if not good:
            good = to_compare.pop()
        for cell in to_compare:
            if matrix[good[0]][good[1]] < matrix[cell[0]][cell[1]]:
                good = cell
        i += good[-1][0]
        j += good[-1][1]
        stack.append([i, j])
    r1, r2 = '', ''
    for ind in range(len(stack)):
        i, j = stack[ind]
        if ind == len(stack) - 1:
            r1 = v[i - 1] + r1
            r2 = w[j - 1] + r2
        else:
            r1 = ('-' if stack[ind + 1][0] == stack[ind][0] else v[i - 1]) + r1
            r2 = ('-' if stack[ind + 1][1] == stack[ind][1] else w[j - 1]) + r2
    r1 += '-' * (max_len - len(r1))
    r2 += '-' * (max_len - len(r2))
    links = ''
    for i in range(max_len):
        links += '|' if r1[i] == r2[i] else ' '
    return r1, links, r2
