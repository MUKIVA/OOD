#include <cassert>
#include <iostream>
#include <memory>
#include <vector>
#include <functional>

using namespace std;

typedef function<void()> FlyBehavior;

FlyBehavior FlyWithWings = []() { cout << "I'm flying with wings!!" << endl; };
FlyBehavior FlyNoWay = []() {};

typedef function<void()> DanceBehavior;

DanceBehavior DanceWaltz = []() {cout << "I'm dance waltz!!" << endl; };
DanceBehavior DanceMinuet = []() {cout << "I'm dance minuet!!" << endl; };
DanceBehavior DanceNoWay = []() {};

typedef function<void()> QuackBehavior;

QuackBehavior QuackQuackBehavior = []() {cout << "Quack Quack!!!" << endl; };
QuackBehavior SqueakBehavior = []() {cout << "Squeek!!!" << endl; };
QuackBehavior MuteQuackBehavior = []() {};

class Duck
{
public:
	Duck(FlyBehavior& flyBehavior,
		QuackBehavior& quackBehavior,
		DanceBehavior& danceBehavior)
		: m_quackBehavior(quackBehavior)
	{
		assert(m_quackBehavior);
		SetFlyBehavior(flyBehavior);
		SetDanceBehavior(danceBehavior);
	}
	void Quack() const
	{
		m_quackBehavior();
	}
	void Swim()
	{
		cout << "I'm swimming" << endl;
	}
	void Fly()
	{
		m_flyBehavior();
	}
	void Dance()
	{
		m_danceBehavior();
	}
	void SetFlyBehavior(FlyBehavior& flyBehavior)
	{
		assert(flyBehavior);
		m_flyBehavior = flyBehavior;
	}

	void SetDanceBehavior(function<void()> danceBehavior)
	{
		assert(danceBehavior);
		m_danceBehavior = danceBehavior;
	}
	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	FlyBehavior m_flyBehavior;
	DanceBehavior m_danceBehavior;
	QuackBehavior m_quackBehavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(FlyWithWings, QuackQuackBehavior, DanceWaltz)
	{
	}

	void Display() const override
	{
		cout << "I'm mallard duck" << endl;
	}
};

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(FlyWithWings, QuackQuackBehavior, DanceMinuet)
	{
	}
	void Display() const override
	{
		cout << "I'm redhead duck" << endl;
	}
};
class DecoyDuck : public Duck
{
public:
	DecoyDuck()
		: Duck(FlyNoWay, MuteQuackBehavior, DanceNoWay)
	{
	}
	void Display() const override
	{
		cout << "I'm decoy duck" << endl;
	}
};
class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(FlyNoWay, SqueakBehavior, DanceNoWay)
	{
	}
	void Display() const override
	{
		cout << "I'm rubber duck" << endl;
	}
};

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(FlyNoWay, QuackQuackBehavior, DanceNoWay)
	{
	}
	void Display() const override
	{
		cout << "I'm model duck" << endl;
	}
};

void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck& duck)
{
	DrawDuck(duck);
	duck.Quack();
	duck.Fly();
	duck.Dance();
	cout << endl;
}

int main()
{
	MallardDuck mallardDuck;
	PlayWithDuck(mallardDuck);

	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);
	redheadDuck.Fly();

	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);

	DecoyDuck decoyDuck;
	PlayWithDuck(decoyDuck);

	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyBehavior(FlyWithWings);
	PlayWithDuck(modelDuck);
}
