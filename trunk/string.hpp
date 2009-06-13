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

#ifndef STRING_HPP
#define STRING_HPP

#include "common.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if STRING_STD_SUPPORT_ENABLE
  #include <iostream>
  #include <string>
#endif

#if STRING_PROFILE_ENABLE
  #define STRING_PROFILE(st) st
#else
  #define STRING_PROFILE(st) st
#endif
  
class String;

Bool operator<(Const String& a,Const String& b);
Bool operator<=(Const String& a,Const String& b);
Bool operator==(Const String& a,Const String& b);
Bool operator>(Const String& a,Const String& b);
Bool operator>=(Const String& a,Const String& b);
Bool operator!=(Const String& a,Const String& b);

#if STRING_STD_SUPPORT_ENABLE
std::ostream& operator<<(std::ostream& s,const String& str);
#endif

// JavaScript String emulator class
class String
{
  public:
  
  static const Int capIncrement_=256;
  
  class Buffer_
  {
    public:
    
    STRING_PROFILE(Static Int allocCount_;)
    
    Int refCount_;
    Char* ptr_;
    //Int length_;
    Int cap_;
    
    Buffer_()
    {
      refCount_=0;
      ptr_=null;
      //length_=0;
      cap_=0;
    }
    
    Void _lock()
    {
      ++refCount_;
    }
    Void _unLock()
    {
      --refCount_;
      
      if(refCount_>0)
        return;
      
      free(ptr_);
      ptr_=null;
      cap_=0;
      
      delete this; // :)
    }
    Bool _isLocked()
    {
      return refCount_>0;
    }
    Bool _isMonopole()
    {
      return refCount_==1;
    }
    Void _alloc(Int cap)
    {
      STRING_PROFILE(++allocCount_;)
      _assert(!_isMonopole(),"non monopole alloc");
      _assert(_t(ptr_),"alloc but non free buffer");
      
      ptr_=(Char *)malloc(cap);
      cap_=cap;
    }
    Void _free()
    {
      _assert(!_isMonopole(),"non monopole alloc");
      _assert(!_t(ptr_),"free but non alloced buffer");
      
      free(ptr_);
      ptr_=null;
      cap_=0;
      
    }

    Void _realloc(Int cap,Bool isCopy=true)
    {
      STRING_PROFILE(++allocCount_;)
      _assert(!_isMonopole(),"non monopole realloc");
      
      if(isCopy)
        ptr_=(char*)realloc(ptr_,cap);
      else
      {
        if(_t(ptr_))
          free(ptr_);
        ptr_=(Char *)malloc(cap);
      }
      
      cap_=cap;
    }
    /*
    Buffer_* _cloneToMonopole(begin,end)
    {
      Buffer_ newBuffer();
      Int newCap=end-begin+capIncrement_;
      
      newBuffer._lock();
      newBuffer._realloc(newCap,false);
      strncpy(newBuffer.ptr_,ptr_+begin,end-begin);
            
      _unLock();
      
      return &newBuffer;
    }
    */

  };
  
  STRING_PROFILE(Static Int totalCopy_;)
  
  Buffer_* buffer_;
  Int begin_;
  //Int end_;
  Int length;
    
  Bool _isEmpty() Const
  {
    return length<=0;
  }

  Bool _isSelf() Const
  {
    return buffer_->_isMonopole();
  }
  Bool _makeSelf(Int cap=-1);
  
  /*
  Int length() const
  {
    return length;
  }
  */
  /*
  Int length() const
  {
    if(length_==-1)
      length_=strlen(str_);
      
    return length_;
  }
  */
    
  Bool _requreCap(Int cap,Bool isCopy=true);
  Void __append(Const Char* begin,Int len=-1);
  String& _append(Const String& str)
  {
    if(_t(str.buffer_))
      __append(str.buffer_->ptr_+str.begin_,str.length);
    
    return *this;
  }
  String& _append(Const Char* str=null,Int len=-1)
  {
    __append(str,len);
    
    return *this;
  }

