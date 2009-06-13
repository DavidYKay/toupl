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

#include "python.hpp"

Lang pythonLang=
{
  &(::_createLangClass<TouplParser::Python>),
  "python",
  {".py",null}
  
};


namespace TouplParser
{

String Python::_indent()
{
  Int i=0,iEnd=curIndent_*charCount_;
  String res;
  
  res._requreCap(iEnd+1);
  memset(res._cStr(),char_,iEnd);
  *(res._cStr()+iEnd)=0;
  res.length=iEnd;
  
  return res;
}

String Python::__addText(Const String& text)
{
  return _indent() & "fpText+=\'" & _quote(text) & "\'\n";
}
String Python::__addValue(Const String& value)
{
  return _indent() & "fpText+=" & value & "\n";
}
String Python::__declareVar(Const String& varName,Const String& varType)
{
  /*
  String type;
  if(varType=="String")
    type="str";
  else if(varType=="Bool")
    type="Boolean";
  */
  
  return "";//_indent() & " " & varName & "\n";
}
String Python::__condBegin(Const String& varName)
{
  String res=_indent() & "if " & varName & ":\n";
  
  ++curIndent_;
  
  return res;
}
String Python::__condEnd(Const String& varName)
{
  --curIndent_;
  
  String res="";//_indent() & "\n";

  return res;
}
// simple. only AND operations
String Python::__condComp(Const Vector<ParseRes_*>& prs)
{
  if(prs.size()==0)
    return null;
  
  String ret="";
  Vector<ParseRes_*>::size_type i;
  
  for(i=0;i<prs.size()-1;++i)
  {
    ret & "(" & prs[i]->varName_ & "=" & prs[i]->value_ & "," & prs[i]->testCode_ & ")[1] && ";
  }

  ret & "(" & prs[i]->varName_ & "=" & prs[i]->value_ & "," & prs[i]->testCode_ & ")[1]";
  
  return ret;
}
String Python::__condCompFinal(ParseRes_* pr)
{
  if(!_t(pr))
    return null;
  
  return _indent() & pr->varName_ & "=" & pr->value_ & "\n";
}

String Python::__createVar(Int pos)
{
  return String("fpVar") & pos;
}
String Python::__boolVarTestCode(Const String& varName)
{
  return varName;
}
String Python::__varTestCode(Const String& varName)
{
  return String("_fpT(") & varName & ")";
}
Void Python::_setup(ArgParser * argp)
{
  String indent;
  
  if(argp->_get("-indent",indent))
  {
    Char * ptr=indent._cStr();
    
    if(*ptr=='s')
      char_=' ';
    else if(*ptr=='t')
      char_='\t';
      
    ++ptr;
    Int temp=atoi(ptr);
    
    if(temp!=0)
      charCount_=temp;
  }  
  
  Base::_setup(argp);
}
  
} // namespace TouplParser

