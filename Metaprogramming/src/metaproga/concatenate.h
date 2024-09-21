#ifndef METAPROGA_CONCATENATE_H
#define METAPROGA_CONCATENATE_H
#include "Pack.h"

template<typename ...T1, typename ...T2>
Pack<T1..., T2...> Concetenate(Pack<T1...>, Pack<T2...>){
    return Pack<T1..., T2...>{};
}
//конец для concetenate

template<typename Pack1, typename Pack2>
using concetenate = decltype(Concetenate(Pack1{}, Pack2{}));

#endif //CONCATENATE_H
