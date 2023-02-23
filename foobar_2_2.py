def solution(l):
    # function which append digit d after n
    def append_digit(n, d):
        return 10 * n + d
    
    # sort input list
    l.sort()

    # get remainder of sum digits when divide 3
    sum_d = 0
    for d in l:
        sum_d += d
    r = sum_d % 3

    # if r!=0, find the smallest digit has the same remainder to sum_d and remove if exist
    if r != 0:
        exist_same_r = False
        for d in l:
            if d % 3 == r:
                l.remove(d)
                exist_same_r = True
                break

        # if there isn't digit has the same r, find 2 smallest digits has the same r to each other (r!=0) 
        # and remove it if exist, if not return 0
        if not exist_same_r:
            # with r = 1
            if r == 1:
                d11 = -1
                d12 = -1
                for d in l:
                    if d11 == -1 and d % 3 == 2:
                        d11 = d
                        continue
                    if d11 != -1 and d12 == -1 and d % 3 == 2:
                        d12 = d
                if d11 * d12 < 0:
                    return 0
                else:
                    l.remove(d11)
                    l.remove(d12)

            # with r = 2
            if r == 2:
                d21 = -1
                d22 = -1
                for d in l:
                    if d21 == -1 and d % 3 == 1:
                        d21 = d
                        continue
                    if d21 != -1 and d22 == -1 and d % 3 == 1:
                        d22 = d

                if d21 * d22 < 0:
                    return 0
                else:
                    l.remove(d21)
                    l.remove(d22)            

    # begin process
    n = 0
    for d in reversed(l):
        n = append_digit(n, d)

    return n

# print(solution([3, 1, 4, 1, 5, 9]))
print(solution([1, 7, 7, 4, 4]))