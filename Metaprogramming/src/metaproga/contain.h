#ifndef METAPROGA_CONTAIN_H
#define METAPROGA_CONTAIN_H


template<typename ... T>
struct Pack{
    template<typename item>
    static constexpr bool solution = std::disjunction<std::is_same<T, item> ...>{};
};

template<typename Pack, typename item>
constexpr bool contain(){
    return Pack::template solution<item>;
}

#endif
