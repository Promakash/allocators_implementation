#include <iostream>
#include "tracking_allocator.h"
#include "linear_allocator.h"

//Для проверки утечек
/*#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define newDBG_NEW
#endif
#endif*/
struct Point{
    int x;
    int y;
    Point(int x, int y){
        this->x = x;
        this->y = y;
    }
};

int main() {
    //Проверял на утечки - утечек нет, но оставил куски, чтоб можно было наглядно убедиться
    // (работает только на msvc как я понял. Пытался через mingw - ничего не отображается)

    std::cout << "base_allocator allocation example" << '\n';

    base_allocator<int> baseAllocator_of_type;
    const int arr_size = 5;
    int* arr_of_int = baseAllocator_of_type.allocate(arr_size);
    for (int i = 0; i < 5; i++){
        arr_of_int[i] = i;
        std::cout << arr_of_int[i] << ' ';
    }
    std::cout << '\n' << '\n';
    baseAllocator_of_type.deallocate(arr_of_int, arr_size);

    std::cout << "base_allocator construct and destroy of class example" << '\n';

    base_allocator<Point> baseAllocator_of_class;
    Point* point_ptr = baseAllocator_of_class.allocate(1);
    baseAllocator_of_class.construct(point_ptr, 1,2);
    std::cout<<"Class has been created! x val = " << point_ptr->x << ", y val = " << point_ptr->y << '\n' << '\n';
    baseAllocator_of_class.destroy(point_ptr);

    std::cout << "Tracking allocator example (build on base_allocator)" << '\n';

    tracking_allocator<int> trackingAllocator;
    arr_of_int = trackingAllocator.allocate(arr_size);
    trackingAllocator.deallocate(arr_of_int, arr_size);

    std::cout << '\n' << "Linear allocator example" << '\n' << '\n';

    linear_allocator<int> linearAllocator_int_size_5(5);//size in bytes
    int* a = linearAllocator_int_size_5.allocate();

    std::cout << "Behavior when buffer is full:" << '\n' << '\n';
    int* b = linearAllocator_int_size_5.allocate();
    if (b == nullptr){
        std::cout << "Nullptr was returned" << '\n' << '\n';
    }

    std::cout << "lin_alloc's buf = 2 bytes. We are going to allocate 1 byte" << '\n';
    linear_allocator <char> linearAllocator_char_size_2(2);
    char* ch = linearAllocator_char_size_2.allocate();

    std::cout << "leveling by bits example:" << '\n';
    char* ch2 = linearAllocator_char_size_2.allocate();

    //Для проверки утечек
    /*_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
    _CrtDumpMemoryLeaks();*/
}
