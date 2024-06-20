using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zad2
{
    public class ReportPrinterBefore
    {
        public string data;
        public string GetData()
        {
            Console.WriteLine("Getting data process");
            data = Console.ReadLine();
            return data;
        }

        public void FormatDocument() { 
            Console.WriteLine("Formatting document process");
            this.data = data.ToUpper();
        }
        public void PrintReport()
        {
            GetData();
            FormatDocument();
            Console.WriteLine("Printing report process");
            Console.WriteLine(data);
        }
    }

    public class MakeReport
    {
        public void PrepareReport()
        {
            DataReceiver dataReceiver = new DataReceiver();
            string data = dataReceiver.GetData();

            DocumentFormatter documentFormatter = new DocumentFormatter();
            data = documentFormatter.FormatDocument(data);

            ReportPrinterAfter reportPrinterAfter = new ReportPrinterAfter();
            reportPrinterAfter.PrintReport(data);
        }
    }

    public class ReportPrinterAfter
    {
        public void PrintReport(string data)
        {
            Console.WriteLine("Printing report process");
            Console.WriteLine(data);
        }
    }

    public class DataReceiver
    {
        public string GetData()
        {
            Console.WriteLine("Receiving data process");
            string data = Console.ReadLine();
            return data;
        }
    }

    public class DocumentFormatter
    {
        public string FormatDocument(string document)
        {
            Console.WriteLine("Formatting document process");
            return document.ToUpper();
        }
    }

    internal class Program
    {
        static void Main(string[] args)
        {
            ReportPrinterBefore firstPrinter = new ReportPrinterBefore();
            MakeReport makeReport = new MakeReport();

            firstPrinter.PrintReport();
            Console.WriteLine();
            makeReport.PrepareReport();
            Console.ReadLine();
        }
    }
}
