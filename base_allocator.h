#pragma once
#include "iostream"
#include "exception"
#include "cstdint"

template <typename T>
struct base_allocator{

    T* allocate(const uint64_t elements_to_allocate){
        if (elements_to_allocate < 1){
            return nullptr;
        }
        else{
            try {
                return reinterpret_cast<T*>(new char[elements_to_allocate * sizeof(T)]);
            }
            catch (const std::bad_alloc& e){
                std::cerr << "Allocation failed: " << e.what() << '\n';
                return nullptr;
            }
        }
    }

    void deallocate (T* ptr, const uint64_t elements_to_deallocate){ //в std аллокаторе нужен размер, по стандарту тоже, поэтому и я размер попросил ))
        delete[] reinterpret_cast<char*>(ptr);
    }

    template<typename... Args>
    void construct (T* ptr, const Args&... args){//placement new
        try{
            if (ptr == nullptr){
                throw std::invalid_argument("Pointer for construction can't be nullptr");
            }
            else{
                new (ptr) T(args...); //args... для корректной работы с классами например Point(x,y);
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

};