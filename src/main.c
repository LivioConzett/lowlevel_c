#include <stdio.h>
#include "kv.h"

int main(int argc, char* argv[]){

    kv_t* table = kv_init(3);
    printf("%p\n", table);


    return 0;
}