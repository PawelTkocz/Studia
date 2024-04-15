using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace Zadanie4
{
    public partial class start : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void SubmitForm(object sender, EventArgs e)
        {
            string query_string = "print.aspx";
            query_string += "?FirstName=";
            query_string += FirstName.Text;
            query_string += "&LastName=";
            query_string += LastName.Text;
            query_string += "&ClassName=";
            query_string += ClassName.Text;
            query_string += "&ListNumber=";

            if (ListNumber.Text == "")
                query_string += "0";
            else
                query_string += ListNumber.Text;
    
            query_string += "&Date=";
            query_string += Date.SelectedDate.ToShortDateString();

            TextBox[] tasks = { Zad1, Zad2, Zad3, Zad4, Zad5, Zad6, Zad7, Zad8, Zad9, Zad10 };
            for(int i=1; i<=10; i++)
            {
                query_string += "&Zad" + i.ToString() + "=";
                if (tasks[i - 1].Text == "")
                    query_string += 0.ToString();
                else
                    query_string += tasks[i-1].Text;
            }
            Response.Redirect(query_string);
        }
    }
}