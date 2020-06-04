## l y R?

```cpp
Lvalue ---->int i      =      42; <------ rvalue
```

# && type objects

instead of creating and allocating objects in memory we can create temporary objects, k and l are the same but l is lighter.

```cpp
    int i = 1; 
    int j = 2; 
    int k = i + j;      <------ k
    int &&l = i + j;    <------ l
```
