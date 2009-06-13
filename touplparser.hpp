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

#ifndef TOUPLPARSER_HPP
#define TOUPLPARSER_HPP

#include "common.hpp"
#include <vector>
#include "string.hpp"
#include "parser.hpp"

#define Vector vector

namespace TouplParser
{
class Base:
public Parser
{
   
  public:
  
  class SeekRet_:
  public Parser::SeekRet_
  {
    public:
    
    SeekRet_* nextSR_;

  };

  class Op_:
  public Parser::Op_
  {
    public:
    
    ParseFunc_ _parseToText;

  };

  class ParseRes_:
  public Parser::ParseRes_
  {
    public:
    
    String res_;
    
    // if specific members
    String varName_;
    String value_;
    String testCode_;
    String decVarsCode_;
  };
  
  virtual Op_* _createOpClass()
  {
    return new Op_();
  }
  virtual SeekRet_* _createSeekRetClass()
  {
    return new SeekRet_();
  }
  virtual ParseRes_* _createParseResClass()
  {
    return new ParseRes_();
  }

  
  Virtual String __addText(Const String& text)
  {
    return String();
  }
  Virtual String __addValue(Const String& value)
  {
    return String();
  }
  Virtual String __declareVar(Const String& varName,Const String& varType)
  {
    return String();
  }
  Virtual String __condBegin(Const String& varName)
  {
    return String();
  }
  Virtual String __condEnd(Const String& varName)
  {
    return String();
  }
  // simple. only AND operations
  Virtual String __condComp(Const Vector<ParseRes_*>& prs)
  {
    return String();
  }
  Virtual String __condCompFinal(ParseRes_* pr)
  {
    return String();
  }

  Virtual String __createVar(Int pos)
  {
    return String();
  }
  Virtual String __boolVarTestCode(Const String& varName)
  {
    return String();
  }
  Virtual String __varTestCode(Const String& varName)
  {
    return String();
  }

  
  /*
  __cutComments(text)
  {
    text=text.replace(/\/%[^\0]*%\//g,"");
    text=text.replace(/\/\/%[^\0]*$/g,"");
    
    return text;
  }
  */
  
  Void _logError(Int pos,const String& errorText)
  {
    LineAndCol lc=_posToLineAndCol(text_,pos);
    
    _log(String("Error (line: ") & lc.line_ & ", col: " & lc.col_ & "): " & errorText);
    
  }
  Void _logError(Int pos,const Char* errorText)
  {
    LineAndCol lc=_posToLineAndCol(text_,pos);
    
    _log(String("Error (line: ") & lc.line_ & ", col: " & lc.col_ & "): " & errorText);
    
  }

  Void _logDebug(Int pos,const String& debugText)
  {
    LineAndCol lc=_posToLineAndCol(text_,pos);
    
    _log(String("Debug (line: ") & lc.line_ & ", col: " & lc.col_ & "): " & debugText);
  }
  Void _logDebug(Int pos,const Char* debugText)
  {
    LineAndCol lc=_posToLineAndCol(text_,pos);
    
    _log(String("Debug (line: ") & lc.line_ & ", col: " & lc.col_ & "): " & debugText);
  }
  
  SeekRet_* _seekDefaultOp(Int begin,SeekRet_* nextSR,Op_* op=null);
  
  ParseRes_* __parseDefaultToText(SeekRet_* selfSR);
  
  ParseRes_* __parseDefault(SeekRet_* selfSR);
  

  ParseRes_* __parseBlockCommentToText(SeekRet_* selfSR);
  
  ParseRes_* __parseBlockComment(SeekRet_* selfSR);
  
  ParseRes_* __parseLineCommentToText(SeekRet_* selfSR);
  ParseRes_* __parseLineComment(SeekRet_* selfSR);
 
  ParseRes_* __parseIgnoreOpToText(SeekRet_* selfSR);
  ParseRes_* __parseIgnoreOp(SeekRet_* selfSR);
  
  ParseRes_* __parseCond(SeekRet_* selfSR);


  ParseRes_* __parseText(SeekRet_* selfSR);
  
  ParseRes_* __parseCode(SeekRet_* selfSR);

  ParseRes_* __parseValue(SeekRet_* selfSR);

  ParseRes_* __parseCondOpAnd(SeekRet_* selfSR);
  
  
  ParseRes_* __parseRoot(SeekRet_* selfSR);
  
  /*
  _parse(text)
  {
    var root=opMap_["root"];
    
    code_=text;
    
    if(!_t(root))
      return null;
    
    return root->_parse(0,root);
  }
  */

  
  /* 
  __compileCode(text)
  {
  }
   */
  Virtual Void _setup(ArgParser * argp);
  
  Base()
  {
    
    //quotedCrypt_=new Crypt->Quoted(_fNew(Crypt->Base));
    //quotedCrypt_->defaultMap_=quotedCrypt_->maps_->full_;
  }
  virtual ~Base()
  {
  
  }
  
  
}; // class Base
} // namespace TouplParser

template<class _C>
TouplParser::Base* _createLangClass()
{
  return new _C();
}

struct Lang
{
  TouplParser::Base* (*_create)();
  Char * name_;
  Char * exts_[10];
};

#endif
