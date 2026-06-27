#include <iostream>
#include "../include/ring_buffer.h"
#include "../include/memory_pool_allocator.h"

int main(){

    MemoryPoolAllocator<int, 3> pool;
    std::cout << "pool created\n";

    int* a = pool.allocate();
    std::cout << "a allocated\n";
    int* b = pool.allocate();
    std::cout << "b allocated\n";
    int* c = pool.allocate();
    std::cout << "c allocated\n";

    std::cout << "a: " << a << "\n";
    std::cout << "b: " << b << "\n";
    std::cout << "c: " << c << "\n";

    pool.free(b);                    // return the middle slot
    int* d = pool.allocate();        // allocate again
    std::cout << "d: " << d << "\n"; // what address comes back?

   

    return 0;
}
