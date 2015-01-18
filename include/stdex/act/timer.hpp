/*//////////////////////////////////////////////////////////////////////////////
    Copyright (c) 2015 Jamboree

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////*/
#ifndef STDEX_ACT_TIMER_HPP_INCLUDED
#define STDEX_ACT_TIMER_HPP_INCLUDED

#include <stdex/act/awaiter.hpp>

namespace stdex { namespace act
{
    template<class Timer>
    inline auto wait_for(Timer& timer, typename Timer::duration const& duration)
    {
        return make_awaiter<void>([&timer, duration](auto&& cb)
        {
            timer.expires_from_now(duration);
            timer.async_wait(cb);
        });
    }

    template<class Timer>
    inline auto wait_until(Timer& timer, typename Timer::time_point const& time_point)
    {
        return make_awaiter<void>([&timer, time_point](auto&& cb)
        {
            timer.expires_at(time_point);
            timer.async_wait(cb);
        });
    }

    template<class Timer>
    inline auto expire(Timer& timer)
    {
        return make_awaiter<void>([&timer](auto&& cb)
        {
            timer.async_wait(cb);
        });
    }
}}

#endif