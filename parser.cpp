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

#include "parser.hpp"

Parser::SeekRet_* Parser::_seekOp(Int begin,Parser::Op_ * op)
{
  if(!_t(op))
    return null;
  
  if(op->lexBegin_.length==0)
    return null;  
  
  Int pos=text_.indexOf(op->lexBegin_,begin);

  if(pos==-1)
    return null;

  SeekRet_* sr=_createSeekRetClass();
  sr->pos_=pos;
  sr->op_=op;
  
  return sr;
}
Parser::SeekRet_* Parser::_seekOpEnd(Int begin,Parser::Op_ * op)
{
  if(!_t(op))
    return null;
  
  if(op->lexEnd_.length==0)
    return null;

  Int pos=text_.indexOf(op->lexEnd_,begin);
  
  if(pos==-1)
    return null;
  
  SeekRet_ * sr=_createSeekRetClass();
  
  sr->pos_=pos;
  sr->op_=op;
  
  return sr;
}
Parser::SeekRet_* Parser::_seekOpGroup(Int begin,Parser::OpGroup_* opGroup)
{
  if(!_t(opGroup))
    return null;
  
  OpGroup_::iterator i=opGroup->begin(),iEnd=opGroup->end();
  SeekRet_ * sr=_createSeekRetClass();
  sr->pos_=text_.length;
  sr->op_=null;
  
  SeekRet_ * sr2;
  
  while(i!=iEnd)
  {
    sr2=_seekOp(begin,(*i).second);
    
    if(_t(sr2) && sr2->pos_ < sr->pos_)
    {
      delete sr;
      sr=sr2;
    }
    ++i;
  }
  
  if(!_t(sr->op_))
  {
    delete sr;
    
    return null;
  }
  
  return sr;
}

Parser::SeekRet_* Parser::_seekMultiLast(Int n,...)
{
  SeekRet_* sr=_createSeekRetClass(),* argSR=null;
  
  sr->pos_=text_.length;
  sr->op_=null;
  
  va_list args;
  va_start(args,n);
  
  while(n-- && _t(sr))
  {
    argSR=va_arg(args,SeekRet_*);
    if(_t(argSR))
    {
      if(sr->pos_>=argSR->pos_)
      {
        if(!sr->noDelete_)
        {
          //cout << "D\n";
          
          delete sr;
        }
        sr=argSR;
      }
      else
        if(!sr->noDelete_)
        {
          //cout << "D\n";
          
          delete argSR;
        }  
    }
  }
  
  va_end(args);
  
  return _t(sr->op_)?sr:null;
}

Parser::SeekRet_* Parser::_seekMultiFirst(Int n,...)
{
  SeekRet_* sr=_createSeekRetClass(),* argSR=null;
  
  sr->pos_=text_.length;
  sr->op_=null;
  
  va_list args;
  va_start(args,n);
  
  while(n-- && _t(sr))
  {
    argSR=va_arg(args,SeekRet_*);
    if(_t(argSR))
    {
      if(sr->pos_>argSR->pos_)
      {
        if(!sr->noDelete_)
        {
          //cout << "D\n";
          
          delete sr;
        }
        sr=argSR;
      }
      else
        if(!sr->noDelete_)
        {
          //cout << "D\n";
          
          delete argSR;
        }  
    }
  }
  
  va_end(args);
  
  return _t(sr->op_)?sr:null;
}

Void Parser::__addOp(Const String& name,Const String& lexBegin,
Const String& lexEnd,ParseFunc_ _parse,OpGroup_ * group)
{
  if(!_t(group))
    group=&opMap_;
  
  Op_* op=(*group)[name];
  
  if(!_t(op))
  {
    op=_createOpClass();
    (*group)[name]=op;
  }
  
  op->lexBegin_=lexBegin;
  op->lexEnd_=lexEnd;
  op->_parse=_parse;
  op->selfName_=name;
}
