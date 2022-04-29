


def printRatio(arr):
    i = 0
    j = 0
    k = 0
    sz = len(arr)

    for v in range(sz):
        if arr[v] == 0:
            i += 1
        if arr[v] > 0:
            j += 1
        if arr[v] < 0:
            k += 1

    output = "".format()


if __name__ == '__main__':
    arr0 = [1, 1, -1, 0, -1]
    printRatio(arr0)
