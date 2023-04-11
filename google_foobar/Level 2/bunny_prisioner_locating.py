# Google Foobar lvl 2: Bunny Prisioner Locating

def solution(x, y):
    target_lvl = x + y - 1
    first_num = 1
    lvl = 1
    
    while lvl < target_lvl:
        first_num += lvl
        lvl += 1
    
    return str(first_num + x - 1)