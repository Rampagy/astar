from astar import astar_search
from Position import Position
import random
import time

MAP_HEIGHT = 500
MAP_WIDTH = 500
SEARCH_ITERATIONS = 100


def generate_map():
    maze = []
    for _ in range(MAP_HEIGHT):
        maze_row = []
        for _ in range(MAP_WIDTH):
            maze_row += [random.randint(0, 255)]

        maze += [maze_row]

    return maze



if __name__=='__main__':
    start = Position(0, 0)
    goal = Position(MAP_WIDTH-1, MAP_HEIGHT-1)
    maze = generate_map()

    # make sure start and end are walkable
    maze[start.y][start.x] = 0
    maze[goal.y][goal.x] = 0

    total_time = 0
    path = []

    for _ in range(SEARCH_ITERATIONS):
        start_time = time.time()

        path = astar_search(maze, start, goal)

        end_time = time.time()
        total_time += end_time - start_time

        # generate a new random map every iteration
        maze = generate_map()

    print('Python path found in {:0.4f} seconds'.format(total_time))