#pragma once
#include "exception"
#include "iostream"
#include "cstdint"


//Линейный аллокатор с выравниванием
template<typename T>
class linear_allocator{
private:
    uint64_t size_of_buffer = 0;
    char* free_bytes = nullptr;
    char* buffer = nullptr;
public:
    //user_input_size in bytes
    linear_allocator(const uint64_t user_input_size = 1'000'000'000){ //1gb by default
        size_of_buffer = user_input_size;
        try{
            buffer = new char[user_input_size];
            free_bytes = buffer;
        }
        catch (const std::bad_alloc& e){
            std::cerr << "Allocation failed: " << e.what() << '\n';
            return;
        }
    }

    T* allocate(const uint64_t size_to_allocate = 1){ // allocation for 1 object by default
        try{
            if (size_to_allocate == 0){
                throw std::invalid_argument("size to allocate must be >0");
            }
            uint64_t arr_size = size_to_allocate*sizeof(T);
            if (free_bytes+arr_size <= buffer+size_of_buffer){
                T* ptr = reinterpret_cast<T*>(free_bytes);
                free_bytes = free_bytes + arr_size;
                if (arr_size % 2 != 0){
                    free_bytes++;
                }
                return ptr;
            }
            else{
                throw std::bad_alloc();
            }
        }
        catch (const std::bad_alloc& e){
            std::cerr << "Can't allocate - buffer is full: " << e.what() << '\n';
            return nullptr;
        }
        catch (const std::invalid_argument& e){
            std::cerr << e.what() << '\n';
            return nullptr;
        }
    }

    template<typename... Args>
    void construct(T* ptr,const Args&... args){ //placement new
        try{
            if (ptr == nullptr){
                throw std::invalid_argument("Pointer for construction can't be nullptr");
            }
            else{
                new (ptr) T(args...); //args... для корректной работы с классами = new Point(x,y);
            }
        }
        catch (std::invalid_argument& e){
            std::cerr << e.what() << '\n';
        }
    }

    void destroy(T* ptr){
        if (ptr == nullptr){
            std::cout << "Nothing to destroy!" << '\n';
            return;
        }
        else{
            ptr->~T();
        }
    }

    void free_buffer(){
        for (uint64_t i = 0; i < size_of_buffer; ++i) {
            buffer[i] = NULL;
        }
        free_bytes = buffer;
    }

    ~linear_allocator(){
        delete[] buffer;
    }

    linear_allocator& operator=(const linear_allocator& copy){
        delete[] this->buffer;
        this->buffer = copy.buffer;
        this->free_bytes = copy.free_bytes;
        this->size_of_buffer = copy.size_of_buffer;
        return *this;
    }

    linear_allocator(const linear_allocator& copy){
        delete[] this->buffer;
        this->buffer = copy.buffer;
        this->free_bytes = copy.free_bytes;
        this->size_of_buffer = copy.size_of_buffer;
    }

};