#ifndef METAPROGA_CONTAIN_H
#define METAPROGA_CONTAIN_H


template<typename T1, typename T2>
struct is_same {
    constexpr static bool value = false;
};

template<typename T>
struct is_same<T, T> {
    constexpr static bool value = true;
};

template<typename T1, typename T2>
constexpr bool is_same_v = is_same<T1, T2>::value;

#endif
