
buildings = [[2,9,10],[9,12,15]]
buildings = [[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]]
buildings = [[0,2,3],[2,5,3]]
buildings = [[1,2,1],[1,2,2],[1,2,3]]
buildings = [[1,5,3], [1,5,3], [1,5,3]]
# buildings = [[1,20,1],[1,21,2],[1,22,3]]
# buildings = [[2,14,4],[4,8,8],[6,16,4]]

remove = []
# append = []
for i, building_i in enumerate(buildings):
    for j, building_j in enumerate(buildings):
        if i < j and building_j[0] <= building_i[1] and building_i[2] == building_j[2]:
            # remove.append(building_i)
            # remove.append(building_j)
            # append.append([building_i[0], building_j[1], building_i[2]])
            buildings[j][0] = building_i[0]
for i, building_i in enumerate(buildings):
    for j, building_j in enumerate(buildings):
        if i < j and building_i[0] == building_j[0] and building_i[1] <= building_j[1] and building_i[2] <= building_j[2]:
            # remove.append(building_i)
            buildings[i] = building_j
for building_to_remove in remove:
    try:
        buildings.remove(building_to_remove)
    except:
        pass

buildings.sort(key=lambda x:x[2], reverse=True)

busy_grounds = []
outline = []

def in_busy_grounds(building, busy_grounds):
    for i, ground in enumerate(busy_grounds):
        if building[1] < ground[0] or building[0] > ground[1]:
            continue
        else: 
            return i
    return None

for i, building in enumerate(buildings):
    ground_index = in_busy_grounds(building, busy_grounds)
    if ground_index == None:
        outline.append([building[0], building[2]])
        busy_grounds.append([building[0], building[1]])
    else:
        # if busy_grounds[ground_index][0] < building[0] and building[0] < busy_grounds[ground_index][1]: 
        #     nearest_point = busy_grounds[ground_index][1]
        #     outline.append([nearest_point, building[2]])

        # if busy_grounds[ground_index][0] < building[1] and building[1] < busy_grounds[ground_index][1]: 
        #     nearest_point = building[0]
        #     outline.append([nearest_point, building[2]])

        # if busy_grounds[ground_index][0] == building[1]: 
        #     outline.append([building[0], building[2]])

        # if busy_grounds[ground_index][1] == building[0]: 
        #     outline.append([building[0], building[2]])
        
        # if busy_grounds[ground_index][0] < building[0] and busy_grounds[ground_index][1] <= building[1]:
            # outline.append(building[0], building[2])
        
        busy_ground = busy_grounds[ground_index]
        if busy_ground[0] > building[0]:
            outline.append([building[0], building[2]])
        if busy_ground[1] < building[1]:
            outline.append([busy_ground[1], building[2]])

        if building[1] == busy_grounds[ground_index][0]:
            busy_grounds[ground_index][0] = building[0]
        if building[0] == busy_grounds[ground_index][1]:
            busy_grounds[ground_index][1] = building[1]

        if busy_grounds[ground_index][1] < building[1]:
            busy_grounds[ground_index][1] = building[1]
        if busy_grounds[ground_index][0] > building[0]:
            busy_grounds[ground_index][0] = building[0]

for i, ground in enumerate(busy_grounds):
    outline.append([busy_grounds[i][1], 0])

outline.sort(key=lambda x:x[0])
# i = 1
# while i < len(outline):
#     if outline[i][1] == outline[i-1][1]:
#         outline.remove(outline[i])
#     else:
#         i += 1
print(outline)

