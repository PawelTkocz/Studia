using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace Zad4
{
    public interface IDataAccessStrategy
    {
        void ConnectToData();
        void GetData();
        void ProcessData();
        void CloseConnection();
    }
    public class DataAccessHandler
    {
        private IDataAccessStrategy _dataAccessStrategy;

        public DataAccessHandler(IDataAccessStrategy dataAccessStrategy)
        {
            this._dataAccessStrategy = dataAccessStrategy;
        }

        public void Execute()
        {
            this._dataAccessStrategy.ConnectToData();
            this._dataAccessStrategy.GetData();
            this._dataAccessStrategy.ProcessData();
            this._dataAccessStrategy.CloseConnection();
        }
    }

    public class DatabaseDataAccessStrategy : IDataAccessStrategy
    {
        public string databasePath;
        public string column;
        FileStream fs;
        List<string> lines;

        public DatabaseDataAccessStrategy(string databasePath, string column)
        {
            this.databasePath = databasePath;
            this.column = column;
        }

        public void ConnectToData()
        {
            this.fs = File.Open(this.databasePath, FileMode.Open);
        }

        public void GetData()
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

        public void ProcessData()
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

        public void CloseConnection()
        {
            this.fs.Close();
        }
    }

    public class XmlDataAccessStrategy : IDataAccessStrategy
    {
        public string filePath;
        private XmlDocument doc = null;

        public XmlDataAccessStrategy(string filePath)
        {
            this.filePath = filePath;
        }

        public void ConnectToData() { }

        public void GetData()
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

        public void ProcessData()
        {
            XmlNodeList nodes = this.doc.DocumentElement.ChildNodes;
            string longest = FindLongestNodeName(nodes);
            Console.WriteLine("Longest node is \"{0}\"", longest);
        }

        public void CloseConnection() { }
    }

    internal class Program
    {
        static void Main(string[] args)
        {
            DataAccessHandler h1 = new DataAccessHandler(new XmlDataAccessStrategy("test.xml"));
            h1.Execute();

            DataAccessHandler h2 = new DataAccessHandler(new DatabaseDataAccessStrategy("database.txt", "Column2"));
            h2.Execute();
            Console.ReadLine();
        }
    }
}
