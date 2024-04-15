using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace Zadanie4
{
    public partial class print : System.Web.UI.Page
    {
        public string firstName;
        public string lastName;
        public string className;
        public string listNumber;
        public string date;
        public int[] tasks = new int[10];
        protected void Page_Load(object sender, EventArgs e)
        {
            firstName = Request.QueryString["FirstName"];
            lastName = Request.QueryString["LastName"];
            className = Request.QueryString["ClassName"];
            listNumber = Request.QueryString["ListNumber"];
            date = Request.QueryString["Date"];
            for(int i=1; i<=10; i++)
            {
                tasks[i-1] = Int32.Parse(Request.QueryString["Zad" + i]);
            }
        }
    }
}