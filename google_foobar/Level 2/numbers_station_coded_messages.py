# Google Foobar lvl 2: Numbers Station Coded Messages

def solution(l, t):
    n = len(l)
    right = 0
 
    for left in range(n):
        for x in range(n - left):
            right = left + x + 1
            res = l[left:right]
            if sum(res) == t:
                return [left, right - 1]
 
    return [-1, -1]