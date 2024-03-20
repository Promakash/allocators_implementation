# allocators_implementation

## Реализованы простейшие аллокаторы
1) Базовый аллокатор
2) Трассирующий аллокатор на основе базового
3) Линейный аллокатор с выравниванием

## Как запустить?
1) Создайте cmake папку в корневной папке проекта.

```
mkdir build
cmake ..
```

2.1) Для билда бенчмарка
```
cd build
make bench_tests
./bench_tests
```
2.2) Для запуска демонстрационного файла
```
cd build
make show_of_allocators
./show_of_allocators
```
