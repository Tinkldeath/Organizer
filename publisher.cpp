#include "publisher.h"

EventPublisher::EventPublisher(){
    subscribers = new Container<IEvent>();
}

void EventPublisher::AddSubscriber(IEvent *sub){
    subscribers->Add(sub);
}

void EventPublisher::RemoveSubscriber(IEvent *sub){
    subscribers->Remove(sub);
}

void EventPublisher::NotifySubscrivers(QDate inDate, QTime inTime){
    Node<IEvent>* p = subscribers->GetTop();
    while(p){
        p->key->Check(inDate, inTime);
        p = p->next;
    }
}

Node<IEvent>* EventPublisher::GetSubscribers(){
    return subscribers->GetTop();
}

void EventPublisher::Delete(){
    delete[] this;
}

void EventPublisher::Display(QListWidget *widget){
    Node<IEvent>* p = subscribers->GetTop();
    while (p) {
        p->key->Display(widget);
        p = p->next;
    }
}

IEvent* EventPublisher::FindSubscriber(QString header){
    Node<IEvent>* p = subscribers->GetTop();
    while (p) {
        if(p->key->GetHeader() == header){
            return p->key;
        }
        p = p->next;
    }
    return nullptr;
}

void EventPublisher::MuteSubscribers(){
    Node<IEvent>* p = subscribers->GetTop();
    while(p){
        p->key->Mute();
        p = p->next;
    }
}

void EventPublisher::UnmuteSubscribers(){
    Node<IEvent>* p = subscribers->GetTop();
    while(p){
        p->key->Unmute();
        p = p->next;
    }
}

void EventPublisher::CheckExecuted(){
    Node<IEvent>* p = subscribers->GetTop();
    while (p) {
        if(p->key->Executed()){
            Node<IEvent>* tmp = p;
            p = p->next;
            subscribers->Remove(tmp->key);
        }
        if(p == nullptr){
            return;
        }
        else p = p->next;
    }
}
