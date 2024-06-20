using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zad3
{

    public class BetterReusable
    {
        private Reusable _reusable;
        private bool _released;
        public BetterReusable()
        {
            _reusable = ObjectPool.Instance().AcquireReusable();
            _released = false;
        }

        public void Release()
        {
           ObjectPool.Instance().ReleaseReusable(_reusable);
            _released = true;
        }

        public int DoWork()
        {
            if(!_released)
                return _reusable.DoWork();
            else
                throw new ArgumentException();
        }
    }
    public class Reusable
    {
        public int DoWork()
        {
            return 5;
        }
    }
    public class ObjectPool
    {
        private static ObjectPool _instance;
        public static ObjectPool Instance()
        {
            if(_instance == null)
            {
                _instance = new ObjectPool(5);
            }
            return _instance;
        }

        private int _capacity;
        private List<Reusable> ready = new List<Reusable>();
        private List<Reusable> released = new List<Reusable>();
        public ObjectPool(int capacity)
        {
            if(capacity <= 0)
            {
                throw new ArgumentException();
            }
            this._capacity = capacity;
        }
        public Reusable AcquireReusable()
        {
            if(released.Count == this._capacity)
            {
                throw new ArgumentException();
            }

            if(ready.Count == 0)
            {
                Reusable newReusable = new Reusable();
                ready.Add(newReusable);
            }
            var reusable = ready[0];
            ready.Remove(reusable);
            released.Add(reusable);
            return reusable;
        }

        public void ReleaseReusable(Reusable reusable)
        {
            if (!released.Contains(reusable))
            {
                throw new ArgumentException();  
            }
            released.Remove(reusable);
            ready.Add(reusable);
        }
    }
    internal class Program
    {
        static void Main(string[] args)
        {
            var reusable0 = new BetterReusable();
            int five = reusable0.DoWork();

            var res = ObjectPool.Instance().AcquireReusable();
            res.DoWork();
            ObjectPool.Instance().ReleaseReusable(res);

            var reusable = new BetterReusable();
            reusable.DoWork();
            reusable.Release();

            Console.ReadLine();
                    
        }
    }
}
