#ifndef DOM_METAPROGRAMMING_HPP
#define DOM_METAPROGRAMMING_HPP

//--------------------------------------------------------------------------------

#include <type_traits>

//--------------------------------------------------------------------------------

namespace dom
{
    template<typename T1, typename T2>
    using isSameWeak = typename 
                        std::is_same
                        <
                            std::decay_t<T1>, 
                            std::decay_t<T2>
                        >;

    template<typename T, typename... Args>
    using isOneOf = typename std::disjunction<isSameWeak<T, Args>... >; 
}

#endif // !DOM_METAPROGRAMMING_HPP
