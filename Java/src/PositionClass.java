package position;

import java.util.List;
import java.util.ArrayList;

public class PositionClass
{
    public int x;
    public int y;

    public PositionClass(int newX, int newY)
    {
        x = newX;
        y = newY;
    }

    /*
    public List<Position> get_surrounding_positions()
    {
        List<Position> neighbors = new ArrayList<Position>();
        neighbors.add( new Position(x + 0, y - 1) ); // north
        neighbors.add( new Position(x + 1, y + 0) ); // east
        neighbors.add( new Position(x + 0, y + 1) ); // south
        neighbors.add( new Position(x - 1, y + 0) ); // west

        return neighbors;
    }*/
}
