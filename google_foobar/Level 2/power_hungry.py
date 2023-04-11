# Google Foobar lvl 2: Power Hungry

def solution(xs):
    # List pre-processing
    helper_list = []
    xs.sort(reverse=True)
    prev_res = None

    # Positive levels
    for i in range(len(xs)):
        if xs[i] > 0:
            helper_list.append(xs[i])
        else:
            break
    
    # Negative levels
    for i in range(len(xs) - 1, -1, -1):
        if xs[i] < 0:
            helper_list.append(xs[i])
        else:
            if xs[i] == 0:
                prev_res = 0
            break
    
    n = len(helper_list)
    if n == 0:
        return str(0)
    
    res = helper_list[0]
    if prev_res == None:
        prev_res = res
    
    for i in range(1, n):
        prev_res = res
        res *= helper_list[i]
    
    return str(res if res > 0 else prev_res)