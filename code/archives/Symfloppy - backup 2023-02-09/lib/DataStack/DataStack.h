#ifndef DataStack_h
#define DataStack_h

#include <Arduino.h>
#include <iostream>


template<typename T>
class DataStack {

    private:
        struct DataStackElement {
            T * content;
            DataStackElement * next_element;
        };

        DataStackElement * first_element;
        DataStackElement * last_element;
        DataStackElement * current_element;
        unsigned int elements_count;


    public:
        DataStack();
        ~DataStack();

        void push(T * element_content);
        int length();

        bool next();
        T * getCurrent();
        T * getNext();
        void resetCursor();

        void removeAll(bool delete_content);

};



template<typename T>
DataStack<T>::DataStack() {
    this->elements_count = 0;
}

template<typename T>
void DataStack<T>::removeAll(bool delete_content) {
    DataStackElement * _current_element;
    DataStackElement * _next_element;

    _current_element = this->current_element;

    while(_current_element) {
        _next_element = _current_element->next_element;

        if (delete_content) {
            delete _current_element->content;
            _current_element->content = NULL;
        }
        delete _current_element;

        _current_element = _next_element;
    }

    this->current_element = NULL;
    this->last_element = NULL;
    this->first_element = NULL;

    this->elements_count = 0;
}

template<typename T>
DataStack<T>::~DataStack() {
    this->removeAll(true);
}


template<typename T>
void DataStack<T>::push(T * element_content) {
    this->elements_count += 1;
    DataStackElement * element = new DataStackElement();

    element->content = element_content;

    if (!this->first_element) {
        this->first_element = element;
        this->current_element = element;
    } else {
        this->last_element->next_element = element;    
    }
    this->last_element = element;
}


template<typename T>
int DataStack<T>::length() {
    return this->elements_count;
}


template<typename T>
void DataStack<T>::resetCursor() {
    this->current_element = this->first_element;
}


template<typename T>
bool DataStack<T>::next() {
    bool result = false;
    if (this->current_element) {
        this->current_element = this->current_element->next_element;
        result = true;
    }
    return result;
}


template<typename T>
T * DataStack<T>::getCurrent() {
    T * result = NULL;
    if (this->current_element) {
        result = this->current_element->content;
    }
    return result;
}


template<typename T>
T * DataStack<T>::getNext() {
    T * result = this->getCurrent();
    if (result) {
        this->next();
    } else {
        this->resetCursor();
    }
    return result;
}

#endif