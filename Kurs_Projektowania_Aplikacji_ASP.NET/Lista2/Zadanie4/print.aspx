<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="print.aspx.cs" Inherits="Zadanie4.print" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <table style="width:50%">
      <tr>
        <th><% =firstName %></th>
        <th><% =lastName %></th>
        <th><% =className %></th>
        <th>Lista <% =listNumber %></th>
        <th><% =date %></th>
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
        <td><% =tasks[0] %></td>
        <td><% =tasks[1] %></td>
        <td><% =tasks[2] %></td>
        <td><% =tasks[3] %></td>
        <td><% =tasks[4] %></td>
        <td><% =tasks[5] %></td>
        <td><% =tasks[6] %></td>
        <td><% =tasks[7] %></td>
        <td><% =tasks[8] %></td>
        <td><% =tasks[9] %></td>
      </tr>
    </table>
</body>
</html>
