# Google Foobar lvl 1: Solar Doomsday

from math import sqrt, pow

def solution(area):
    panels = []
    tmp_area = area
    biggest_panel_side = 0
    biggest_panel_area = 0
 
    while True:
        if tmp_area < 4:
            panels.extend((1 for _ in range(tmp_area)))
            break
 
        biggest_panel_side = int(sqrt(tmp_area))
        biggest_panel_area = int(pow(biggest_panel_side, 2))
        panels.append(biggest_panel_area)
        tmp_area -= biggest_panel_area
 
    return panels