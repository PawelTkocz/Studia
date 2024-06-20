using System;
using System.Collections.Generic;
using System.Dynamic;
using System.Linq;
using System.Linq.Expressions;
using System.Text;
using System.Threading.Tasks;

namespace Zad2
{
    public class MyDynamicClass : DynamicObject
    {
        Dictionary<string, object> dictionary = new Dictionary<string, object>();
        public override bool TrySetMember(SetMemberBinder binder, object value)
        {
            dictionary[binder.Name.ToLower()] = value;
            return true;
        }
        public override bool TryGetMember(GetMemberBinder binder, out object result)
        {
            string name = binder.Name.ToLower();
            return dictionary.TryGetValue(name, out result);
        }

        public override bool TrySetIndex(SetIndexBinder binder, object[] indexes, object value)
        {
            int index = (int)indexes[0];

            if (dictionary.ContainsKey("Property" + index))
                dictionary["Property" + index] = value;
            else
                dictionary.Add("Property" + index, value);
            return true;
        }

        public override bool TryGetIndex(GetIndexBinder binder, object[] indexes, out object result)
        {
            int index = (int)indexes[0];
            return dictionary.TryGetValue("Property" + index, out result);
        }

        public override bool TryInvoke(InvokeBinder binder, object[] args, out object result)
        {
            if((args.Length == 2) && (args[0].GetType() == typeof(int)) && (args[1].GetType() == typeof(String)))
            {
                Console.WriteLine("New <int, string> pair: <{0}, {1}>", args[0], args[1]);
                result = (int)args[0]+1;
                return true;
            }
            return base.TryInvoke(binder, args, out result);
        }
        public override bool TryInvokeMember(InvokeMemberBinder binder, object[] args, out object result)
        {
            if(binder.Name == "Foo")
            {
                result = (int)args[0] + (int)args[1] - (int)args[2];
                return true;
            }
            else if(binder.Name == "Bar")
            {
                result = (string)args[1] + (string)args[2];
                return true;
            }

            return base.TryInvokeMember(binder, args, out result);
        }

        public override bool TryUnaryOperation(UnaryOperationBinder binder, out object result)
        {
            if(binder.Operation != ExpressionType.Negate)
            {
                Console.WriteLine(binder.Operation + ": This unary operation is not implemented");
                result = null;
                return false;
            }
            result = 143;
            return true;
        }

        public override bool TryBinaryOperation(BinaryOperationBinder binder, object arg, out object result)
        {
            if (binder.Operation != ExpressionType.Add)
            {
                Console.WriteLine(binder.Operation + ": This unary operation is not implemented");
                result = null;
                return false;
            }

            dynamic res = new MyDynamicClass();
            res.ResultOfBinaryAdd = (int)((MyDynamicClass)arg).dictionary["addarg"] + (int)(dictionary["addarg"]);
            result = res;
            return true;
        }
    }
    internal class Program
    {
        static void Main(string[] args)
        {
            dynamic e = new MyDynamicClass();

            //TrySetMember()
            e.MyDynamicProp1 = "DynamicProp1Value";
            e.MyDynamicProp2 = 14;
            //TryGetMember()
            Console.WriteLine("{0}, {1}", e.MyDynamicProp1, e.MyDynamicProp2);

            //TrySetIndex()
            e[0] = 10;
            e[3] = 11;
            //TryGetIndex()
            Console.WriteLine("{0} {1}", e[0], e[3]);

            //TryInvoke()
            e(5, "dogs");
            //TryInvokeMember()
            Console.WriteLine(e.Foo(4, 9, 1));
            Console.WriteLine(e.Bar("mam", "dwa", "koty", 3));

            //TryUnaryOperation()
            Console.WriteLine(-e);
            //TryBinaryOperation()
            e.addArg = 11;
            dynamic f = new MyDynamicClass();
            f.addArg = 12;
            dynamic g = new MyDynamicClass();
            g = e + f;
            Console.WriteLine(g.ResultOfBinaryAdd);

            Console.ReadLine();
        }
    }
}
