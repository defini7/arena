#include <stdio.h>

#define ARENA_IMPL
#include "arena.h"

typedef struct Test
{
    int a;
    float b;
} Test;

int main()
{
    Arena a;
    arena_init(&a, 1000);
    
    Test* t = arena_get(&a, sizeof(Test));
    float* p = arena_get(&a, sizeof(float));
    
    *p = 25.0f;
    t->a = 10312;
    t->b = 3.14f;

    printf("%f %d %f\n", *p, t->a, t->b);

    // Must fail
    arena_get(&a, 100);
    
    arena_free(&a);
    
    return 0;
}
