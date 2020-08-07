def rle(s: str) -> str:
    res, last_repeats_amount, last_non_repeat = '', 1, ''
    i = 0
    while True:
        if i >= len(s) - 1:
            if i == len(s) - 1:
                if last_non_repeat:
                    last_non_repeat += s[i]
                    res += '{}{}'.format((len(last_non_repeat)) * (-1 if len(last_non_repeat) > 1 else 1),
                                         last_non_repeat)
                else:
                    res += '{}{}'.format(last_repeats_amount, s[i])
            break
        else:
            if s[i] != s[i + 1]:
                last_non_repeat += s[i]
            else:
                if last_non_repeat:
                    res += '{}{}'.format((len(last_non_repeat)) * (-1 if len(last_non_repeat) > 1 else 1),
                                         last_non_repeat)
                    last_non_repeat = ''
                j = i
                while j < len(s):
                    if s[j] != s[i]:
                        break
                    else:
                        j += 1
                res += '{}{}'.format(j - i, s[i])
                i = j - 1

        i += 1
    return res


def inverse_rle(s: str) -> str:
    s = s.upper()
    res, i = '', 0
    while i < len(s):
        index = ''
        while s[i] == '-' or s[i].isdigit():
            index += s[i]
            i += 1
        index = int(index)
        if index > 0:
            letters = s[i] * index
            i += 1
        else:
            letters = s[i:i + abs(index)]
            i += abs(index)
        res += letters
    return res
