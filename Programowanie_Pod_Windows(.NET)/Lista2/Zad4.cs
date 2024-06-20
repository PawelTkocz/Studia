using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zad4
{
    public delegate void HandleChangeProperty(object source, string propertyName, object propertyValue);
    internal class Person
    {
        public event HandleChangeProperty PropertyValueChanged;

        private string name;
        private string surname;
        public string Name {
            get
            {
                return name;
            }
            set
            {
                if (this.PropertyValueChanged != null)
                {
                    this.PropertyValueChanged(this, "Name", value);
                }
                name = value;
            }
        }
        public string Surname {
            get
            {
                return surname;
            }
            set
            {
                if (this.PropertyValueChanged != null && surname != value)
                {
                    this.PropertyValueChanged(this, "Surname", value);
                }
                surname = value;
            }
        }

        private static void Person_PropertyValueChanged(object source, string propertyName, object propertyValue)
        {
            Console.WriteLine("właściwość {0}, nowa wartość {1}", propertyName, propertyValue);
        }
        static void Main(string[] args)
        {
            Person person = new Person();
            person.PropertyValueChanged += Person.Person_PropertyValueChanged;
            person.Name = "Jan";
            person.Surname = "Kowalski";
            person.Name = "Kuba";
            person.Surname = "Kowalski";
            person.Name = "Kuba";
            Console.ReadLine();
        }
    }
}
