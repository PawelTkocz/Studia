<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="print.aspx.cs" Inherits="Zadanie4b.print" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <table style="width:50%">
      <tr>
        <th><% =Session["firstName"] %></th>
        <th><% =Session["lastName"]%></th>
        <th><% =Session["className"] %></th>
        <th>Lista <% =Session["listNumber"] %></th>
        <th><% =Session["date"] %></th>
      </tr>
      <tr>
        <td style="width:10%">1</td>
        <td style="width:10%">2</td>
        <td style="width:10%">3</td>
        <td style="width:10%">4</td>
        <td style="width:10%">5</td>
        <td style="width:10%">6</td>
        <td style="width:10%">7</td>
        <td style="width:10%">8</td>
        <td style="width:10%">9</td>
        <td style="width:10%">10</td>
      </tr>
      <tr>
        <td><% =Session["Zad1"] %></td>
        <td><% =Session["Zad2"]%></td>
        <td><% =Session["Zad3"] %></td>
        <td><% =Session["Zad4"] %></td>
        <td><% =Session["Zad5"] %></td>
        <td><% =Session["Zad6"] %></td>
        <td><% =Session["Zad7"] %></td>
        <td><% =Session["Zad8"] %></td>
        <td><% =Session["Zad9"] %></td>
        <td><% =Session["Zad10"] %></td>
      </tr>
    </table>
</body>
</html>
