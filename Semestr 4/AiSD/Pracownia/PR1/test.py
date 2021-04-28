import random

testArray = []


# print(testArray)


def binary_search(arr, low, high, x, index):
    if high >= low:
        mid = (high + low) // 2
        if arr[mid] == x and mid != index:
            return mid
        elif arr[mid] > x:
            return binary_search(arr, low, mid - 1, x, index)
        else:
            return binary_search(arr, mid + 1, high, x, index)
    else:
        return -1


def findNumberOfStrings(array):

    uniqueElements = []

    while len(uniqueElements) != len(array):
        for element in array:
            uniqueElements = list(set(array))
            print(f"Unique elements = {uniqueElements}")
            array.sort()
            i = array.index(element)
            index = binary_search(array, 0, len(array) - 1, element, i)

            if index != -1:
                a = array[index]
                array.remove(a)
                array.remove(a)
                array.append(2 * a)
            print(array)
    return array


def createStruct(array):
    occurences = []
    keys = []
    for key in array:
        if key in keys:
            occurences[key][1] += 1
        else:
            keys.append(key)
            occurences.append([key, 1])

    return occurences


# def findNumberOfStrings2(array):
#     occurences = createStruct(array)
#     newOccurences = []
#     print(occurences)

# for key in occurences:
#     k = 0
#     value = occurences[key]
#     while value:
#         digit = value & 1
#         if digit:
#             newKey = key * 2**k
#             if newKey in newOccurences.keys():
#                 newOccurences[newKey] += 1
#             else:
#                 newOccurences[newKey] = 1
#         value = value >> 1
#         print(value)
#         k += 1
#     print(newOccurences)
# occurences = newOccurences


a = [3, 3, 3, 6, 6, 6, 6, 6, 7]
b = [1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3]
c = [2] * 13
d = [7, 7, 7, 8, 8, 8, 8, 1, 1, 2, 2, 2, 6, 6, 6, 3, 3, 3]

# for i in range(10):
#     testArray.append(random.randint(0, 5))

# testArray.sort()

array = findNumberOfStrings(d)

# findNumberOfStrings2(a)