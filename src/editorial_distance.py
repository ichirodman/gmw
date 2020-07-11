s1 = list(input())
s2 = list(input())

s_temp = [range(len(s2) + 1)] + [[i + 1] + [0] * len(s2) for i in range(len(s1))]
for i in range(len(s1)):
    for j in range(len(s2)):
        s_temp[i + 1][j + 1] = min(s_temp[i][j] + (s1[i] != s2[j]), s_temp[i][j + 1] + 1, s_temp[i + 1][j] + 1)

s1_ans = list()
s2_ans = list()
s1_len = len(s1)
s2_len = len(s2)


while s1_len and s2_len:
    m = min(s_temp[s1_len - 1][s2_len - 1] + (s1[s1_len - 1] != s2[s2_len - 1]), s_temp[s1_len - 1][s2_len] + 1,
            s_temp[s1_len][s2_len - 1] + 1)
    if s_temp[s1_len - 1][s2_len] + 1 == m:
        s1_ans.append(s1[s1_len - 1])
        s2_ans.append('-')
        s1_len -= 1
    elif s_temp[s1_len][s2_len - 1] + 1 == m:
        s1_ans.append('-')
        s2_ans.append(s2[s2_len - 1])
        s2_len -= 1
    else:
        s1_ans.append(s1[s1_len - 1])
        s2_ans.append(s2[s2_len - 1])
        s1_len -= 1
        s2_len -= 1

for i in range(s1_len - 1, -1, -1):
    s1_ans.append(s1[i])
    s2_ans.append('-')
for i in range(s2_len - 1, -1, -1):
    s1_ans.append('-')
    s2_ans.append(s2[i])

print(''.join(s1_ans[::-1]))
print(''.join(s2_ans[::-1]))
