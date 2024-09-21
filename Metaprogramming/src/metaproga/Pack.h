#ifndef METAPROGA_CORRECT_CONTAIN_H
#define METAPROGA_CORRECT_CONTAIN_H
#include "contain.h"
#include "index.h"

template<typename ...T>
struct Pack {

    template<typename R>
    constexpr static bool contain =  false || (is_same_v<T, R> || ...);

    template<typename R>
    constexpr static unsigned int count = 0 + (is_same_v<T, R> + ...);

    template<typename R>
    constexpr static unsigned int index = Index<R, T...>::value;

};

#endif //METAPROGA_CORRECT_CONTAIN_H
