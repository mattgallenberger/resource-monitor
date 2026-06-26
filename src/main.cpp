#include <iostream>
#include "../include/ring_buffer.h"

int main(){

    ringBuffer<int, 5> buffer;

    std::cout << buffer.isFull() << "\n";

    return 0;
}
