#pragma once
#include "base_allocator.h"

template <typename T>
struct tracking_allocator:base_allocator<T>{

    T* allocate(const uint64_t elements_to_allocate){
        T* ptr = base_allocator<T>::allocate(elements_to_allocate);
        if (ptr != nullptr){
            std::cout << sizeof(T)*elements_to_allocate << " bytes were allocated" << '\n';
        }
        return ptr;
    }

    void deallocate (T* ptr, const uint64_t elements_to_deallocate){
        if (ptr != nullptr){
            base_allocator<T>::deallocate(ptr, elements_to_deallocate);
            std::cout << sizeof(T)*elements_to_deallocate << " bytes were deallocated" << '\n';
        }
        else{
            std::cout << "Nothing to deallocate - nullptr" << '\n';
        }
    }

    template<typename... Args>
    void construct (T* ptr, const Args&... args){
        if (ptr != nullptr){
            base_allocator<T>::construct(ptr, args...);
            std::cout << "Object was built, which consume " << sizeof(T) << " bytes" << '\n';
        }
    }

    void destroy(T* ptr){
        if (ptr != nullptr){
            std::cout << "Were cleaned " << sizeof(T) << " bytes" << '\n';
            base_allocator<T>::destroy(ptr);
        }
    }
};