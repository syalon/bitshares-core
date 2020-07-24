#pragma once

// TODO:syalon
#define ENABLE_MIRA

#ifdef ENABLE_MIRA
#include <mira/index_adapter.hpp>
#include <mira/multi_index_container.hpp>
#include <mira/ordered_index.hpp>
#include <mira/tag.hpp>
#include <mira/member.hpp>
#include <mira/indexed_by.hpp>
#include <mira/composite_key.hpp>
#include <mira/mem_fun.hpp>
#endif

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/tag.hpp>
#include <mira/boost_adapter.hpp>

#include <boost/mpl/vector.hpp>
#include <type_traits>
#include <typeinfo>

namespace graphene { namespace chain {

// #ifdef ENABLE_MIRA
//   template< typename T >
//   using allocator = std::allocator< T >;

//   // typedef boost::shared_mutex read_write_mutex;
//   // typedef boost::shared_lock< read_write_mutex > read_lock;
// #endif  //  ENABLE_MIRA

//	ordered_non_unique & boost::multi_index::hashed_unique use boost impl
// using boost::multi_index::ordered_non_unique;
// using boost::multi_index::hashed_unique;

#ifndef ENABLE_MIRA
using boost::multi_index::multi_index_container;
using boost::multi_index::indexed_by;
using boost::multi_index::ordered_unique;
using boost::multi_index::tag;
using boost::multi_index::member;
using boost::multi_index::composite_key;
using boost::multi_index::composite_key_compare;
using boost::multi_index::const_mem_fun;
using boost::multi_index::identity;

template< class Iterator >
inline boost::reverse_iterator< Iterator > make_reverse_iterator( Iterator iterator )
{
   return boost::reverse_iterator< Iterator >( iterator );
}

#else
template< typename Arg1, typename Arg2 >
using multi_index_container = mira::multi_index_adapter< Arg1, Arg2, std::allocator< Arg1 > >;
using mira::multi_index::indexed_by;
using mira::multi_index::ordered_unique;
using mira::multi_index::tag;
using mira::multi_index::member;
using mira::multi_index::composite_key;
using mira::multi_index::composite_key_compare;
using mira::multi_index::const_mem_fun;
using mira::multi_index::identity;

template< typename T1, typename T2, typename T3 >
class bmic_type : public ::mira::boost_multi_index_adapter< T1, T2, T3 >
{
public:
   using mira::boost_multi_index_adapter< T1, T2, T3 >::boost_multi_index_adapter;
};

template< typename T1, typename T2, typename T3 >
class mira_type : public ::mira::multi_index_container< T1, T2, T3 >
{
public:
   using mira::multi_index_container< T1, T2, T3 >::multi_index_container;
};

template< class Iterator >
inline Iterator make_reverse_iterator( Iterator iterator )
{
   return iterator.reverse();
}

#endif

} } // graphene::chain
