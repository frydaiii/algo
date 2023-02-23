def solution(src, dest):
    class Cell:
        def __init__(self, index, prev = None):
            self.index = index
            self.prev = prev

    # init steps
    steps = [(-2, -1), (-2, 1), (1, -2), (-1, -2), (1, 2), (-1, 2), (2, -1), (2, 1)]

    # visited cells and queue of cells that need to visited
    visited_indexs = []
    vcells = [Cell(src)]

    # cell index to position function
    def i2pos(i):
        x = i // 8
        y = i % 8
        return (x, y)
    
    # position to index function
    def pos2i(x, y):
        if 7 >= x >= 0 and 7 >= y >= 0:
            return 8 * x + y
        return -1

    # begin process
    if src == dest:
        return 0
    dest_cell = None
    while True:
        current_cell = vcells.pop(0)
        visited_indexs.append(current_cell.index)
        if current_cell.index == dest:
            dest_cell = current_cell
            break
        (x_src, y_src) = i2pos(current_cell.index)
        for step in steps:
            (x_step, y_step) = step
            x = x_src + x_step
            y = y_src + y_step
            next_cell_index = pos2i(x, y)
            if next_cell_index != -1 and next_cell_index not in visited_indexs:
                vcells.append(Cell(next_cell_index, current_cell))

    # get the result
    count_step = 0
    while True:
        count_step += 1
        dest_cell = dest_cell.prev
        if dest_cell.index == src:
            break

    return count_step

import sys
print(solution(int(sys.argv[1]), int(sys.argv[2])))
