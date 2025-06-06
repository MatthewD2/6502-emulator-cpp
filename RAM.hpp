#include <cstdint>
#include <iostream>

typedef int8_t BYTE;
typedef int16_t HALF_WORD;

class RAM {
    public:
        //define RAM sizes as binary
        static const int Internal_Ram_Size = 0x0800; // 2KB
        static const int Address_Space_size = 0x10000 // 64KB address space

        // default constructor
        RAM();



        for (int i = 0; i < Internal_Ram_Size; ++i) {
                mem[i] = 0;
        }
        
        // reading: given an address, go to that address and output 
        // whats there

        // writing: given an address, go to that address and change the value
        // to whatever the user sets it to be

        // Challenge: try to do this in one function

        // Your gonna have a signal R_W_n <--- "bool" where
        // if R_W_n = 1 then we are reading, otherwise we are writing.


    private:

        // array: we need to specify 64kb of memory
};

RAM::RAM() {
    for (int i = 0; i < Internal_Ram_Size; ++i) {
                mem[i] = 0;
            }
}
