# Google Foobar lvl 1: The cake is not a lie!

def solution(s):
    n = len(s)
    pos = 0
    is_valid_sequence = True
    sequence_len = 0
    
    for i in range(1, n + 1):
        is_valid_sequence = True
        
        if n % i == 0:
            sequence_len = n // i
            
            for j in range(1, sequence_len):
                pos = i * j
                
                if s[pos - i:pos] != s[pos:pos + i]:
                    is_valid_sequence = False
                    break
                
            if is_valid_sequence:
                return sequence_len