using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zad5
{
    public class Card
    {
        public int Number;
        private int _pin;

        public Card(int number, int pin)
        {
            this.Number = number;
            this._pin = pin;
        }

        public bool PinValid(int pin)
        {
            return this._pin == pin;
        }
    }
    public class ATMMachine
    {
        private List<Card> _cardsDatabase = new List<Card>()
        {
            new Card(12345, 4432),
            new Card(12346, 8971),
            new Card(12347, 1101),
            new Card(12348, 4760),
            new Card(12349, 3390)
        };
        public ATMMachine()
        {
            this.state = new WaitingForCardState(this);
            this.insertedCard = null;
        }

        public IState state;
        public bool cardValid;
        public Card insertedCard;
        public void SetState(IState newState)
        {
            this.state = newState;
        }

        public bool ValidCardNumber(int cardNumber)
        {
            foreach (Card c in this._cardsDatabase)
            {
                if (c.Number == cardNumber)
                {
                    this.insertedCard = c;
                    return true;
                }
            }
            return false;
        }

        public bool ValidPIN(int pin)
        {
            return this.insertedCard.PinValid(pin);
        }

        public void InsertCard(int cardNumber)
        {
            this.state.InsertCard(cardNumber);
        }

        public void InsertPIN(int pin)
        {
            this.state.InsertPIN(pin);
        }

        public void ChooseOperation(int operation)
        {
            this.state.ChooseOperation(operation);
        }

        public void WithdrawCard()
        {
            this.insertedCard = null;
            this.state.WithdrawCard();
        }

        public void DoAnotherOperation()
        {
            this.state.DoAnotherOperation();
        }
    }
    public interface IState
    {
        void InsertCard(int cardNumber);
        void InsertPIN(int pin);
        void ChooseOperation(int operation);
        void WithdrawCard();
        void DoAnotherOperation();
    }

    public class WaitingForCardState : IState
    {
        private ATMMachine _ATMMachine;

        public WaitingForCardState(ATMMachine ATMMachine)
        {
            Console.WriteLine("Oczekiwanie na wlozenie karty");
            this._ATMMachine = ATMMachine;
        }
        public void ChooseOperation(int operation)
        {
            throw new Exception();
        }

        public void DoAnotherOperation()
        {
            throw new Exception();
        }

        public void InsertCard(int cardNumber)
        {
            this._ATMMachine.SetState(new ReadingCardState(this._ATMMachine, cardNumber));
            if(this._ATMMachine.cardValid)
                this._ATMMachine.SetState(new WaitingForPINState(this._ATMMachine));
            else
                this._ATMMachine.SetState(new CardReadingErrorState(this._ATMMachine));

        }

        public void InsertPIN(int pin)
        {
            throw new Exception();
        }

        public void WithdrawCard()
        {
            throw new Exception();
        }
    }

    public class ReadingCardState : IState
    {
        private ATMMachine _ATMMachine;

        public ReadingCardState(ATMMachine ATMMachine, int cardNumber)
        {
            Console.WriteLine("Trwa odczytywanie karty");
            this._ATMMachine = ATMMachine;
            this._ATMMachine.cardValid = this._ATMMachine.ValidCardNumber(cardNumber);
        }

        public void ChooseOperation(int operation)
        {
            throw new Exception();
        }

        public void InsertCard(int cardNumber)
        {
            throw new Exception();
        }

        public void DoAnotherOperation()
        {
            throw new Exception();
        }

        public void InsertPIN(int pin)
        {
            throw new Exception();
        }

        public void WithdrawCard()
        {
            this._ATMMachine.SetState(new WaitingForCardState(this._ATMMachine));
        }
    }
    
    public class CardReadingErrorState : IState
    {
        private ATMMachine _ATMMachine;

        public CardReadingErrorState(ATMMachine ATMMachine)
        {
            Console.WriteLine("Blad podczas odczytywania karty");
            this._ATMMachine = ATMMachine;
        }

        public void ChooseOperation(int operation)
        {
            throw new Exception();
        }

        public void InsertCard(int cardNumber)
        {
            throw new Exception();
        }

        public void DoAnotherOperation()
        {
            throw new Exception();
        }

        public void InsertPIN(int pin)
        {
            throw new Exception();
        }

        public void WithdrawCard()
        {
            this._ATMMachine.SetState(new WaitingForCardState(this._ATMMachine));
        }
    }
    public class WaitingForPINState : IState
    {
        private ATMMachine _ATMMachine;

        public WaitingForPINState(ATMMachine ATMMachine)
        {
            Console.WriteLine("Wprowadz PIN");
            this._ATMMachine = ATMMachine;
        }

        public void ChooseOperation(int operation)
        {
            throw new Exception();
        }

        public void InsertCard(int cardNumber)
        {
            throw new Exception();
        }

        public void DoAnotherOperation()
        {
            throw new Exception();
        }

        public void InsertPIN(int pin)
        {
            if (this._ATMMachine.ValidPIN(pin))
                this._ATMMachine.SetState(new ChoosingOperationState(this._ATMMachine));
            else
                this._ATMMachine.SetState(new WrongPINState(this._ATMMachine));
        }

        public void WithdrawCard()
        {
            this._ATMMachine.SetState(new WaitingForCardState(this._ATMMachine));
        }
    }

    public class WrongPINState : IState
    {
        private ATMMachine _ATMMachine;

        public WrongPINState(ATMMachine ATMMachine)
        {
            Console.WriteLine("Podany pin jest nieprawidlowy");
            this._ATMMachine = ATMMachine;
        }

        public void ChooseOperation(int operation)
        {
            throw new Exception();
        }

        public void InsertCard(int cardNumber)
        {
            throw new Exception();
        }

        public void DoAnotherOperation()
        {
            throw new Exception();
        }

        public void InsertPIN(int pin)
        {
            throw new Exception();
        }

        public void WithdrawCard()
        {
            this._ATMMachine.SetState(new WaitingForCardState(this._ATMMachine));
        }
    }

    public class ChoosingOperationState : IState
    {
        private ATMMachine _ATMMachine;

        public ChoosingOperationState(ATMMachine ATMMachine)
        {
            Console.WriteLine("Wybierz operacje do wykonania");
            this._ATMMachine = ATMMachine;
        }

        public void ChooseOperation(int operation)
        {
            this._ATMMachine.SetState(new OperationOngoingState(this._ATMMachine, operation));
            if(operation == 0)
            {
                this._ATMMachine.SetState(new NextOperationOptionState(this._ATMMachine));
            }
            else
            {
                this._ATMMachine.SetState(new OperationErrorState(this._ATMMachine));
            }
        }

        public void DoAnotherOperation()
        {
            throw new Exception();
        }

        public void InsertCard(int cardNumber)
        {
            throw new Exception();
        }

        public void InsertPIN(int pin)
        {
            throw new Exception();
        }

        public void WithdrawCard()
        {
            this._ATMMachine.SetState(new WaitingForCardState(this._ATMMachine));
        }
    }

    public class OperationOngoingState : IState
    {
        private ATMMachine _ATMMachine;

        public OperationOngoingState(ATMMachine ATMMachine, int operation)
        {
            this._ATMMachine = ATMMachine;
            if(operation == 0)
            {
                Console.WriteLine("Wykonywanie operacji nr 1");
            }
            else
            {
                Console.WriteLine("Wykonywanie operacji nr 2");
            }
        }

        public void ChooseOperation(int operation)
        {
            throw new Exception();
        }

        public void DoAnotherOperation()
        {
            throw new Exception();
        }

        public void InsertCard(int cardNumber)
        {
            throw new Exception();
        }

        public void InsertPIN(int pin)
        {
            throw new Exception();
        }

        public void WithdrawCard()
        {
            this._ATMMachine.SetState(new WaitingForCardState(this._ATMMachine));
        }
    }

    public class OperationErrorState : IState
    {
        private ATMMachine _ATMMachine;

        public OperationErrorState(ATMMachine ATMMachine)
        {
            Console.WriteLine("Blad podczas wykonywania operacji");
            this._ATMMachine = ATMMachine;
        }

        public void ChooseOperation(int operation)
        {
            throw new Exception();
        }

        public void InsertCard(int cardNumber)
        {
            throw new Exception();
        }

        public void DoAnotherOperation()
        {
            throw new Exception();
        }

        public void InsertPIN(int pin)
        {
            throw new Exception();
        }

        public void WithdrawCard()
        {
            this._ATMMachine.SetState(new WaitingForCardState(this._ATMMachine));
        }
    }

    public class NextOperationOptionState : IState
    {
        private ATMMachine _ATMMachine;

        public NextOperationOptionState(ATMMachine ATMMachine)
        {
            this._ATMMachine = ATMMachine;
        }

        public void ChooseOperation(int operation)
        {
            throw new Exception();
        }

        public void InsertCard(int cardNumber)
        {
            throw new Exception();
        }

        public void DoAnotherOperation()
        {
            Console.WriteLine("Rozpocznij nowa operacje");
            this._ATMMachine.SetState(new ChoosingOperationState(this._ATMMachine));
        }

        public void InsertPIN(int pin)
        {
            throw new Exception();
        }

        public void WithdrawCard()
        {
            this._ATMMachine.SetState(new WaitingForCardState(this._ATMMachine));
        }
    }

    internal class Program
    {
        static void Main(string[] args)
        {
            ATMMachine m = new ATMMachine();
            m.InsertCard(12347);
            m.InsertPIN(1101);
            m.ChooseOperation(0);
            m.DoAnotherOperation();
            m.ChooseOperation(1);
            m.WithdrawCard();

            m.InsertCard(999999);
            m.WithdrawCard();

            m.InsertCard(12349);
            m.InsertPIN(1000);
            m.WithdrawCard();

            Console.ReadLine();
        }
    }
}
