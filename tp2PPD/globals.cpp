#include "globals.h"
#include "item.h"

bool comparar_itens(item* i1, item* i2){
    return i1->identificador() < i2->identificador();
}
