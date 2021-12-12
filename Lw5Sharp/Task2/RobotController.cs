using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task2
{
    internal class RobotController
    {
        private readonly TextReader _reader;
        private readonly TextWriter _writer;
        private readonly Robot _robot;
        private readonly Menu menu;
 
        public RobotController(TextReader reader, TextWriter writer)
        {
            _reader = reader;
            _writer = writer;

            menu = new(_reader, _writer);
            _robot = new();

            menu.AddItem("on", "Turns the robot on", _robot.TurnOn);
            menu.AddItem("off", "Turns the robot off", _robot.TurnOff);
            menu.AddItem("north", "Makes the Robot walk north", () => _robot.Walk(WalkDirection.North));
            menu.AddItem("south", "Makes the Robot walk south", () => _robot.Walk(WalkDirection.South));
            menu.AddItem("west", "Makes the Robot walk west", () => _robot.Walk(WalkDirection.West));
            menu.AddItem("east", "Makes the Robot walk east", () => _robot.Walk(WalkDirection.East));
            menu.AddItem("stop", "Stop the robot", _robot.Stop);
            menu.AddItem("exit", "Exit from this menu", menu.Exit);
            menu.AddItem("help", "Show instructions", menu.ShowInstructions);
            menu.AddItem("macro", "Entering macro creation mode", menu.CreateMacroCommand);
        }

        public void Start()
        {
            menu.Run();
        }
    }
}
