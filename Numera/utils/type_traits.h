#ifndef TYPE_TRAITS_H
#define TYPE_TRAITS_H

#include <type_traits>

namespace nr
{
    template <typename Container>
    using value_type_t = typename std::decay_t<Container>::value_type;

    template <typename Iterator>
    using iterator_value_type_t =
        typename std::iterator_traits<Iterator>::value_type;


    template <typename Container, typename type>
    using conditional_type_f = 
    typename std::conditional_t<
    std::is_floating_point_v<
    typename Container::value_type>,
    typename Container::value_type, type>;

    template<typename Iterator, typename type>
    using iterator_conditional_type_f = 
    typename std::conditional_t<
    std::is_floating_point_v<
    typename std::iterator_traits<Iterator>::value_type>,
    typename std::iterator_traits<Iterator>::value_type, type>;

}   

#endif // TYPE_TRAITS_H