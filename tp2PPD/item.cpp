/* 
 * File:   item.cpp
 * Author: Otmar
 * 
 * Created on 28 de Abril de 2014, 20:47
 */

#include "item.h"

item::item(int id_item) {
    this->id = id_item;
}


int item::identificador(){
    return this->id;
}

bool item::operator ==(const item& other) const{
    return other.id == this->id;
}


