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

#include "string.hpp"

STRING_PROFILE(Int String::Buffer_::allocCount_=0;)
STRING_PROFILE(Int String::totalCopy_=0;)

Bool String::_makeSelf(Int cap)
{
  if(!_t(buffer_))
    return false;
  
  if(_isSelf())
    return true;
  
  if(cap==-1)
    cap=length;
  
  if(cap<length)
    length=cap-1;
  
  Buffer_* newBuffer=new Buffer_();
  
  newBuffer->_lock();
  newBuffer->_alloc(cap);
  
  strncpy(newBuffer->ptr_,buffer_->ptr_+begin_,length);
  STRING_PROFILE(totalCopy_+=length;)
  begin_=0;
  buffer_->_unLock();
  buffer_=newBuffer;
  
  *(buffer_->ptr_+begin_+length)=0;
  
  return true;
}


Bool String::_requreCap(Int cap,Bool isCopy)
{
  if(!_t(buffer_))
  {
    buffer_=new Buffer_();
    
    buffer_->_lock();
    buffer_->_alloc(cap);
    begin_=0;
    length=0;
    
    return true;
  }
  
  if(buffer_->cap_<cap)
  {
    if(_isSelf())
    {
      buffer_->_realloc(cap,isCopy);
      
      return true;
    }
    else
      return false;
  }
  
  return true;
}

Void String::__append(Const Char* begin,Int len)
{
  if(!_t(begin))
    return;
  
  if(len==-1)
    len=strlen(begin);
    
  Int cap=length+len+capIncrement_;
  
  _makeSelf(cap);
  
  _requreCap(cap,true);
  
  strncpy(buffer_->ptr_+begin_+length,begin,len);
  STRING_PROFILE(totalCopy_+=len;)
  
  length+=len;
  *(buffer_->ptr_+begin_+length)=0;
}

Bool String::__setAndCopy(Const Char* begin,Int len)
{
  if(!_t(begin))
    return false;
  
  if(len==-1)
    len=strlen(begin);
    
  Int cap=length+len+capIncrement_;
      
  
  if(!_t(buffer_))
  {
    buffer_=new Buffer_();
    
    buffer_->_lock();
    buffer_->_alloc(cap);
    
  }
  if(buffer_->cap_<cap)
  {
    if(_isSelf())
      buffer_->_realloc(cap,false);
    else  
    {
      Buffer_* newBuffer=new Buffer_();

      newBuffer->_lock();
      newBuffer->_alloc(cap);
      
      buffer_->_unLock();
      
      buffer_=newBuffer;
      
    }  
  }
  
  strncpy(buffer_->ptr_,begin,len);
  STRING_PROFILE(totalCopy_+=len;)
  
  begin_=0;
  length=len;
  *(buffer_->ptr_+begin_+length)=0;
  
  return true;
}
Bool String::__setAndNotCopy(Const String* cStrOwner,Int begin,Int len)
{
  _assert(!_t(cStrOwner),"String::__setAndNotCopy:: cStrOwner is null");
  
  if(begin==-1)
    begin=cStrOwner->begin_;
  
  if(len<0)
    len=cStrOwner->length-begin+cStrOwner->begin_;
  
  if(!_t(cStrOwner->buffer_))
  {
    length=0;
    
    return true;
  }
  
  cStrOwner->buffer_->_lock();
  begin_=begin;
  length=len;
  buffer_=cStrOwner->buffer_;
  
  return true;
}
Int String::indexOf(Const String& sub,Int beginIndex)
{
  if(!_t(buffer_))
    return -1;
  
  if(beginIndex<0)
    beginIndex=0;
    
  if(!_t(sub.buffer_))
    return beginIndex;
    
  
  Char* ptr=strstr(buffer_->ptr_+begin_+beginIndex,sub.buffer_->ptr_);
  
  return _t(ptr)?ptr-buffer_->ptr_-begin_:-1;
}
Int String::lastIndexOf(Const String& sub,Int endIndex)
{
  if(!_t(buffer_))
    return -1;

  if(endIndex==-1)
    endIndex=length;

  if(!_t(sub.buffer_))
    return endIndex;
    
  if(length<sub.length)
    return -1;
  
  if(length==sub.length)
    return sub==(*this);
  
  Char* begin=buffer_->ptr_+begin_,* end=begin+endIndex;
  Char* subBegin=sub.buffer_->ptr_+sub.begin_,* subEnd=subBegin+sub.length;
  Char* ptr=end-sub.length-1;
  Char c=*(subEnd-1);
  Int ret=1;
  
  while(ptr>=begin && ret!=0)
  {
    while(ptr>=begin && *ptr!=c)
      --ptr;
    
    if(ptr<begin)
      break;
    
    ret=strncmp(ptr,subBegin,sub.length);
  }
  
  return ptr>=begin?ptr-begin:-1;
}

Bool operator<(Const String& a,Const String& b)
{
  if(!_t(a.buffer_) && !_t(b.buffer_))
    return false;
  
  if(_t(a.buffer_) && !_t(b.buffer_))
    return false;
    
  if(!_t(a.buffer_) && _t(b.buffer_))
    return true;
  
  if(_t(a.buffer_) && _t(b.buffer_))
  {
    Int ret=strncmp(a.buffer_->ptr_+a.begin_,b.buffer_->ptr_+b.begin_,_min(a.length,b.length));
    
    if(ret<0)
      return true;
    
    if(ret==0)
      return a.length < b.length;
  }
  
  return false;  
}
Bool operator<=(Const String& a,Const String& b)
{
  if(!_t(a.buffer_) && !_t(b.buffer_))
    return true;
  
  if(_t(a.buffer_) && !_t(b.buffer_))
    return false;
    
  if(!_t(a.buffer_) && _t(b.buffer_))
    return true;
  
  if(_t(a.buffer_) && _t(b.buffer_))
  {
    Int ret=strncmp(a.buffer_->ptr_+a.begin_,b.buffer_->ptr_+b.begin_,_min(a.length,b.length));
  
    if(ret<=0)
      return true;
    
    if(ret==0)
      return a.length <= b.length;

  }
    
  return false;
}
Bool operator==(Const String& a,Const String& b)
{
  if(!_t(a.buffer_) && !_t(b.buffer_))
    return true;
  
  if(_t(a.buffer_) && !_t(b.buffer_))
    return false;
    
  if(!_t(a.buffer_) && _t(b.buffer_))
    return false;
  
  if(_t(a.buffer_) && _t(b.buffer_))
  {
    Int ret=strncmp(a.buffer_->ptr_+a.begin_,b.buffer_->ptr_+b.begin_,_min(a.length,b.length));
  
    if(ret==0 && a.length == b.length)
      return true;
  }

  return false;
}
Bool operator>(Const String& a,Const String& b)
{
  return !(b<=a);
}
Bool operator>=(Const String& a,Const String& b)
{
  return !(b<a);
}
Bool operator!=(Const String& a,Const String& b)
{
  return !(b==a);
}

#if STRING_STD_SUPPORT_ENABLE
std::ostream& operator<<(std::ostream& s,const String& str)
{
  if(_t(str.buffer_))
    s.write(str.buffer_->ptr_+str.begin_,str.length);
  
  return s;
}
#endif
