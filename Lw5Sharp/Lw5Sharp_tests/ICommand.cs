﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Document
{
    internal interface ICommand
    {
        void Execute(string[]? args = null);
        void Unexecute();
    }
}