  String& operator+=(Const String& rhv)
  {
    _append(rhv);
    
    return *this;
  }
  String& operator+=(Const Char* rhv)
  {
    _append(rhv);
    
    return *this;
  }
  String& operator+=(Const Char& rhv)
  {
    _append(&rhv,1);
    
    return *this;
  }
  
  Bool __setAndCopy(Const Char* begin,Int len=-1);
  Bool __setAndNotCopy(Const String* cStrOwner,Int begin,Int len);

  /*
  String& _zerofy()
  {
    _makeSelf();
    
    length=0;
    
    if(cap_>0)
      cStr_[length]=0;
    
    return *this;
  }
  */
  Void __init()
  {
    buffer_=null;
    begin_=0;
    length=0;
  }
    
  String& _set(Const Char* rhv=null,Int len=-1)
  {
    __setAndCopy(rhv,len);
    
    return *this;
  }
  /*
  String& _set(Const String& rhv)
  {
    if(!_t(rhv.buffer_))
    {
      length=0;
      
      return *this;
    }
    
    __setAndCopy(rhv.buffer_->ptr_+rhv.begin_,rhv.length);
    
    // debug
    cout << "String::_set(Const String& rhv) " << begin_;
    
    return *this;
  }
  */
  String& _set(Const String& rhv)
  {
    if(!_t(rhv.buffer_))
    {
      length=0;
      
      return *this;
    }

    __setAndNotCopy(&rhv,rhv.begin_,rhv.length);
    
    return *this;
  }
  
  String()
  {
    __init();
  }

  String(Const Char* lhv)
  {
    __init();

    _set(lhv,-1);
  }
  String(Const Char* lhv,Int len)
  {
    __init();

    _set(lhv,len);
  }
  String(Const String& lhv)
  {
    __init();
    
    _set(lhv);
  }
  ~String()
  {
    if(!_t(buffer_))
      return;
    
    buffer_->_unLock();
    
  }

  String& operator=(Const Char* rhv)
  {
    _set(rhv);
    return *this;
  }
  
  String& operator=(Const String& rhv)
  {
    _set(rhv);

    return *this;
  }
  /*
  String& operator=(String& rhv)
  {
    _set(rhv);

    // debug
    cout << "String::operator=(String& rhv) " << begin_;

    return *this;
  }
  */

  String substr(Int begin=0,Int len=-1)
  {
    String res;
    
    if(_t(buffer_))
      res.__setAndNotCopy(this,begin_+begin,len);
    
    return res;
  }
  String substring(Int begin=0,Int end=-1)
  {
    if(end==-1)
      end=length;
    
    String res;

    if(_t(buffer_))
      res.__setAndNotCopy(this,begin_+begin,end-begin);
    
    return res;
  }
  
  
  Int indexOf(Const String& sub,Int beginIndex=0);
  Int lastIndexOf(Const String& sub,Int endIndex=-1);
  
#if STRING_STD_SUPPORT_ENABLE
  
  // ;)
  std::string _sStr() const
  {
    if(_t(buffer_))
      return std::string(buffer_->ptr_+begin_,length);
    else
      return std::string(); 
  }
#endif  
  
  Char* _cStr(Bool isWrite=true) const 
  {
    if(!_t(buffer_))
      return  null;
    
    if(isWrite && !_isSelf())
      return null;
    
    return buffer_->ptr_+begin_;  
  }
  
  String& operator+=(Int n)
  {
    Int cap=begin_+length+10;
    
    _makeSelf(cap);
    
    _requreCap(cap,true);
    
    sprintf(_cStr()+length,"%d",n);
    length=strlen(_cStr());
    
    return *this;
  }
  
  template<class _C>
  String& operator&(_C c)
  {
    *this+=c;
    
    return *this;
  }
  
};

#endif
