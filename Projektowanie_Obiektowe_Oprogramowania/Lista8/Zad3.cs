using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace Zad3
{
    public abstract class DataAccessHandler
    {
        public abstract void ConnectToData();
        public abstract void GetData();
        public abstract void ProcessData();
        public abstract void CloseConnection();

        public void Execute()
        {
            ConnectToData();
            GetData();
            ProcessData();
            CloseConnection();
        }
    }

    public class DatabaseDataAccessHandler : DataAccessHandler
    {
        public string databasePath;
        public string column;
        FileStream fs;
        List<string> lines;

        public DatabaseDataAccessHandler(string databasePath, string column)
        {
            this.databasePath = databasePath;
            this.column = column;
        }

        public override void ConnectToData()
        {
            this.fs = File.Open(this.databasePath, FileMode.Open);
        }

        public override void GetData()
        {
            this.lines = new List<string>();
            const Int32 BufferSize = 128;
            using (var streamReader = new StreamReader(this.fs, Encoding.UTF8, true, BufferSize))
            {
                string line;
                while ((line = streamReader.ReadLine()) != null)
                        this.lines.Add(line);
            }
        }

        public override void ProcessData()
        {
            string[] headers = this.lines[0].Split(' ');
            int colNum = Array.FindIndex(headers, h => h == this.column);
            if (colNum == -1)
                Console.WriteLine("No column named {0}", this.column);
            else
            {
                int sum = 0;
                foreach (string line in this.lines.Skip(1))
                    sum += Int32.Parse(line.Split(' ')[colNum]);
                Console.WriteLine(sum);
            }
        }

        public override void CloseConnection()
        {
            this.fs.Close();
        }
    }

    public class XmlDataAccessHandler : DataAccessHandler
    {
        public string filePath;
        private XmlDocument doc = null;

        public XmlDataAccessHandler(string filePath)
        {
            this.filePath = filePath;
        }

        public override void ConnectToData() {}

        public override void GetData()
        {
            this.doc = new XmlDocument();
            this.doc.Load(this.filePath);
        }

        public string FindLongestNodeName(XmlNodeList nodes)
        {
            string longest = "";

            foreach (XmlNode node in nodes)
            {
                if (longest.Length < node.Name.Length)
                    longest = node.Name;

                string childLongest = FindLongestNodeName(node.ChildNodes);
                if (longest.Length < childLongest.Length)
                    longest = childLongest;
            }

            return longest;
        }

        public override void ProcessData()
        {
            XmlNodeList nodes = this.doc.DocumentElement.ChildNodes;
            string longest = FindLongestNodeName(nodes);
            Console.WriteLine("Longest node is \"{0}\"", longest);
        }

        public override void CloseConnection() { }
    }

    internal class Program
    {
        static void Main(string[] args)
        {
            XmlDataAccessHandler h1 = new XmlDataAccessHandler("test.xml");
            h1.Execute();

            DatabaseDataAccessHandler h2 = new DatabaseDataAccessHandler("database.txt", "Column2");
            h2.Execute();
            Console.ReadLine();
        }
    }
}
