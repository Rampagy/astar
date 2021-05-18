package astar;

import java.util.Collections;

class Pair implements Comparable<Pair>
{
    Float value;
    Position position;

    public Pair(Float value, Position position)
    {
        this.value = value;
        this.position = position;
    }

    @Override
    public int compareTo(Pair o)
    {
        float diff = value - o.value;

        if (diff < 0)
        {
            return -1;
        }
        else if (diff > 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}