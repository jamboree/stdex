/*//////////////////////////////////////////////////////////////////////////////
    Copyright (c) 2015 Jamboree

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////*/
#ifndef STDEX_ACT_RESOLVER_HPP_INCLUDED
#define STDEX_ACT_RESOLVER_HPP_INCLUDED

#include <stdex/act/awaiter.hpp>

namespace stdex { namespace act
{
    template<class Resolver>
    inline auto resolve(Resolver& resolver, typename Resolver::query const& query)
    {
        ACT_RETURN_FREE_AWAITER(typename Resolver::iterator, resolver, resolve, query);
    }

    template<class Resolver>
    inline auto resolve(Resolver& resolver, typename Resolver::endpoint_type const& endpoint)
    {
        ACT_RETURN_FREE_AWAITER(typename Resolver::iterator, resolver, resolve, endpoint);
    }
}}

#endif