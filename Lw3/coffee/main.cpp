﻿#include "Beverages.h"
#include "Condiments.h"

#include <iostream>
#include <string>
#include <functional>

using namespace std;


/*
Функциональный объект, создающий лимонную добавку
*/
struct MakeLemon
{
	MakeLemon(unsigned quantity)
		:m_quantity(quantity)
	{}

	auto operator()(IBeveragePtr && beverage)const
	{
		return make_unique<CLemon>(move(beverage), m_quantity); 
	}
private:
	unsigned m_quantity;
};

/*
Функция, возвращающая функцию, создающую коричную добавку
*/
function<IBeveragePtr(IBeveragePtr &&)> MakeCinnamon()
{
	return [] (IBeveragePtr && b) {
		return make_unique<CCinnamon>(move(b));
	};
}

/*
Возвращает функцию, декорирующую напиток определенной добавкой

Параметры шаблона: 
	Condiment - класс добавки, конструктор которого в качестве первого аргумента
				принимает IBeveragePtr&& оборачиваемого напитка
	Args - список типов прочих параметров конструктора (возможно, пустой)
*/
template <typename Condiment, typename... Args>
auto MakeCondiment(const Args&...args)
{
	// Возвращаем функцию, декорирующую напиток, переданный ей в качестве аргумента
	// Дополнительные аргументы декоратора, захваченные лямбда-функцией, передаются
	// конструктору декоратора через make_unique
	return [=](auto && b) {
		// Функции make_unique передаем b вместе со списком аргументов внешней функции
		return make_unique<Condiment>(forward<decltype(b)>(b), args...);
	};
}

/*
Перегруженная версия оператора <<, которая предоставляет нам синтаксический сахар
для декорирования компонента

Позволяет создать цепочку оборачивающих напиток декораторов следующим образом:
auto beverage = make_unique<CConcreteBeverage>(a, b, c)
					<< MakeCondimentA(d, e, f)
					<< MakeCondimentB(g, h);

Функциональные объекты MakeCondiment* запоминают аргументы, необходимые для создания
дополнения, и возвращают фабричную функцию, принимающую оборачиваемый напиток, которая
при своем вызове создаст нужный объект Condiment, передав ему запомненные аргументы.
Использование:
	auto beverage = 
		make_unique<CConcreteBeverage>(a, b, c)
		<< MakeCondimentA(d, e, f)
		<< MakeCondimentB(g, h);
или даже так:
	auto beverage = 
		make_unique<CConcreteBeverage>
		<< MakeCondiment<CondimentA>(d, e, f)
		<< MakeCondiment<CondimentB>(g, h);
В последнем случае нет необходимости писать вручную реализации MakeCondimentA и MakeCondimentB, т.к.
необходимую реализацию сгенерирует компилятор

Классический способ оборачивания выглядел бы так:
	auto baseBeverage = make_unique<CConcretedBeverage>(a, b, c);
	auto wrappedWithCondimentA = make_unique<CCondimentA>(move(baseBeverage), d, e, f);
	auto beverage = make_unique<CCondimentB>(move(wrappedWithCondimentA), g, h);
либо так:
	auto beverage = make_unique<CCondimentB>(
						make_unique<CCondimentA>(
							make_unique<CConcreteBeverage>(a, b, c), // Напиток
							d, e, f	// доп. параметы CondimentA
						),
						g, h		// доп. параметры CondimentB
					);

unique_ptr<CLemon> operator << (IBeveragePtr && lhs, const MakeLemon & factory)
{
	return factory(move(lhs));
}
unique_ptr<CCinnamon> operator << (IBeveragePtr && lhs, const MakeCinnamon & factory)
{
	return factory(move(lhs));
}
*/
template <typename Component, typename Decorator>
auto operator << (Component && component, const Decorator & decorate)
{
	return decorate(forward<Component>(component));
}

