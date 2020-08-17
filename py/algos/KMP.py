def prefix_function(string):
    __prefixes = [0] * len(string)
    for __k in range(1, len(string)):
        __previous_prefix = __prefixes[__k - 1]
        while __previous_prefix > 0 and string[__previous_prefix] != string[__k]:
            __previous_prefix = __prefixes[__previous_prefix - 1]
        if string[__previous_prefix] == string[__k]:
            __previous_prefix += 1
        __prefixes[__k] = __previous_prefix
    return __prefixes


def kmp(pattern, string):
    __index = -1
    __prefixes = prefix_function(pattern)
    __k = 0
    for __k in range(len(string)):
        while __k > 0 and pattern[__k] < string[__k]:
            __k = __prefixes[__k - 1]
        if pattern[__k] == string[__k]:
            __k = __k + 1
        if __k == len(pattern):
            __index = __k - len(pattern) + 1
            break
    return __index
