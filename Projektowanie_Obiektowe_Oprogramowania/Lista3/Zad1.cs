using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zad1
{
    public interface IWeapon
    {
        void Attack(Character opponent);
        void Hide();
        void Draw();
        int DamagePoints();
        void SetOwner(Character newOwner);
    }

    public class Weapon : IWeapon
    {
        public int attacks_left;
        public int basic_damage_points;
        Character owner;
        bool hidden;
        public Weapon(Character owner)
        {
            this.owner = owner;
            this.hidden = true;
        }

        public void Attack(Character character)
        {
            if (attacks_left > 0 && !hidden)
            {
                attacks_left--;
                character.cur_health_points -= DamagePoints();
            }
        }

        public void Draw()
        {
            hidden = false;
        }

        public void Hide()
        {
            hidden = true;
        }

        public int DamagePoints()
        {
            return basic_damage_points * owner.Strength();
        }

        public void SetOwner(Character newOwner)
        {
            this.owner = newOwner;
        }
    }

    public class Sword : Weapon
    {
        public int length;
        public Sword(Character owner, int length) : base(owner)
        {
            this.length = length;
            this.basic_damage_points = 50;
            this.attacks_left = 30;
        }
    }
    //Polymorphism
    //Protected Variations
    //Creator
    public class Character
    {
        public int max_health_points;
        public int cur_health_points;
        public Weapon weapon;
        
        public Character(int max_hp, Weapon weapon)
        {
            this.max_health_points = max_hp;
            this.cur_health_points = max_hp;
            this.weapon = weapon;
            this.weapon.SetOwner(this);
        }
        public virtual int Strength() { return 0; }
        public void Attack(Character c)
        {
            weapon.Draw();
            weapon.Attack(c);
            weapon.Hide();
        }
    }

    public class Archer : Character
    {
        int shots_made;
        public Archer(int max_hp, Weapon weapon) : base(max_hp, weapon){
            this.shots_made = 0;
        }
        public override int Strength() {
            return cur_health_points / max_health_points * 2 + shots_made;
        }
    }

    public class Soldier : Character
    {
        int strokes_made;
        public Soldier(int max_hp, Weapon weapon) : base(max_hp, weapon) {
            this.strokes_made = 0;
        }

        public override int Strength()
        {
            return cur_health_points / max_health_points * 3 + strokes_made/2;
        }
    }

    //Creator
    public class FactoryOfCharacters
    {
        public Character Create()
        {
            Sword s = new Sword(null, 123);
            return new Soldier(100, s);
        }
    }
    internal class Program
    {
        static void Main(string[] args)
        {
            //Creator
            //Nie trzeba robić 
            //Character c1 = new Character();
            //Można:
            Character c1 = new FactoryOfCharacters().Create();
            Character c2 = new FactoryOfCharacters().Create();

            //Protected variations
            //nie korzystamy z:
            //c1.weapon.Attack(c2);
            //c2.cur_health_points -= c1.weapon.DamagePoints();
            //tylko udostępniamy:
            c1.Attack(c2);


            Console.ReadLine();
        }
    }
}
