/*//////////////////////////////////////////////////////////////////////////////
    Copyright (c) 2015 Jamboree

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////*/
#ifndef STDEX_ACT_SOCKET_HPP_INCLUDED
#define STDEX_ACT_SOCKET_HPP_INCLUDED

#include <cstddef>
#include <stdex/act/awaiter.hpp>

namespace stdex { namespace act
{
    template<class Socket>
    inline auto connect(Socket& socket, typename Socket::endpoint_type const& endpoint)
    {
        ACT_RETURN_AWAITER(void, socket, connect, endpoint);
    }

    template<class Socket, class MutableBufferSequence>
    inline auto read_some(Socket& socket, MutableBufferSequence const& buffers)
    {
        ACT_RETURN_AWAITER(std::size_t, socket, read_some, buffers);
    }

    template<class Socket, class MutableBufferSequence>
    inline auto receive(Socket& socket, MutableBufferSequence const& buffers)
    {
        ACT_RETURN_AWAITER(std::size_t, socket, receive, buffers);
    }

    template<class Socket, class MutableBufferSequence>
    inline auto receive(Socket& socket, MutableBufferSequence const& buffers, typename Socket::message_flags flags)
    {
        ACT_RETURN_AWAITER(std::size_t, socket, receive, buffers, flags);
    }

    template<class Socket, class ConstBufferSequence>
    inline auto send(Socket& socket, ConstBufferSequence const& buffers)
    {
        ACT_RETURN_AWAITER(std::size_t, socket, send, buffers);
    }

    template<class Socket, class ConstBufferSequence>
    inline auto send(Socket& socket, ConstBufferSequence const& buffers, typename Socket::message_flags flags)
    {
        ACT_RETURN_AWAITER(std::size_t, socket, send, buffers, flags);
    }

    template<class Socket, class ConstBufferSequence>
    inline auto write_some(Socket& socket, ConstBufferSequence const& buffers)
    {
        ACT_RETURN_AWAITER(std::size_t, socket, write_some, buffers);
    }
}}

#endif