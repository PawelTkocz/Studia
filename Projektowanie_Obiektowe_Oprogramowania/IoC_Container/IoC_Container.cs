using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace Zad1
{
    [AttributeUsage(AttributeTargets.Constructor)]
    public class DependencyConstructor : Attribute
    {

    }

    [AttributeUsage(AttributeTargets.Property)]
    public class DependencyProperty : Attribute
    {

    }
    public class SimpleContainer
    {
        private Dictionary<Type, object> _singletons = new Dictionary<Type, object>();
        private Dictionary<Type, Type> _instanceTypePolicy = new Dictionary<Type, Type>();
        private Dictionary<Type, bool> _instanceSingletonPolicy = new Dictionary<Type, bool>();
        private object _lock = new object();
        public void RegisterType<T>(bool Singleton) where T : class
        {
            Type typeFrom = typeof(T);
            if (typeFrom.IsAbstract)
                throw new Exception("Can't register abstract type.");

            if (_instanceTypePolicy.ContainsKey(typeFrom))
                _instanceSingletonPolicy[typeFrom] = Singleton;
            else
            {
                _instanceTypePolicy.Add(typeFrom, typeFrom);
                _instanceSingletonPolicy.Add(typeFrom, Singleton);
            }
        }
        public void RegisterType<From, To>(bool Singleton) where To : From
        {
            Type typeFrom = typeof(From);
            Type typeTo = typeof(To);
            if (_instanceTypePolicy.ContainsKey(typeFrom))
            {
                _instanceTypePolicy[typeFrom] = typeTo;
                _instanceSingletonPolicy[typeFrom] = Singleton;
            }
            else
            {
                _instanceTypePolicy.Add(typeFrom, typeTo);
                _instanceSingletonPolicy.Add(typeFrom, Singleton);
            }
        }
        private void AddSingleton(Type type, object instance)
        {
            if (!_singletons.ContainsKey(type))
            {
                lock (_lock)
                {
                    if (!_singletons.ContainsKey(type))
                        _singletons.Add(type, instance);
                }
            }
            else
            {
                _singletons[type] = instance;
            }
        }
        public void RegisterInstance<T>(T instance)
        {
            Type type = typeof(T);
            if (_instanceTypePolicy.ContainsKey(type))
            {
                _instanceTypePolicy[type] = type;
                _instanceSingletonPolicy[type] = true;
            }
            else
            {
                _instanceTypePolicy.Add(type, type);
                _instanceSingletonPolicy.Add(type, true);
            }
            AddSingleton(type, instance);
        }    
        private ConstructorInfo FindDependencyConstructor(Type type)
        {
            ConstructorInfo res = null;
            ConstructorInfo[] tab = type.GetConstructors();
            foreach (ConstructorInfo c in tab)
            {
                DependencyConstructor depConst = c.GetCustomAttribute(typeof(DependencyConstructor)) as DependencyConstructor;
                if (depConst != null)
                {
                    if (res == null)
                        res = c;
                    else
                        return null;
                }
            }
            return res;
        }
        private ConstructorInfo FindLongestConstructor(Type type)
        {
            ConstructorInfo[] tab = type.GetConstructors();
            if (tab.Length == 0)
                throw new Exception("No constructors for this type.");
            ConstructorInfo longest = tab[0];
            int max_len = longest.GetParameters().Length;
            int longest_cnt = 0;

            foreach (ConstructorInfo c in tab)
            {
                int c_params_len = c.GetParameters().Length;
                if(c_params_len > max_len)
                {
                    max_len = c_params_len;
                    longest = c;
                    longest_cnt = 1;
                }
                else if(c_params_len == max_len)
                    longest_cnt++;
            }

            if(longest_cnt != 1)
                throw new Exception("More than one possible contructor to resolve.");
            return longest;
        }       
        private ConstructorInfo FindConstructor(Type type)
        {
            ConstructorInfo c = FindDependencyConstructor(type);
            if (c != null)
                return c;
            return FindLongestConstructor(type);
        }
        private void InjectDependencyProperties(Type type, object instance)
        {
            PropertyInfo[] propertyInfos = type.GetProperties();
            foreach (PropertyInfo propertyInfo in propertyInfos)
            {
                DependencyProperty depProp = propertyInfo.GetCustomAttribute(typeof(DependencyProperty)) as DependencyProperty;
                if (depProp != null && propertyInfo.SetMethod.IsPublic)
                    propertyInfo.SetValue(instance, ResolveFromType(propertyInfo.PropertyType, new List<Type>()));
            }
        }
        private object RecursiveCreateInstance(Type type, List<Type> typesList)
        {
            if (typesList.Contains(type))
                throw new Exception("Cycle detected during recursive dependency injection.");

            ConstructorInfo c = FindConstructor(type);
            ParameterInfo[] paramInfo = c.GetParameters();
            object[] parameters = new object[paramInfo.Length];

            typesList.Add(type);
            for (int i = 0; i < paramInfo.Length; i++)
            {
                Type param_type = paramInfo[i].ParameterType;
                parameters[i] = ResolveFromType(param_type, typesList);
            }
            typesList.Remove(type);

            object instance = c.Invoke(parameters);
            InjectDependencyProperties(type, instance);

            return instance;
        }
        private object ResolveFromType(Type typeFrom, List<Type> typesList)
        {
            if (_instanceTypePolicy.ContainsKey(typeFrom))
            {
                Type typeTo = _instanceTypePolicy[typeFrom];
                if (_instanceSingletonPolicy[typeFrom])
                {
                    //tu można zamienić typeTo na typeFrom jeśli chemy, żeby dla różnych
                    //interfejsów/klas abstrakcyjnych były różne singletony tej samej wybranej klasy
                    Type singletonForType = typeTo;
                    if (!_singletons.ContainsKey(singletonForType))
                    {
                        object instance = RecursiveCreateInstance(typeTo, typesList);
                        AddSingleton(singletonForType, instance);
                    }
                    return _singletons[singletonForType];
                }
                return RecursiveCreateInstance(typeTo, typesList);
            }

            if (typeFrom.IsAbstract)
                throw new Exception("Can't resolve abstract type, which wasn't previously registered.");
            return RecursiveCreateInstance(typeFrom, typesList);
        }

        public void BuildUp<T>(T Instance)
        {
            InjectDependencyProperties(typeof(T), Instance);
        }
        public T Resolve<T>()
        {
            Type typeFrom = typeof(T);
            return (T)ResolveFromType(typeFrom, new List<Type>());
        }
    }

    internal class Program
    {
        static void Main(string[] args)
        {
        }
    }
}
