using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Web;

namespace Zad1
{
    /// <summary>
    /// Summary description for Handler1
    /// </summary>
    public class Handler1 : IHttpHandler
    {

        public void ProcessRequest(HttpContext context)
        {
            context.Response.Write("Treść żądania: " + context.Request.RequestContext);   
            context.Response.AppendHeader("Content-type", "text/html");
            context.Response.Write("Adres bieżącego żądania: " + context.Request.Url + "<br />");
            context.Response.Write("Nagłówki HTTP: <br />");
            foreach (var key in context.Request.Headers.AllKeys)
                context.Response.Write(key + ": " + context.Request.Headers.Get(key) + "<br />");
            context.Response.Write("Rodzaj żądania: " + context.Request.HttpMethod + "<br />");

            var bodyReader = new StreamReader(context.Request.InputStream);
            context.Response.Write("Treść: " + bodyReader.ReadToEnd() + "<br />");

            context.Response.End();

        }

        public bool IsReusable
        {
            get
            {
                return false;
            }
        }
    }
}