<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="start.aspx.cs" Inherits="Zadanie4b.start" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
        <asp:Table ID="Table" runat="server">
            <asp:TableRow runat="server">  
                <asp:TableCell runat="server">Imię</asp:TableCell>  
                <asp:TableCell runat="server">
                    <asp:TextBox ID="FirstName" runat="server"></asp:TextBox>
                </asp:TableCell>                 
            </asp:TableRow>  
            <asp:TableRow runat="server">  
                <asp:TableCell runat="server">Nazwisko</asp:TableCell> 
                <asp:TableCell runat="server">
                    <asp:TextBox ID="LastName" runat="server"></asp:TextBox>
                </asp:TableCell>  
            </asp:TableRow>  
            <asp:TableRow runat="server">  
                <asp:TableCell runat="server">Nazwa zajęć</asp:TableCell>
                <asp:TableCell runat="server">
                    <asp:TextBox ID="ClassName" runat="server"></asp:TextBox>
                </asp:TableCell> 
            </asp:TableRow>  
            <asp:TableRow runat="server">  
                <asp:TableCell runat="server">Numer Zestawu</asp:TableCell>  
                <asp:TableCell runat="server">
                    <asp:TextBox ID="ListNumber" runat="server"></asp:TextBox>
                    <asp:TableCell runat="server"><asp:RegularExpressionValidator ID="Validator0" ControlToValidate="ListNumber" runat="server" ErrorMessage="Podaj liczbę naturalną" ValidationExpression="\d+"></asp:RegularExpressionValidator></asp:TableCell>
                </asp:TableCell> 
            </asp:TableRow>  
            <asp:TableRow runat="server">  
                <asp:TableCell runat="server">Data</asp:TableCell>  
                <asp:TableCell runat="server"><asp:Calendar ID="Date" runat="server"></asp:Calendar></asp:TableCell> 
            </asp:TableRow>
            <asp:TableRow runat="server">  
                <asp:TableCell runat="server">Zadanie</asp:TableCell>  
                <asp:TableCell runat="server">Punkty</asp:TableCell> 
            </asp:TableRow>
            <asp:TableRow runat="server">  
                <asp:TableCell runat="server">1</asp:TableCell>  
                <asp:TableCell runat="server"><asp:TextBox ID="Zad1" runat="server"></asp:TextBox></asp:TableCell> 
                <asp:TableCell runat="server"><asp:RegularExpressionValidator ID="Validator1" ControlToValidate="Zad1" runat="server" ErrorMessage="Podaj liczbę naturalną lub pozostaw puste pole" ValidationExpression="\d+"></asp:RegularExpressionValidator></asp:TableCell>
            </asp:TableRow>
            <asp:TableRow runat="server">  
                <asp:TableCell runat="server">2</asp:TableCell>  
                <asp:TableCell runat="server"><asp:TextBox ID="Zad2" runat="server"></asp:TextBox></asp:TableCell>
                <asp:TableCell runat="server"><asp:RegularExpressionValidator ID="Validator2" ControlToValidate="Zad2" runat="server" ErrorMessage="Podaj liczbę naturalną lub pozostaw puste pole" ValidationExpression="\d+"></asp:RegularExpressionValidator></asp:TableCell>
            </asp:TableRow>
            <asp:TableRow runat="server">  
                <asp:TableCell runat="server">3</asp:TableCell>  
                <asp:TableCell runat="server"><asp:TextBox ID="Zad3" runat="server"></asp:TextBox></asp:TableCell> 
                <asp:TableCell runat="server"><asp:RegularExpressionValidator ID="Validator3" ControlToValidate="Zad3" runat="server" ErrorMessage="Podaj liczbę naturalną lub pozostaw puste pole" ValidationExpression="\d+"></asp:RegularExpressionValidator></asp:TableCell>
            </asp:TableRow>
            <asp:TableRow runat="server">  
                <asp:TableCell runat="server">4</asp:TableCell>  
                <asp:TableCell runat="server"><asp:TextBox ID="Zad4" runat="server"></asp:TextBox></asp:TableCell>
                <asp:TableCell runat="server"><asp:RegularExpressionValidator ID="Validator4" ControlToValidate="Zad4" runat="server" ErrorMessage="Podaj liczbę naturalną lub pozostaw puste pole" ValidationExpression="\d+"></asp:RegularExpressionValidator></asp:TableCell>
            </asp:TableRow>
            <asp:TableRow runat="server">  
                <asp:TableCell runat="server">5</asp:TableCell>  
                <asp:TableCell runat="server"><asp:TextBox ID="Zad5" runat="server"></asp:TextBox></asp:TableCell> 
                <asp:TableCell runat="server"><asp:RegularExpressionValidator ID="Validator5" ControlToValidate="Zad5" runat="server" ErrorMessage="Podaj liczbę naturalną lub pozostaw puste pole" ValidationExpression="\d+"></asp:RegularExpressionValidator></asp:TableCell>
            </asp:TableRow>
            <asp:TableRow runat="server">  
                <asp:TableCell runat="server">6</asp:TableCell>  
                <asp:TableCell runat="server"><asp:TextBox ID="Zad6" runat="server"></asp:TextBox></asp:TableCell> 
                <asp:TableCell runat="server"><asp:RegularExpressionValidator ID="Validator6" ControlToValidate="Zad6" runat="server" ErrorMessage="Podaj liczbę naturalną lub pozostaw puste pole" ValidationExpression="\d+"></asp:RegularExpressionValidator></asp:TableCell>
            </asp:TableRow>
            <asp:TableRow runat="server">  
                <asp:TableCell runat="server">7</asp:TableCell>  
                <asp:TableCell runat="server"><asp:TextBox ID="Zad7" runat="server"></asp:TextBox></asp:TableCell> 
                <asp:TableCell runat="server"><asp:RegularExpressionValidator ID="Validator7" ControlToValidate="Zad7" runat="server" ErrorMessage="Podaj liczbę naturalną lub pozostaw puste pole" ValidationExpression="\d+"></asp:RegularExpressionValidator></asp:TableCell>
            </asp:TableRow>
            <asp:TableRow runat="server">  
                <asp:TableCell runat="server">8</asp:TableCell>  
                <asp:TableCell runat="server"><asp:TextBox ID="Zad8" runat="server"></asp:TextBox></asp:TableCell> 
                <asp:TableCell runat="server"><asp:RegularExpressionValidator ID="Validator8" ControlToValidate="Zad8" runat="server" ErrorMessage="Podaj liczbę naturalną lub pozostaw puste pole" ValidationExpression="\d+"></asp:RegularExpressionValidator></asp:TableCell>
            </asp:TableRow>
            <asp:TableRow runat="server">  
                <asp:TableCell runat="server">9</asp:TableCell>  
                <asp:TableCell runat="server"><asp:TextBox ID="Zad9" runat="server"></asp:TextBox></asp:TableCell> 
                <asp:TableCell runat="server"><asp:RegularExpressionValidator ID="Validator9" ControlToValidate="Zad9" runat="server" ErrorMessage="Podaj liczbę naturalną lub pozostaw puste pole" ValidationExpression="\d+"></asp:RegularExpressionValidator></asp:TableCell>
            </asp:TableRow>
            <asp:TableRow runat="server">  
                <asp:TableCell runat="server">10</asp:TableCell>  
                <asp:TableCell runat="server"><asp:TextBox ID="Zad10" runat="server"></asp:TextBox></asp:TableCell>
                <asp:TableCell runat="server"><asp:RegularExpressionValidator ID="Validator10" ControlToValidate="Zad10" runat="server" ErrorMessage="Podaj liczbę naturalną lub pozostaw puste pole" ValidationExpression="\d+"></asp:RegularExpressionValidator></asp:TableCell>
            </asp:TableRow>
            <asp:TableRow runat="server">   
                <asp:TableCell runat="server"><asp:Button ID="Submit" runat="server" Text="Zatwierdź" OnClick="SubmitForm" /></asp:TableCell> 
            </asp:TableRow>
        </asp:Table>
    </form>
</body>
</html>
