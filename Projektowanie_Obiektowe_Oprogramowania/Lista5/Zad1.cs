using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Mail;
using System.Text;
using System.Threading.Tasks;

namespace Zad1
{
    public class SmtpFacade
    {
        public void Send(string From, string To, string Subject, string Body, Stream Attachment, string AttachmentMimeType)
        {
            MailMessage mailMessage = new MailMessage(From, To, Subject, Body);
            if (Attachment != null)
                mailMessage.Attachments.Add(new Attachment(Attachment, AttachmentMimeType));

            SmtpClient client = new SmtpClient("smtp.poczta.onet.pl")
            {
                Credentials = new NetworkCredential("kamil.kowalski@op.pl", "secretPassword123"),
                EnableSsl = true
            };

            try
            {
                client.Send(mailMessage);
            }
            catch (Exception exception)
            {
                Console.WriteLine(exception);
            }
        }
    }
    internal class Program
    {
        static void Main(string[] args)
        {
            SmtpFacade smtpFacade = new SmtpFacade();
            FileStream fs = File.Create("file.txt");
            smtpFacade.Send("kamil.kowalski@op.pl", "jakub.kowalski@op.pl", "New mail", "Hello World", fs, "text/plain");
            Console.ReadLine();
        }
    }
}
