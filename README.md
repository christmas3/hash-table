# Хеш таблица

Реализация примитивной хэш таблицы методом цепочек с квадратичным пробингом

# Зависимости сборки

* c++17
* cmake
* gtest

# Сборка cmake

``` shell
mkdir ../build
cd ../build
cmake ..
cmake --build .
```

## Запуск тестов

```shell 
./hash_table
```

# Docker

```shell
docker build -t testing .
docker run -it testing sh
/src/testing/build/testing
```
