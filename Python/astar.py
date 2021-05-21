import Position
import heapq

def heuristic(a, b):
    return abs( (a.x - b.x) + (a.y - b.y) )


def astar_search(weighted_map, start, goal):
    mapWidth = len(weighted_map[0])
    mapHeight = len(weighted_map)

    path = []
    if (start.x < 0) or (start.y < 0) or (goal.x >= mapWidth) or (goal.y >= mapHeight) or \
            (start == goal) or (mapWidth < 2) or (mapHeight < 2):
        return path

    close_set = set()
    came_from = dict()
    gscore = {start: 0}
    fscore = {start : heuristic(start, goal)}
    oheap_copy = { start }
    oheap = []
    heapq.heappush(oheap, (fscore[start], start))


    while ( len(oheap) > 0 ):
        current = heapq.heappop(oheap)[1]
        try:
            oheap_copy.remove(current)
        except:
            pass

        if current == goal:
            # path found!
            while current in came_from:
                path.append(current)
                current = came_from[current]

            path.reverse()
            return path

        # add current position to the already searched list
        close_set.add(current)
        neighbors = current.get_surrounding_positions()

        for neighbor in neighbors:
            if (neighbor.x >= 0 and neighbor.y >= 0 and
                    neighbor.y < mapHeight and neighbor.x < mapWidth and
                    weighted_map[neighbor.y][neighbor.x] < 255):

                tentative_gscore = gscore[current] + weighted_map[neighbor.y][neighbor.x]

                current_gscore = 0
                if neighbor in gscore:
                    current_gscore = gscore[neighbor]

                if (tentative_gscore >= current_gscore and
                        neighbor in close_set):
                    continue

                if (tentative_gscore < current_gscore or
                        neighbor not in oheap_copy):

                    # track the node's parent
                    came_from[neighbor] = current

                    # gscore = cost to get from start to the curernt position
                    # hscore = estimated cost to get from the current position to the goal
                    # fscore = gscore + hscore
                    gscore[neighbor] = tentative_gscore
                    fscore[neighbor] = tentative_gscore + heuristic(neighbor, goal)

                    # add to the open list
                    if (fscore[neighbor], neighbor) in oheap:
                        print('WHOOAAAA HOOLD UPP')

                    heapq.heappush(oheap, (fscore[neighbor], neighbor))
                    if neighbor not in oheap_copy:
                        oheap_copy.add(neighbor)

    return path