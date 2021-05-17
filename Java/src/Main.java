import astar.Position;

class Main
{
    public static void main(String[] args)
    {
        Position point = new Position(1, 2);
        System.out.println(String.valueOf(point.x) + ":" + String.valueOf(point.y));


        /*for (Position p : point.get_surrounding_positions())
        {
            System.out.println(String.valueOf(p.x) + ":" + String.valueOf(p.y));
        }*/
    }
}