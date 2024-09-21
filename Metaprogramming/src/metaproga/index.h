#ifndef METAPROGA_INDEX_H
#define METAPROGA_INDEX_H

template<typename ...T>
struct Index;

template<typename T, typename U, typename ...Us>
struct Index<T, U, Us...>{
    constexpr static unsigned int value = Index<T, Us ...>::value + 1;
};

template<typename T, typename ...Us>
struct Index<T, T, Us...> {
    constexpr static unsigned int value = 0;
};

template<typename T>
struct Index<T>{
    constexpr static unsigned int value = 0;
};

#endif //INDEX_H
