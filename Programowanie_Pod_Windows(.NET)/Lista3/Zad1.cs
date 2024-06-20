using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zad1
{
    public interface IClassInfo
    {
        string[] GetFieldNames();
        object GetFieldValue(string fieldName);
    }
    public class XMLGenerator
    {
        public string GenerateXML(IClassInfo dataObject)
        {
            StringBuilder sb = new StringBuilder();
            
            string[] fieldNames = dataObject.GetFieldNames();
            for(int i=0; i<fieldNames.Length; i++)
            {
                string fieldName = fieldNames[i];
                sb.Append("<");
                sb.Append(fieldName);
                sb.Append(">");
                sb.Append(dataObject.GetFieldValue(fieldName));
                sb.Append("</");
                sb.Append(fieldName);
                sb.Append(">\n");
            }
            return sb.ToString();
        }
    }
    public class Person : IClassInfo
    {
        public string Name { get; set; }
        public string Surname { get; set; }
        public string[] GetFieldNames()
        {
            return new[] { "Name", "Surname" };
        }
        public object GetFieldValue(string fieldName)
        {
            switch (fieldName)
            {
                case "Name":
                    return this.Name;
                case "Surname":
                    return this.Surname;
                default:
                    return null;
            }
            throw new NotImplementedException();
        }

    }


    internal class Program
    {
        static void Main(string[] args)
        {
            Person person = new Person(){
                Name = "Jan",
                Surname = "Kowalski"
            };
            XMLGenerator generator = new XMLGenerator();
            string xml = generator.GenerateXML(person);
            Console.WriteLine(xml);
            Console.ReadLine();
        }
    }
}
