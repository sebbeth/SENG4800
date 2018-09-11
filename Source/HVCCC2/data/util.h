#pragma once

template<typename... Ts>
struct TypeList;

#include <tuple>
namespace type_utility_detail
{
    template<int... Is>
    struct seq { };

    template<int N, int... Is>
    struct gen_seq : gen_seq<N - 1, N - 1, Is...> { };

    template<int... Is>
    struct gen_seq<0, Is...> : seq<Is...> { };
    template<typename T, typename F, int... Is>
    void for_each(T&& t, F f, seq<Is...>)
    {
        auto l = { (f(std::get<Is>(t)), 0)... };
    }


	//template<typename Func, typename... Types>
	//struct for_each_in_typelist_conditional {};

	//template<typename Predicate, typename... Types>
	//struct for_each_in_typelist<Predicate, TypeList<Types...>> : for_each_in_typelist<Predicate, Types...> {
	//};

	template <typename, typename>
	struct list_append_impl {};

	template <typename... Ts, typename... Us>
	struct list_append_impl<TypeList<Ts...>, TypeList<Us...>> {
		using type = TypeList<Ts..., Us...>;
	};

	template <template <typename> class, typename...>
	struct filter_impl;

	template <template <typename> class Predicate>
	struct filter_impl<Predicate> {
		using type = TypeList<>;
	};

	template <template <typename> class Predicate, typename T, typename... Rest>
	struct filter_impl<Predicate, T, Rest...> {
		using type = typename list_append_impl<
			std::conditional_t<
			Predicate<T>::value,
			TypeList<T>,
			TypeList<>
			>,
			typename filter_impl<Predicate, Rest...>::type
		>::type;
	};



	template <template <typename> class, typename...>
	struct any_impl;

	template <template <typename> class Predicate>
	struct any_impl<Predicate> {
		using type = std::false_type;
	};

	template <template <typename> class Predicate, typename T, typename... Rest>
	struct any_impl<Predicate, T, Rest...> {
		using type = typename std::conditional_t<
			Predicate<T>::value,
			std::true_type,
			any_impl<Predicate, Rest...>
		>::type;
	};

	template <template <typename> class, typename...>
	struct all_impl;

	template <template <typename> class Predicate>
	struct all_impl<Predicate> {
		using type = std::true_type;
	};

	template <template <typename> class Predicate, typename T, typename... Rest>
	struct all_impl<Predicate, T, Rest...> {
		using type = typename std::conditional_t<
			Predicate<T>::value,
			any_impl<Predicate, Rest...>,
			std::false_type
		>::type;
	};
}

template<template <typename> class Predicate, typename... Types>
using TypeFilter = typename type_utility_detail::filter_impl<Predicate, Types...>::type;

template<template <typename> class Predicate, typename... Types>
using ConditionalAll = typename type_utility_detail::all_impl<Predicate, Types...>::type;

template<template <typename> class Predicate, typename... Types>
using ConditionalAny = typename type_utility_detail::all_impl<Predicate, Types...>::type;


using tmp = TypeFilter<std::is_void, void, void, int>;

template<typename... Ts, typename F>
void forEachInTuple(std::tuple<Ts...>& t, F f)
{
    type_utility_detail::for_each(t, f, type_utility_detail::gen_seq<sizeof...(Ts)>());
}

template<typename... Ts, typename F>
void forEachInTuple(const std::tuple<Ts...>& t, F f)
{
	type_utility_detail::for_each(t, f, type_utility_detail::gen_seq<sizeof...(Ts)>());
}