//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// Copyright (C) 2011 Vicente J. Botet Escriba
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// <boost/thread/future.hpp>

// class packaged_task<R>

// packaged_task(packaged_task&& other);

#define BOOST_THREAD_VERSION 2

#include <boost/thread/future.hpp>
#include <boost/detail/lightweight_test.hpp>

class A
{
    long data_;

public:
    explicit A(long i) : data_(i) {}

    long operator()() const {return data_;}
    long operator()(long i, long j) const {return data_ + i + j;}
};


int main()
{
  {
    boost::packaged_task<double> p0(A(5));
    boost::packaged_task<double> p = boost::move(p0);
    BOOST_TEST(!p0.valid());
    BOOST_TEST(p.valid());
    boost::future<double> f = BOOST_THREAD_MAKE_RV_REF(p.get_future());
    //p(3, 'a');
    p();
    BOOST_TEST(f.get() == 5.0);
  }
  {
    boost::packaged_task<double> p0;
    boost::packaged_task<double> p = boost::move(p0);
    BOOST_TEST(!p0.valid());
    BOOST_TEST(!p.valid());
  }

  return boost::report_errors();
}

