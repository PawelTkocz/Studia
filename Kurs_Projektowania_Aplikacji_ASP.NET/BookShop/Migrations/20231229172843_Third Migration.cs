using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace BookShop.Migrations
{
    public partial class ThirdMigration : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.RenameColumn(
                name: "number",
                table: "OrderedBooksTable",
                newName: "Number");

            migrationBuilder.RenameColumn(
                name: "BookId",
                table: "BookTable",
                newName: "Id");

            migrationBuilder.AddColumn<double>(
                name: "Price",
                table: "BookTable",
                type: "float",
                nullable: false,
                defaultValue: 0.0);
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropColumn(
                name: "Price",
                table: "BookTable");

            migrationBuilder.RenameColumn(
                name: "Number",
                table: "OrderedBooksTable",
                newName: "number");

            migrationBuilder.RenameColumn(
                name: "Id",
                table: "BookTable",
                newName: "BookId");
        }
    }
}
