# Macrograd

### How to run:

```
cmake -S . -B build
cmake --build build
build/macrograd jsons/simple_json.json
```

### Running valgrind to check memory leaks:


```
cd build/tests/
valgrind --leak-check=full ./BuildingBlocks_test 2>../../valgrind-logs/BuildingBlocksHeap.txt
```