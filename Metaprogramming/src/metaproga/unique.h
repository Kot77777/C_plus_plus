#ifndef METAPROGA_UNIQUE_H
#define METAPROGA_UNIQUE_H
#include "Pack.h"
#include "concatenate.h"

template<typename... T>
struct is_not_empty;

template<typename R, typename... T>
struct is_not_empty<R, T...> {
    static constexpr bool value = true;
};

template<>
struct is_not_empty<> {
    static constexpr bool value = false;
};

template<typename R1, typename R2, typename ...T1, typename ...T2>
auto Unique(Pack<R1, R2, T1...>, Pack<T2...> B) {
    if constexpr (is_not_empty<R2>::value){
        if constexpr (!B.template contain<R1>) {
            return Unique(Pack<R2, T1 ...>{}, Concetenate(B, Pack<R1>{}));
        }
        else {
            return Unique(Pack<R2, T1 ...>{}, B);
        }
    }
    else{
        return Unique(Pack<R1>{}, B);
    }
}

template<typename R1, typename ...T2>
auto Unique(Pack<R1>, Pack<T2...> B) {
    if constexpr (!B.template contain<R1>) {
        return Pack<T2..., R1>{};
    }
    else {
        return B;
    }
}

template<typename ...T>
Pack<> Unique(Pack<>, Pack<>) {
    return Pack<>{};
}


template<typename Pack1, typename Pack2>
using unique = decltype(Unique(Pack1{}, Pack2{}));

#endif //UNIQUE_H
