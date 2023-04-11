# Google Foobar lvl 2: Please Pass the Coded Messages

def get_max_number(l):
    list_sum = sum(l)
    if list_sum % 3 == 0:
        return l
 
    max_list = []
    tmp_max_list = []
 
    for i in range(len(l)):
        items = l[:i]
        items.extend(l[i+1:])
 
        tmp_max_list = get_max_number(items)
        if len(tmp_max_list) > len(max_list):
            max_list = tmp_max_list
 
    return max_list
 
def solution(l):
    l.sort()
    res = get_max_number(l)
    res.sort(reverse = True)
 
    if(len(res) > 0):
        number = [str(x) for x in res] 
        return ''.join(number)
    else:
        return '0'