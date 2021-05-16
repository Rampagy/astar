import position.PositionClass;

class Main
{
    public static void main(String[] args)
    {
        PositionClass point = new PositionClass(1, 2);
        System.out.println(String.valueOf(point.x) + ":" + String.valueOf(point.y));


        /*for (Position p : point.get_surrounding_positions())
        {
            System.out.println(String.valueOf(p.x) + ":" + String.valueOf(p.y));
        }*/
    }
}