void DialogWithUser()
{
	cout << "Type 1 for coffee or 2 for tea or 3 for Milckshake\n";
	int beverageChoice;
	cin >> beverageChoice;

	unique_ptr<IBeverage> beverage;

	if (beverageChoice == 1)
	{
		cout << "Type 1 - Latte, 2 - Double Latte, 3 - Cappuccino, 4 - DoubleCappuccino\n";
		cin >> beverageChoice;
		if (beverageChoice == 1)
		{
			beverage = make_unique<CLatte>();
		}
		else if (beverageChoice == 2)
		{
			beverage = make_unique<CDoubleLatte>();
		}
		else if (beverageChoice == 3)
		{
			beverage = make_unique<CCappuccino>();
		}
		else if (beverageChoice == 4)
		{
			beverage = make_unique<CDoubleCappuccino>();
		}
		else
		{
			return;
		}
	}
	else if (beverageChoice == 2)
	{
		cout << "Type 1 - White, 2 - Green, 3 - Black, 4 - Yellow\n";
		cin >> beverageChoice;
		if (beverageChoice == 1)
		{
			beverage = make_unique<CWhiteTea>();
		}
		else if (beverageChoice == 2)
		{
			beverage = make_unique<CGreenTea>();
		}
		else if (beverageChoice == 3)
		{
			beverage = make_unique<CBlackTea>();
		}
		else if (beverageChoice == 4)
		{
			beverage = make_unique<CYellowTea>();
		}
		else
		{
			return;
		}
	}
	else if (beverageChoice == 3)
	{
		cout << "Type 1 - Small, 2 - Medium, 3 - Large\n";
		cin >> beverageChoice;
		if (beverageChoice == 1)
		{
			beverage = make_unique<CSmallMilkshake>();
		}
		else if (beverageChoice == 2)
		{
			beverage = make_unique<CMediumMilkshake>();
		}
		else if (beverageChoice == 3)
		{
			beverage = make_unique<CLargeMilkshake>();
		}
		else
		{
			return;
		}
	}
	else
	{
		return;
	}

	int condimentChoice;
	for (;;)
	{
		cout << "1 - Lemon, 2 - Cinnamon, 3 - Ice Cubes, 4 - Chocolate, 5 - Cream,\n6 - Liquor, 7 - Syrup, 8 - ChocolateCrumbs, 9 - CoconutFlakes 0 - Checkout" << endl;
		cin >> condimentChoice;

		if (condimentChoice == 1)
		{
			cout << "Quantity (1 - 5): ";
			cin >> condimentChoice;
			if (condimentChoice <= 0 || condimentChoice > 5)
				return;
			beverage = move(beverage) << MakeCondiment<CLemon>(condimentChoice);
		}
		else if (condimentChoice == 2)
		{
			beverage = move(beverage) << MakeCondiment<CCinnamon>();
		}
		else if (condimentChoice == 3)
		{
			cout << "Quantity (1 - 5): ";
			cin >> condimentChoice;
			if (condimentChoice <= 0 || condimentChoice > 5)
				return;
			int quantity = condimentChoice;
			cout << "Type: 1 - Dry 2 - Water";
			cin >> condimentChoice;
			if (condimentChoice != 1 && condimentChoice != 2)
				return;
			beverage = move(beverage) << MakeCondiment<CIceCubes>(quantity, (condimentChoice == 1) ? IceCubeType::Dry : IceCubeType::Water);
		}
		else if (condimentChoice == 4)
		{
			cout << "Quantity (1 - 5): ";
			cin >> condimentChoice;
			if (condimentChoice <= 0 || condimentChoice > 5)
				return;
			beverage = move(beverage) << MakeCondiment<CChocolate>(condimentChoice);
		}
		else if (condimentChoice == 5)
		{
			beverage = move(beverage) << MakeCondiment<CCream>();
		}
		else if (condimentChoice == 6)
		{
			cout << "Type: 1 - Chocolate 2 - Walnut";
			cin >> condimentChoice;
			if (condimentChoice != 1 && condimentChoice != 2)
				return;
			beverage = move(beverage) << MakeCondiment<CLiquor>((condimentChoice == 1) ? LiquorType::Chocolate : LiquorType::Walnut);
		}
		else if (condimentChoice == 7)
		{
			cout << "Type: 1 - Chocolate 2 - Maple";
			cin >> condimentChoice;
			if (condimentChoice != 1 && condimentChoice != 2)
				return;
			beverage = move(beverage) << MakeCondiment<CSyrup>((condimentChoice == 1) ? SyrupType::Chocolate : SyrupType::Maple);
		}
		else if (condimentChoice == 8)
		{
			cout << "Mass (1 - 5): ";
			cin >> condimentChoice;
			beverage = move(beverage) << MakeCondiment<CChocolateCrumbs>(condimentChoice);
		}
		else if (condimentChoice == 9)
		{
			cout << "Mass (1 - 5): ";
			cin >> condimentChoice;
			beverage = move(beverage) << MakeCondiment<CCoconutFlakes>(condimentChoice);
		}
		else if (condimentChoice == 0)
		{
			break;
		}
		else
		{
			return;
		}
	}



	cout << beverage->GetDescription() << ", cost: " << beverage->GetCost() << endl;
}


