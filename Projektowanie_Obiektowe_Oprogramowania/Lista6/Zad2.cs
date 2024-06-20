using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zad2
{
    internal class Program
    {
        public class Context
        {
            private Dictionary<string, bool> _variables = new Dictionary<string, bool>();

            public bool GetValue(string VariableName)
            {
                if (_variables.ContainsKey(VariableName))
                    return _variables[VariableName];
                else
                    throw new ArgumentException("Variable '{0}' undefined", VariableName);
            }

            public void SetValue(string VariableName, bool Value)
            {
                if (_variables.ContainsKey(VariableName))
                    _variables[VariableName] = Value;
                else
                    _variables.Add(VariableName, Value);
            }
        }

        public abstract class AbstractExpression
        {
            public abstract bool Interpret(Context context);
        }

        public class ConstExpression : AbstractExpression
        {
            public string const_expression;

            public ConstExpression(string constExpression) { 
                this.const_expression = constExpression; 
            }

            public override bool Interpret(Context context)
            {
                switch (const_expression)
                {
                    case "true":
                        return true;
                    case "false":
                        return false;
                    default:
                        return context.GetValue(const_expression);
                }
            }
        }

        public class BinaryExpression : AbstractExpression
        {
            public AbstractExpression Left;
            public AbstractExpression Right;
            public string Operator;

            public BinaryExpression(string Operator, AbstractExpression Left, AbstractExpression Right)
            {
                this.Operator = Operator;
                this.Left = Left;
                this.Right = Right;
            }
            public override bool Interpret(Context context)
            {
                switch (Operator)
                {
                    case "||":
                        return Left.Interpret(context) || Right.Interpret(context);
                    case "&&":
                        return Left.Interpret(context) && Right.Interpret(context);
                    default:
                        throw new ArgumentException("Unknown operator");
                }
            }
        }

        public class UnaryExpression : AbstractExpression
        {
            public AbstractExpression Expression;
            public string Operator;

            public UnaryExpression(string Operator, AbstractExpression Expression)
            {
                this.Operator = Operator;
                this.Expression = Expression;
            }
            public override bool Interpret(Context context)
            {
                switch (Operator)
                {
                    case "!":
                        return !this.Expression.Interpret(context);
                    default:
                        throw new ArgumentException("Unknown operator");
                }
            }
        }
        static void Main(string[] args)
        {
            Context ctx = new Context();
            ctx.SetValue("x", false);
            ctx.SetValue("y", true);
            AbstractExpression exp = new BinaryExpression(
                "&&",
                new BinaryExpression(
                    "||",
                    new ConstExpression("y"),
                    new ConstExpression("false")),
                new BinaryExpression(
                    "&&",
                    new UnaryExpression(
                        "!",
                        new ConstExpression("x")),
                    new ConstExpression("true")));
            //  (y || false) && (!x && true)
            bool Value = exp.Interpret(ctx);
            Console.WriteLine(Value);
            Console.ReadLine();
        }
    }
}
