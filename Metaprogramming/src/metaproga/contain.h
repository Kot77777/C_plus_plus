#ifndef METAPROGA_CONTAIN_H
#define METAPROGA_CONTAIN_H
#include <typeinfo>

template<typename ... T>
struct Pack{

    constexpr int size() {
        return (sizeof ... (T));
    }

    constexpr std::array<const char*, sizeof ... (T)> initialize(){
        return {typeid(T).name() ...};
    }
};

template<typename Pack, typename item>
constexpr bool contain()
{
    Pack a;
    constexpr int lenth = a.size();
    std::array<const char*, lenth> type = a.initialize();
    for (int i = 0; i < lenth; ++i) {
        if (typeid(item).name() == type[i]){return true;}
    }
    return false;
}

#endif
