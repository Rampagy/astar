package astar;

import java.util.ArrayList;

public class Position {
    public final int x;
    public final int y;

    public Position(final int x, final int y) {
        this.x = x;
        this.y = y;
    }

    public ArrayList<Position> GetSurroundingPositions()
    {
        final ArrayList<Position> neighbors = new ArrayList<Position>();
        neighbors.add(new Position(x + 0, y - 1)); // north
        neighbors.add(new Position(x + 1, y + 0)); // east
        neighbors.add(new Position(x + 0, y + 1)); // south
        neighbors.add(new Position(x - 1, y + 0)); // west
        return neighbors;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Position position = (Position) o;

        if (x != position.x) return false;
        return y == position.y;
    }

    @Override
    public int hashCode() {
        int result = x;
        result = 31 * result + y;
        return result;
    }
}
