/*
This file is part of Toupl.
http://code.google.com/p/toupl/
 
Autor: Bga
Email: bga.email@gmail.com
X.509 & GnuPG Email certifaces here: http://code.google.com/p/jbasis/downloads/list

Copyright 2009 Bga <bga.email@gmail.com>
 
Licensed to the Apache Software Foundation (ASF) under one
or more contributor license agreements.  See the NOTICE file
distributed with this work for additional information
regarding copyright ownership.  The ASF licenses this file
to you under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance
with the License.  You may obtain a copy of the License at
 
  http://www.apache.org/licenses/LICENSE-2.0
 
Unless required by applicable law or agreed to in writing,
software distributed under the License is distributed on an
"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
KIND, either express or implied.  See the License for the
specific language governing permissions and limitations
under the License.
*/

#ifndef COMMON_HPP
#define COMMON_HPP

#include "config.hpp"

// disable standart assert
#define NDEBUG
#include <assert.h>

using namespace std;

typedef void Void;
typedef int Int;
typedef bool Bool;
typedef char Char;
typedef long Long;


#define null 0
#define Const const
#define Virtual virtual
#define Unsigned unsigned
#define Static static

#if ASSERT_ENABLE
  #define _assert(st,msg) if((st)) printf((msg));
#else
  #define _assert(st,msg)
#endif  


#if DEBUG_ENABLE
  #define DEBUG(st) st
#else
  #define DEBUG(st)
#endif  

template<class _C>
Bool _t(const _C& c)
{
  return c!=null;
}

template<class _C>
_C _c(_C& c,Int deep=-1);
template<class _C>
_C _c(_C& c,Int deep=-1)
{
  return _C(c);
}
template<class _C>
_C _c(const _C& c,Int deep=-1)
{
  return _C(c);
}

template<class _C>
_C _min(const _C& a,const _C& b)
{
  return a<b?a:b;
}
template<class _C>
_C _max(const _C& a,const _C& b)
{
  return a>b?a:b;
}

template<class _C>
Void _delete(_C& c)
{
  if(!_t(c))
    return;
  
  delete c;
  c=null;
}

class String;

Void _log(Const String& msg);
Void _log(Const Char* msg);

struct LineAndCol
{
  Int line_;
  Int col_;
};

LineAndCol _posToLineAndCol(String& str,Int pos,Int tabSpacesLength=8);

#endif
