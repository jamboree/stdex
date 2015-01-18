/*//////////////////////////////////////////////////////////////////////////////
    Copyright (c) 2015 Jamboree

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////*/
#ifndef STDEX_ACT_AWAITER_HPP_INCLUDED
#define STDEX_ACT_AWAITER_HPP_INCLUDED

#include <functional>
#include <type_traits>
#include <stdex/coroutine.hpp>
#include <boost/system/system_error.hpp>

namespace stdex { namespace act_detail
{
    template<class T>
    inline T const& unwrap(T const& val)
    {
        return val;
    }

    template<class T>
    inline T& unwrap(std::reference_wrapper<T> val)
    {
        return val;
    }
}}

namespace stdex { namespace act
{
    template<class T, class F>
    struct awaiter
    {
        F _f;
        boost::system::error_code _ec;
        T _val;

        bool await_ready() const
        {
            return false;
        }

        void await_suspend(stdex::coroutine_handle<> cb)
        {
            _f([this, cb](boost::system::error_code ec, T val)
            {
                _ec = ec;
                _val = val;
                cb();
            });
        }

        T await_resume()
        {
            if (_ec)
                throw boost::system::system_error(_ec);
            return _val;
        }
    };

    template<class F>
    struct awaiter<void, F>
    {
        F _f;
        boost::system::error_code _ec;

        bool await_ready() const
        {
            return false;
        }

        void await_suspend(stdex::coroutine_handle<> cb)
        {
            _f([&_ec = _ec, cb](boost::system::error_code ec)
            {
                _ec = ec;
                cb();
            });
        }

        void await_resume()
        {
            if (_ec)
                throw boost::system::system_error(_ec);
        }
    };

    template<class T, class F>
    inline awaiter<T, std::remove_reference_t<F>> make_awaiter(F&& f)
    {
        return{ std::forward<F>(f) };
    }

#define ACT_RETURN_AWAITER(R, obj, op, ...)             \
    return make_awaiter<R>([&obj, =](auto&& cb)         \
    {                                                   \
        obj.async_##op(__VA_ARGS__, cb);                \
    })

#define ACT_RETURN_FREE_AWAITER(R, obj, op, ...)                            \
    return [&obj](auto&&... args)                                           \
    {                                                                       \
        return make_awaiter<R>([&obj, =](auto&& cb)                         \
        {                                                                   \
            ::boost::asio::async_##op(obj, act_detail::unwrap(args)..., cb);\
        });                                                                 \
    }(__VA_ARGS__)
}}

#endif
