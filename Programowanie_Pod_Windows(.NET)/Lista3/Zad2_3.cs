using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace Zad2_3
{
    [AttributeUsage(AttributeTargets.Field)]
    public class IgnoreInXML : Attribute
    {

    }
    public class Person
    {
        public string Name;
        public string Surname;
        [IgnoreInXML]
        public int Age;
    }

    public class XMLGenerator
    {
        public string GenerateXML(object dataObject)
        {
            StringBuilder sb = new StringBuilder();

            Type t = dataObject.GetType();
            FieldInfo[] fieldNames = t.GetFields();
            for (int i = 0; i < fieldNames.Length; i++)
            {
                FieldInfo fieldInfo = fieldNames[i];

                IgnoreInXML ignore_xml = fieldInfo.GetCustomAttribute(typeof(IgnoreInXML)) as IgnoreInXML;
                if(ignore_xml == null)
                {
                    string fieldName = fieldNames[i].Name;
                    sb.Append("<");
                    sb.Append(fieldName);
                    sb.Append(">");
                    sb.Append(fieldInfo.GetValue(dataObject));
                    sb.Append("</");
                    sb.Append(fieldName);
                    sb.Append(">\n");
                }

            }
            return sb.ToString();
        }
    }
    internal class Program
    {
        static void Main(string[] args)
        {
            Person person = new Person(){
                Name = "Jan",
                Surname = "Kowalski",
                Age = 19
            };
            XMLGenerator generator = new XMLGenerator();
            string xml = generator.GenerateXML(person);
            Console.WriteLine(xml);
            Console.ReadLine();
        }
    }
}
