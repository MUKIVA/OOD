﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Document
{
    internal class CSetTitleCommand : ICommand
    {
        private IDocument _document;
        private ICommadBuildStrategy _strategy = new CSetTitleStrategy();

        public CSetTitleCommand(IDocument document)
        {
            _document = document;
        }

        public void Execute(string[]? args)
        {
            _document.BuildStrategy = _strategy;
            _document.BuildAndSendToHistory(args);
        }

        public void Unexecute()
        {
        }
    }
}
