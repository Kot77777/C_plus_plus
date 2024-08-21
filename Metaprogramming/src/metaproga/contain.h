#ifndef METAPROGA_CONTAIN_H
#define METAPROGA_CONTAIN_H


template<typename ... T>
struct Pack{

    template<typename item>
    constexpr bool initialize(){
        return std::disjunction<std::is_same<T, item> ...>{};
    }

};

template<typename Pack, typename item>
constexpr bool contain()
{
    Pack a;
    return (a. template initialize<item>());
}

#endif
