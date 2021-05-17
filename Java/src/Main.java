package astar;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.HashMap;
import java.util.HashSet;
import java.util.PriorityQueue;

public class Main {
	static Random random = new Random();
	final static int MAP_WIDTH = 5000;
	final static int MAP_HEIGHT = 5000;
	final int SEARCH_ITERATIONS = 2000;
	static List<List<Integer>> maze = new ArrayList<List<Integer>>();
	
	static void GenerateMaze()
	{
		//height
		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			List<Integer> maze_row = new ArrayList<Integer>();
			//width
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				//System.out.println("i is " + i + "j is " + j);
				int temp = random.nextInt();
				if (temp < 0)
				{
					temp = -temp;
				}
				maze_row.add(temp % 256);
			}
			maze.add(maze_row);
		}
	}
	
	
	public static void main(String[] args) 
	{
		Position start = new Position(0, 0);
		Position goal = new Position(MAP_WIDTH - 1, MAP_HEIGHT - 1);
		GenerateMaze();
		//System.out.println(String.valueOf(point.x)+ ":" + String.valueOf(point.y));
		System.out.println(maze.get(0).get(0).toString());
		maze.get(start.x).set(start.y, 0);
		maze.get(MAP_WIDTH - 1).set(MAP_HEIGHT - 1, 0);

		
		
	}
	
	static List<Position> OptimizedAStarSearch(ArrayList<List<Integer>> weightedMap, Position start, Position goal)
	{
		int mapWidth = weightedMap.get(0).size();
		int mapHeight = weightedMap.size();
		
		List<Position> path = new ArrayList<Position>();
		if((start.x < 0 )|| (start.y < 0) || (goal.x >= mapWidth) || (goal.y >= mapHeight) || 
				(start == goal) || (mapWidth < 2) || (mapHeight < 2))
		{
			return path;
		}
		
		HashSet<Position> close_set = new HashSet<Position>();
		HashMap<Position, Position> came_from = new HashMap<Position, Position>();
		HashMap<Position, Float> gscore = new HashMap<Position, Float>();
		HashMap<Position, Float> fscore = new HashMap<Position, Float>();
		PriorityQueue<Integer> oheap = new PriorityQueue<Integer>();
		
		Position current;
		List<Position> neighbors = new ArrayList<Position>();
		HashMap<Position, Float> neighborIter = new HashMap<Position, Float>();
		float tentative_gscore;
		float current_gscore;
		
		gscore.put(start, (float)0);
		fscore.put(start, OptimizedHeuristic(start, goal));
		
		
		return path;
	}
	

	static float OptimizedHeuristic(Position a, Position b)
	{
		return (float)Math.abs( (a.x - b.x)+ (a.y - b.y));
	}
}