int main()
{
	DialogWithUser();
	//cout << endl;
	//{
	//	// Наливаем чашечку латте
	//	auto latte = make_unique<CLatte>();
	//	// добавляем корицы
	//	auto cinnamon = make_unique<CCinnamon>(move(latte));
	//	// добавляем пару долек лимона
	//	auto lemon = make_unique<CLemon>(move(cinnamon), 2);
	//	// добавляем пару кубиков льда
	//	auto iceCubes = make_unique<CIceCubes>(move(lemon), 2, IceCubeType::Dry);
	//	// добавляем 2 грамма шоколадной крошки
	//	auto beverage = make_unique<CChocolateCrumbs>(move(iceCubes), 2);

	//	// Выписываем счет покупателю
	//	cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	//}

	//{
	//	auto beverage =
	//		make_unique<CChocolateCrumbs>(			// Внешний слой: шоколадная крошка
	//			make_unique<CIceCubes>(				// | под нею - кубики льда
	//				make_unique<CLemon>(			// | | еще ниже лимон
	//					make_unique<CCinnamon>(		// | | | слоем ниже - корица
	//						make_unique<CLatte>()),	// | | |   в самом сердце - Латте
	//					2),							// | | 2 дольки лимона
	//				2, IceCubeType::Dry),			// | 2 кубика сухого льда
	//			2);									// 2 грамма шоколадной крошки

	//	// Выписываем счет покупателю
	//	cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	//}

	//// Подробнее рассмотрим работу MakeCondiment и оператора <<
	//{
	//	// lemon - функция, добавляющая "2 дольки лимона" к любому напитку
	//	auto lemon2 = MakeCondiment<CLemon>(2);
	//	// iceCubes - функция, добавляющая "3 кусочка льда" к любому напитку
	//	auto iceCubes3 = MakeCondiment<CIceCubes>(3, IceCubeType::Water);
	//	
	//	auto tea = make_unique<CTea>();

	//	// декорируем чай двумя дольками лимона и тремя кусочками льда
	//	auto lemonIceTea = iceCubes3(lemon2(move(tea)));	
	//	/* Предыдущая строка выполняет те же действия, что и следующий код:
	//	auto lemonIceTea = 
	//		make_unique<CIceCubes>(
	//			make_unique<CLemon>(
	//				move(tea), 
	//				2), 
	//			2, IceCubeType::Water);
	//	*/
	//	
	//	auto oneMoreLemonIceTea =
	//		make_unique<CTea>()	// Берем чай
	//		<< MakeCondiment<CLemon>(2)	// добавляем пару долек лимона
	//		<< MakeCondiment<CIceCubes>(3, IceCubeType::Water); // и 3 кубика льда
	//	/*
	//	Предыдущая конструкция делает то же самое, что и следующая:
	//	auto oneMoreLemonIceTea =
	//		MakeCondiment<CIceCubes>(3, IceCubeType::Water)(
	//			MakeCondiment<CLemon>(2)(make_unique<CTea>())
	//			);
	//	*/
	//}

	//// Аналог предыдущего решения с добавкой синтаксического сахара
	//// обеспечиваемого операторами << и функцией MakeCondiment
	//{
	//	auto beverage = 
	//		make_unique<CLatte>()							// Наливаем чашечку латте,
	//		<< MakeCondiment<CCinnamon>()					// оборачиваем корицей,
	//		<< MakeCondiment<CLemon>(2)						// добавляем пару долек лимона
	//		<< MakeCondiment<CIceCubes>(2, IceCubeType::Dry)// брасаем пару кубиков сухого льда
	//		<< MakeCondiment<CChocolateCrumbs>(2);			// посыпаем шоколадной крошкой

	//	// Выписываем счет покупателю
	//	cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	//}

	//{
	//	auto beverage = 
	//		make_unique<CMilkshake>()					// Наливаем молочный коктейль
	//		<< MakeCondiment<CSyrup>(SyrupType::Maple)	// заливаем кленовым сиропом
	//		<< MakeCondiment<CCoconutFlakes>(8);		// посыпаем кокосовой стружкой

	//	// Выписываем счет покупателю
	//	cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	//}
}
