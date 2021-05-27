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
    oheap_copy = { start : fscore[start] }
    oheap = []
    heapq.heappush(oheap, (fscore[start], start))


    while ( len(oheap) > 0 ):
        current = heapq.heappop(oheap)[1]
        oheap_copy.pop(current)

        if current == goal:
            # path found!
            while current in came_from:
                path.append(current)
                current = came_from[current]

            path.reverse()
            return path

        neighbors = current.get_surrounding_positions()

        for neighbor in neighbors:

            # if the neighbor is a vlid position
            if (neighbor.x >= 0 and neighbor.y >= 0 and
                    neighbor.y < mapHeight and neighbor.x < mapWidth and
                    weighted_map[neighbor.y][neighbor.x] < 255):

                neighbor_gscore = gscore[current] + weighted_map[neighbor.y][neighbor.x] + \
                                    heuristic(neighbor, current)
                neighbor_fscore = neighbor_gscore + heuristic(neighbor, goal)

                # if this neighbor is already on the open list with a smaller fscore, skip it
                open_neighbor = oheap_copy.get(neighbor)
                if (open_neighbor != None):
                    if open_neighbor <= neighbor_fscore:
                        continue
                # check if it is on the closed list
                elif neighbor in close_set:
                    if fscore.get(neighbor) <= neighbor_fscore:
                        continue
                # add to the open list
                else:
                    # track the node's parent
                    came_from[neighbor] = current

                    # gscore = cost to get from start to the curernt position
                    # hscore = estimated cost to get from the current position to the goal
                    # fscore = gscore + hscore
                    gscore[neighbor] = neighbor_gscore
                    fscore[neighbor] = neighbor_fscore

                    # add to the open list
                    heapq.heappush(oheap, (fscore[neighbor], neighbor))
                    oheap_copy[neighbor] = fscore[neighbor]

        # add current position to the already searched list
        close_set.add(current)

    return path