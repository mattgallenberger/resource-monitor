#pragma once
#include <stdexcept>
#include <iostream>

template <typename T, int Capacity>

class ringBuffer{
    
    private:

    int head;

    int tail;

    int size;

    T buffer[Capacity];

    public:

    ringBuffer() : head(0), tail(0), size(0)  {

    }

    void push(T value){
        buffer[tail] = value;
        tail = (tail + 1) % Capacity;

        if(size == Capacity){
            head = (head + 1) % Capacity;
        }
        else{
            size++;
        }
    }

    T pop(){

        if(size == 0){
            throw std::runtime_error("The buffer is empty");
        }
        else{
        T temp = buffer[head];
        head = (head + 1) % Capacity;
        size--;
        return temp;
        }

    }

    bool isEmpty(){
        if(size == 0){
            return true;
        }
        else{
            return false;
        }
    }

    bool isFull(){
        if(size == Capacity){
            return true;
        }
        else{
            return false;
        }
    }

    void print(){

        for(int i=0; i < size; i++){
            std::cout << (buffer[(head + i) % Capacity]) << "\n";
        }
    }



};