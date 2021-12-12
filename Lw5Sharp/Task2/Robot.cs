using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task2
{

    public enum WalkDirection
    {
        North,
        South,
        West,
        East,
        UnknownDirection
    }

    internal class Robot
    {
        private bool turnedOn = false;
        private WalkDirection? direction;

        private WalkDirection Direction
        {
            get { return direction ?? WalkDirection.UnknownDirection; }
            set 
            {
                switch (value)
                {
                    case WalkDirection.North: Console.WriteLine("Walking north"); break;
                    case WalkDirection.South: Console.WriteLine("Walking south"); break;
                    case WalkDirection.West: Console.WriteLine("Walking west"); break;
                    case WalkDirection.East: Console.WriteLine("Walking east"); break;
                    default: Console.WriteLine("Error"); break;
                }
                direction = value; 
            }
        }

        public void TurnOn()
        {
            if (turnedOn) return;
            turnedOn = true;
            Console.WriteLine("It am waiting for your commands");
        }
        public void TurnOff()
        {
            if (!turnedOn) return;
            turnedOn = false;
            Console.WriteLine("It is a pleasure to serve you");
        }
        public void Walk(WalkDirection direction)
        {
            if (!turnedOn)
            {
                Console.WriteLine("The robot should be turned on first");
                return;
            }

            Direction = direction;
        }

        public void Stop()
        {
            Console.WriteLine("Stop walking");
        }
    }
}
