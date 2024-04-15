using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace Zadanie4b
{
    public partial class start : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                //strona w wypadku otrzymania żądania POST
                /*
                Sposób na odczytanie parametrów przesłanych przez POST
                string[] keys = Request.Form.AllKeys;
                for (int i = 0; i < keys.Length; i++)
                    Response.Write(keys[i] + ": " + Request.Form[keys[i]] + "<br>");
                */
            }
            else
            {
                //strona w wypadku otrzymania żądania GET
                /*
                 Sposób na odczytanie parametrów przesłanych przez GET
                exampleVar = Request.QueryString["ExampleVar"];
                */
            }
        }

        protected void SubmitForm(object sender, EventArgs e)
        {
            Session["FirstName"] = FirstName.Text;
            Session["LastName"] = LastName.Text;
            Session["ClassName"] = ClassName.Text;

            if(ListNumber.Text == "")
                Session["ListNumber"] = "0";
            else
                Session["ListNumber"] = ListNumber.Text;

            Session["Date"] = Date.SelectedDate.ToShortDateString();
     

            TextBox[] tasks = { Zad1, Zad2, Zad3, Zad4, Zad5, Zad6, Zad7, Zad8, Zad9, Zad10 };
            for (int i = 1; i <= 10; i++)
            {
                int val = 0;   
                if (tasks[i - 1].Text != "")
                    val = Int32.Parse(tasks[i - 1].Text);
                Session["Zad" + i.ToString()] = val;
            }
            Response.Redirect("print.aspx");
        }
    }
}