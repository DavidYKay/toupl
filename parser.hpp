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

#ifndef PARSER_HPP
#define PARSER_HPP

#include "common.hpp"
#include <map>
#include <cstdarg>
#include "string.hpp"
#include "args.hpp"

#define Map map

class Parser
{
  public:
  
 
  class ParseRes_;
  class SeekRet_;
  typedef ParseRes_* (Parser::*ParseFunc_)(SeekRet_*);
  
  class Op_
  {
    public:
    
    ParseFunc_ _parse;
    
    String lexBegin_;
    String lexEnd_;
    
    String selfName_;

  };
  
  
  class SeekRet_
  {
    public:
    
    Int pos_;
    Op_ * op_;
    Bool noDelete_;
    
    SeekRet_()
    {
      noDelete_=false;
    }

  };
  
  class ParseRes_
  {

    public:
    
    Int endPos_;

  };

  String text_;
  
  typedef Map<String,Op_ *> OpMap_;
  OpMap_ opMap_;
  
  typedef OpMap_ OpGroup_;
  typedef Map<String,OpGroup_ *> OpGroupMap_;
  OpGroupMap_ opGroupMap_;
    
  Virtual Op_* _createOpClass()
  {
    return new Op_();
  }
  Virtual SeekRet_* _createSeekRetClass()
  {
    return new SeekRet_();
  }
  Virtual ParseRes_* _createParseResClass()
  {
    return new ParseRes_();
  }

  SeekRet_* _noDelete(SeekRet_* sr)
  {
    if(_t(sr))
      sr->noDelete_=true;
    
    return sr;
  }
  SeekRet_* _seekOp(Int begin,Op_ * op);
  SeekRet_* _seekOpEnd(Int begin,Op_ * op);
  SeekRet_* _seekOpGroup(Int begin,OpGroup_* opGroup);
  SeekRet_* _seekTextEnd()
  {
    SeekRet_* sr=new SeekRet_();
    
    sr->pos_=text_.length;
    sr->op_=opMap_["textEnd"];
    
    return sr;
  }

  SeekRet_* _seekMultiLast(Int n,...);

  SeekRet_* _seekMultiFirst(Int n,...);
  
  Void __addOp(Const String& name,Const String& lexBegin,Const String& lexEnd,ParseFunc_ _parse,OpGroup_ * group=null);
  
  Void __addOpToOpGroup(OpGroup_* group,Op_* op)
  {
    OpGroup_& g=(*group);
    g[op->selfName_]=op;
  }
  
  ParseRes_* _parse(String text)
  {
    Op_* root=opMap_["root"];
    
    text_=text;
    
    if(!_t(root))
      return null;
    
    SeekRet_* sr=_createSeekRetClass();
    
    sr->op_=root;
    sr->pos_=0;
    
    return (this->*(root->_parse))(sr);
  }
  
  Void _setup(ArgParser * argp)
  {
    opGroupMap_["all"]=&opMap_;
  }
  
  virtual ~Parser()
  {
  
  }
  
};

#endif
