#ifndef METAPROGA_CONTAIN_H
#define METAPROGA_CONTAIN_H
#include <typeinfo>

template<typename A, typename ... T>
struct Pack{

    template<typename B>
    bool next_type()
    {
        if constexpr ((sizeof ... (T)) != 0) {
            if(typeid(A).name() == typeid(B).name()) {
                return true;
            }
            Pack<T...> f;
            return f.template next_type<B>();
        }
        else {
            if(typeid(A).name() == typeid(B).name()) {
                return true;
            }
            else{return false;}
        }
    }
};

template<typename Pack, typename item>
bool contain()
{
    Pack a;
    bool type = a.template next_type<item>();
    return type;
}

#endif
