#ifndef CONTAINER_H
#define CONTAINER_H

template  <typename T> struct Node
{
    Node(T* inKey){
        key = inKey;
        next = nullptr;
        prev = nullptr;
    }
    T* key;
    Node* next;
    Node* prev;
};

template <typename T> class Container
{
private:
    Node<T>* top;
    Node<T>* tail;
public:
    Container(){
        top = nullptr;
        tail = nullptr;
    }

    void Add(T* item){
        if(top == nullptr){
            top = new Node(item);
            tail = top;
            return;
        }
        Node<T>* p = new Node(item);
        tail->next = p;
        p->prev = tail;
        p->next = nullptr;
        tail = p;
    }

    void Remove(T* item){
        Node<T>* p = top;
        while (p) {
            if(p->key == item){
                break;
            }
            p = p->next;
        }
        if(p == nullptr){
            return;
        }
        else if(p == top && p->next != nullptr){
            Node<T>* tmp = top->next;
            tmp->prev = nullptr;
            delete top;
            top = tmp;
        }
        else if(p == top && p->next == nullptr){
            delete  top;
            top = nullptr;
            tail = nullptr;
        }
        else if(p == tail){
            Node<T>* tmp = p->prev;
            tmp->next = nullptr;
            delete tail;
            tail = tmp;
        }
        else{
            Node<T>* prev = p->prev;
            Node<T>* next = p->next;
            prev->next = next;
            next->prev = prev;
            delete  p;
        }
    }

    Node<T>* GetTop(){
        return top;
    }

};

#endif // CONTAINER_H
