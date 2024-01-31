def longest_repeated_subsequence(a) :
    n = len(a)

    M = [[0]* n for i in range(n)]
    M[0][0] = 0

    # First row
    for j in range(1, n):
        if a[0] == a[j]:
            M[0][j] = 1
        else:
            M[0][j] = M[0][j - 1]

    # First column
    for i in range(1, n):
        if a[i] == a[0]:
            M[i][0] = 1
        else:
            M[i][0] = M[i - 1][0]

    for i in range(1, n):
        for j in range(1, n):
            if a[i] == a[j] and i != j:
                M[i][j] = max(M[i - 1][j - 1] + 1, M[i - 1][j], M[i][j - 1])
            else :
                M[i][j] = max(M[i - 1][j], M[i][j - 1])


    return M[n - 1][n - 1]


def main() :
    strings = [
        'abab',
        'abba',
        'acbdaghfb',
        'abcdacb'
    ]

    for s in strings :
        print(longest_repeated_subsequence(s) > 1)


if __name__ == "__main__":
    main()