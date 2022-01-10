﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;
using System.Collections.ObjectModel;

namespace Lw9.Model
{
    public class CanvasModel : INotifyPropertyChanged
    {
        private ObservableCollection<ShapeModel> _shapes = new();
        private int _height;
        private int _width;

        public ObservableCollection<ShapeModel> Shapes
        {
            get { return _shapes; }
        }
        public int Height
        {
            get { return _height; }
            set
            {
                if (_height == value) return;
                _height = value;
                OnPropertyChanged("Height");
            }
        }
        public int Width
        {
            get { return _width; }
            set 
            {
                if (_width == value) return;
                _width = value;
                OnPropertyChanged("Width");
            }
        }
        
        public event PropertyChangedEventHandler? PropertyChanged;
        void OnPropertyChanged(string propertyName) => PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
}
