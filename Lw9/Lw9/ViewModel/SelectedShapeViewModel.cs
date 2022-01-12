using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;
using Lw9.Model;
using System.Collections.ObjectModel;
using System.Windows.Input;
using System.Windows;

namespace Lw9.ViewModel
{
    public class SelectedShapeViewModel : INotifyPropertyChanged
    {
        private ShapeViewModel? _selectedShape;
        public event PropertyChangedEventHandler? PropertyChanged;

        public SelectedShapeViewModel()
        {
        }

        public ShapeViewModel? SelectedShape
        {
            get { return _selectedShape; }
            set
            {
                if (_selectedShape == value) return;
                _selectedShape = value;
                OnPropertyChanged("SelectedShape");
            }
        }
        void OnPropertyChanged(string propertyName) => PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
}
