using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Version1
{
    public class Person { }

    public abstract class PersonRegistry
    {
        protected PersonNotifier notifier;
        public PersonRegistry(PersonNotifier personNotifier)
        {
            notifier = personNotifier;
        }
        public abstract IEnumerable<Person> GetPersons();

        public void NotifyPersons()
        {
            this.notifier.NotifyPersons(this.GetPersons());
        }
    }

    public class XmlPersonRegistry : PersonRegistry
    {
        public XmlPersonRegistry(PersonNotifier personNotifier) : base(personNotifier)
        {
        }

        public override IEnumerable<Person> GetPersons()
        {
            //read Persons from XML file
            throw new NotImplementedException();
        }
    }
    public class DataBasePersonRegistry : PersonRegistry
    {
        public DataBasePersonRegistry(PersonNotifier personNotifier) : base(personNotifier)
        {
        }

        public override IEnumerable<Person> GetPersons()
        {
            //read Persons from database
            throw new NotImplementedException();
        }
    }

    public abstract class PersonNotifier
    {
        public abstract void NotifyPersons(IEnumerable<Person> persons);
    }

    public class MailPersonNotifier : PersonNotifier
    {
        public override void NotifyPersons(IEnumerable<Person> persons)
        {
            //notify via Email
            throw new NotImplementedException();
        }
    }
    public class SMSPersonNotifier : PersonNotifier
    {
        public override void NotifyPersons(IEnumerable<Person> persons)
        {
            //notify via SMS
            throw new NotImplementedException();
        }
    }
}

namespace Version2
{
    public class Person { }

    public abstract class PersonNotifier
    {
        protected PersonGetter personGetter;
        public PersonNotifier(PersonGetter personGetter)
        {
            this.personGetter = personGetter;
        }
        public abstract void NotifyPersons(IEnumerable<Person> persons);

        public void NotifyPersons()
        {
            NotifyPersons(GetPersons());
        }

        public IEnumerable<Person> GetPersons()
        {
            return this.personGetter.GetPersons();
        }
    }

    public class EmailPersonNotifier : PersonNotifier
    {
        public EmailPersonNotifier(PersonGetter personGetter) : base(personGetter)
        {
        }
        public override void NotifyPersons(IEnumerable<Person> persons)
        {
            //notify persons via Email
            throw new NotImplementedException();
        }
    }
    public class SMSPersonNotifier : PersonNotifier
    {
        public SMSPersonNotifier(PersonGetter personGetter) : base(personGetter)
        {
        }
        public override void NotifyPersons(IEnumerable<Person> persons)
        {
            //notify persons via SMS
            throw new NotImplementedException();
        }
    }

    public abstract class PersonGetter
    {
        public abstract IEnumerable<Person> GetPersons();
    }
    public class XmlPersonGetter : PersonGetter
    {
        public override IEnumerable<Person> GetPersons()
        {
            //get persons from Xml file
            throw new NotImplementedException();
        }
    }
    public class DatabasePersonGetter : PersonGetter
    {
        public override IEnumerable<Person> GetPersons()
        {
            //get persons from database
            throw new NotImplementedException();
        }
    }
}

namespace Zad4
{
    public class PersonRegistry
    {
        public List<Person> GetPersons()
        {
            return new List<Person>()
                {
                    new Person(),
                    new Person()
                };
        }
        public void NotifyPersons()
        {
            foreach (Person person in GetPersons())
                Console.WriteLine(person);
        }
    }
    public class Person { }

    internal class Program
    {
        static void Main(string[] args)
        {
            Version1.PersonRegistry registry = new Version1.XmlPersonRegistry(new Version1.MailPersonNotifier());
            registry.NotifyPersons();
            Version2.PersonNotifier notifier = new Version2.SMSPersonNotifier(new Version2.DatabasePersonGetter());
            notifier.NotifyPersons();
        }
    }
}
