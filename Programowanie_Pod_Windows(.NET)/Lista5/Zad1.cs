using BenchmarkDotNet.Attributes;
using BenchmarkDotNet.Jobs;
using BenchmarkDotNet.Running;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zad1
{
    /*
    Operacje na typach dynamicznych są wykonywane w zależności od tego jakiego rzeczywistego typu są argumenty.
    Mając jakieś wyrażanie wykorzystujące dynamiczne typy, kompilator buduje drzewo rozbioru takiego wyrażenia,
    umieszcza w kompilacie takie właśnie abstrakcyjne drzewo rozbioru (z lukami w miejscach, gdzie nie wiadomo jakiego
    typu jest argument operatora, itd.). Kiedy następuje wywołanie z konkretnymi parametrami, system DLR zastępuje wszystkie
    luki w wyrażeniach typami które wnioskuje z kontekstu wywołania. Takie ukonkretnione dla danych typów parametrów drzewo jest
    potem zapamiętywane w cache - jeśli następne wywołanie z dynamicznymi argumetnami będzie tych samych typów, nie będzie konieczności
    tłumaczenia drzewa ponownie. 

    */
    /*
Dla wyrażenia return x+y:

| Method  | x_int | y_int | x_dyn | y_dyn | Mean       | Error     | StdDev    | Median     |
|-------- |------ |------ |------ |------ |-----------:|----------:|----------:|-----------:|
| DoWork1 | 1     | 2     | 1     | 2     |  0.0827 ns | 0.0383 ns | 0.1008 ns |  0.0136 ns |
| DoWork2 | 1     | 2     | 1     | 2     | 10.1477 ns | 0.2259 ns | 0.2113 ns | 10.1581 ns |

Dla wyrażenia return (int)(Math.Sqrt(x) * Math.Sin(y) / Math.Tan(x)):

| Method  | x_int | y_int | x_dyn | y_dyn | Mean      | Error    | StdDev   |
|-------- |------ |------ |------ |------ |----------:|---------:|---------:|
| DoWork1 | 1     | 2     | 1     | 2     |  90.69 ns | 1.778 ns | 1.826 ns |
| DoWork2 | 1     | 2     | 1     | 2     | 179.39 ns | 3.544 ns | 6.995 ns |
    */
    public class DynamicTest
    {
        [Params(1)]
        public int x_int;
        [Params(2)]
        public int y_int;
        [Params(1)]
        public dynamic x_dyn;
        [Params(2)]
        public dynamic y_dyn;

        [Benchmark]
        public int DoWork1()
        {
            int x = x_int;
            int y = y_int;

            return (int)(Math.Sqrt(x) * Math.Sin(y) / Math.Tan(x));
        }

        [Benchmark]
        public dynamic DoWork2()
        {
            dynamic x = x_dyn;
            dynamic y = y_dyn;

            return (int)(Math.Sqrt(x) * Math.Sin(y) / Math.Tan(x));
        }
    }
    internal class Program
    {
        static void Main(string[] args)
        {
            BenchmarkRunner.Run<DynamicTest>();
            Console.ReadLine();
        }
    }
}
