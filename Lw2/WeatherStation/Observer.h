#pragma once

#include <set>
#include <vector>
#include <map>
#include <functional>
#include <iterator>

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс, 
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template <typename T>
class IObserver
{
public:
	virtual void Update(const void* subject, T const& data) = 0;
	virtual ~IObserver() = default;
};

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T, class Context>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T>& observer, std::set<Context> const& subscriptions, int priority = 0) = 0;
	virtual void NotifyObservers(std::set<Context> const& subscriptionsToServe) = 0;
	virtual void RemoveObserver(IObserver<T>& observer, std::set<Context> const& unsubscriptions) = 0;
};


// Реализация интерфейса IObservable
template <class T, class Context>
class CObservable : public IObservable<T, Context>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType& observer, std::set<Context> const& subscriptions, int priority = 0) override
	{
		if (m_observers.contains(&observer))
		{
			return;
		}
		m_observersPriorityQueue.emplace(priority, &observer);
		m_observers.insert(&observer);
		m_observerSubscriptions.insert(make_pair(&observer, subscriptions));
	}

	bool IsSubscribe(std::set<Context> const& subscriberSubs, std::set<Context> const& updatedSubs)
	{
		for (Context ctx : subscriberSubs)
		{
			if (updatedSubs.contains(ctx)) return true;
		}
		return false;
	}

	void NotifyObservers(std::set<Context> const& updatedSubs) override
	{
		T data = GetChangedData();
		for (auto & observer : m_observersPriorityQueue)
		{
			if (IsSubscribe(m_observerSubscriptions[observer.second], updatedSubs))
			{
				observer.second->Update(this, data);
			}
		}
	}

	void RemoveObserver(ObserverType& observer, std::set<Context> const& unsubscriptions) override
	{
		auto iterObsSubs = m_observerSubscriptions.find(&observer);
		if (iterObsSubs == m_observerSubscriptions.end())
		{
			return;
		}

		for (Context ctx : unsubscriptions)
		{
			if ((*iterObsSubs).second.contains(ctx))
			{
				(*iterObsSubs).second.erase(ctx);
			}
		}
		
		if (!(*iterObsSubs).second.empty())
		{
			return;
		}

		auto iterToErase = m_observersPriorityQueue.begin();
		for (auto iter = m_observersPriorityQueue.begin(); iter != m_observersPriorityQueue.end(); ++iter)
		{
			if (iter == m_observersPriorityQueue.end())
			{
				return;
			}
			
			if ((*iter).second == &observer)
			{
				iterToErase = iter;
				break;
			}
		}
		m_observersPriorityQueue.erase(iterToErase);
		m_observers.erase(&observer);
	}

	std::multimap<int, ObserverType*, std::greater<int>> GetPriorityMap() const
	{
		/*std::vector<ObserverType*> queue;
		for (auto observer : m_observersPriorityQueue)
		{
			queue.push_back(observer.second);
		}
		return queue;*/
		return m_observersPriorityQueue;

	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData()const = 0;

private:
	std::set<ObserverType*> m_observers;
	std::multimap<int, ObserverType*, std::greater<int>> m_observersPriorityQueue;
	std::map<ObserverType*, std::set<Context>> m_observerSubscriptions;
};

