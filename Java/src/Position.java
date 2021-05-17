package astar;

import java.util.ArrayList;
import java.util.List;

public class Position {

    int x;
    int y;

    Position(int first, int second)
    {
        x = first;
        y = second;
    }

    boolean CompareEqual(Position compareTo)
    {
        if (this.x == compareTo.x)
        {
            if(this.y == compareTo.y)
            {
                return true;
            }
        }
        return false;
    }

    public List<Position> GetSurroundingPositions()
    {
        List<Position> neighbors = new ArrayList<Position>();
        neighbors.add(new Position(x + 0, y - 1)); // north
        neighbors.add(new Position(x + 1, y + 0)); // east
        neighbors.add(new Position(x + 0, y + 1)); // south
        neighbors.add(new Position(x - 1, y + 0)); // west
        return neighbors;
    }
}
