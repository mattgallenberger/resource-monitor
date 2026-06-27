template <typename T, int Capacity>

class MemoryPoolAllocator{

    private:

    // Struct to create an individual node in the free list.
    struct FreeNode {
    FreeNode* next;
};

    // Private data members, creates head node and pointer to the raw block of memory.
    FreeNode* free_list_head;
    void* rawBlock;

    public:
    
    // Constructor for the Memory Allocator.
    MemoryPoolAllocator(){
        
         size_t slotSize = std::max(sizeof(T), sizeof(FreeNode));

        // Grabs one raw block big enough for Capacity objects — no constructors run yet.
        rawBlock = operator new(slotSize * Capacity);

        // Loops through the size of the free list.
        for (int i = 0; i < Capacity; i++) {
            
            // Creates a pointer to the next node in the allocated chunk of memory.
            FreeNode* node = (FreeNode*)((char*)rawBlock + i * slotSize);
            
            // If capacity is reached, set node's next to nullptr.
            if(i == Capacity - 1){
                node->next = nullptr;
            }
            else {
                // Set current node's next to the next node in the chain.
                node->next = (FreeNode*)((char*)rawBlock + (i + 1) * slotSize);
            }

        }   
         // Sets the head to the first node in the chain.
        free_list_head = (FreeNode*)((char*)rawBlock);
    }
    
    // Function returns address of the next free block of memory, and advances to the next block of memory.
    T* allocate(){
        
        // Checks if free list is full, returns nullptr.
        if(free_list_head == nullptr){
            return nullptr;
        }

        // Else return address of available block.
        else{
            
            FreeNode* temp = free_list_head;

            free_list_head = temp->next;

            return (T*)(temp);
        }
        
    }

    // Sets the head to the freed node.
    void free(T* ptr){
         
        // Create a FreeNode pointer called "node", and set it to the pointer of the block we want to free.
        FreeNode* node = (FreeNode*)ptr;

        // Set block we want freed's next to where head is currently pointing at.
         node->next = free_list_head;

        // Set head to the block you just freed.
         free_list_head = node;
    }

    // Deconstructor that hands back the raw block of data.
    ~MemoryPoolAllocator(){
        operator delete(rawBlock);
    }

};

