using System;
using System.Collections;
using System.Collections.Generic;
using Priority_Queue;


namespace astar
{
    /// <summary>
    /// A position is an object with x and y values indicating the absolute position on the map.
    /// </summary>
    public class Position : FastPriorityQueueNode
    {
        public readonly int x;
        public readonly int y;

        public Position(int x, int y)
        {
            this.x = x;
            this.y = y;
        }

        /// <summary>
        /// Returns a list of all positions around the given position in each cardinal direction
        /// </summary>
        public List<Position> GetSurroundingPositions()
        {
            List<Position> neighbors = new List<Position>();
            neighbors.Add(new Position(this.x + 0, this.y - 1)); // north
            neighbors.Add(new Position(this.x + 1, this.y + 0)); // east
            neighbors.Add(new Position(this.x + 0, this.y + 1)); // south
            neighbors.Add(new Position(this.x - 1, this.y + 0)); // west
            return neighbors;
        }

        public override bool Equals(object o)
        {
            if (this == o)return true;
            if (o == null || this.GetType() != o.GetType()) return false;

            Position position = (Position) o;

            if (x != position.x) return false;
            return y== position.y;
        }

        public override int GetHashCode()
        {
            return (this.x >= this.y) ? this.x * this.x + this.x + this.y : this.x + this.y * this.y; // szudziks function
        }

        public override string ToString()
        {
            return this.x.ToString() + ":" + this.y.ToString();
        }
    }
}