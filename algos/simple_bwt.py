def bwt(s: str) -> str:
    assert "\002" not in s and "\003" not in s, "Input string cannot contain STX and ETX characters"
    s = "\002" + s + "\003"
    table = sorted(s[i:] + s[:i] for i in range(len(s)))
    return "".join([row[-1:] for row in table])


def inverse_bwt(r: str) -> str:
    table = [""] * len(r)
    for i in range(len(r)):
        table = sorted(r[i] + table[i] for i in range(len(r)))
    return [row for row in table if row.endswith("\003")][0].rstrip("\003").strip("\002")
