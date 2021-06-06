#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "event.h"
#include "container.h"

class IPublisher
{
public:
    virtual void AddSubscriber(IEvent *sub) = 0;
    virtual void RemoveSubscriber(IEvent *sub) = 0;
    virtual void NotifySubscrivers(QDate inDate, QTime inTime) = 0;
    virtual void Delete() = 0;
    virtual Node<IEvent>* GetSubscribers() = 0;
    virtual IEvent* FindSubscriber(QString header) = 0;
    virtual void Display(QListWidget* widget) = 0;
    virtual void MuteSubscribers() = 0;
    virtual void UnmuteSubscribers() = 0;
    virtual void CheckExecuted() = 0;
};

class EventPublisher : public IPublisher
{
private:
    Container<IEvent> *subscribers;
public:
    EventPublisher();
    void AddSubscriber(IEvent *sub) override;
    void RemoveSubscriber(IEvent *sub) override;
    void NotifySubscrivers(QDate inDate, QTime inTime) override;
    void Delete() override;
    Node<IEvent>* GetSubscribers() override;
    void Display(QListWidget *widget) override;
    IEvent* FindSubscriber(QString header) override;
    void MuteSubscribers() override;
    void UnmuteSubscribers() override;
    void CheckExecuted() override;
};


#endif // PUBLISHER_H
