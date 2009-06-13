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

#include "js.hpp"

Lang jsLang=
{
  &(::_createLangClass<TouplParser::JS>),
  "javascript",
  {".js",null}
  
};


namespace TouplParser
{

String JS::__addText(Const String& text)
{
  return String("fpText+=\"") & _quote(text) & "\";\n";
}
String JS::__addValue(Const String& value)
{
  return String("fpText+=") & value & ";\n";
}
String JS::__declareVar(Const String& varName,Const String& varType)
{
  return String("var ") & varName & ";\n";
}
String JS::__condBegin(Const String& varName)
{
  return String("if(") & varName & ")\n{\n";
}
String JS::__condEnd(Const String& varName)
{
  return String("}\n");
}
// simple. only AND operations
String JS::__condComp(Const Vector<ParseRes_*>& prs)
{
  if(prs.size()==0)
    return null;
  
  String ret="";
  Vector<ParseRes_*>::size_type i;
  
  for(i=0;i<prs.size()-1;++i)
  {
    ret & "(" & prs[i]->varName_ & "=" & prs[i]->value_ & "," & prs[i]->testCode_ & ") && ";
  }

  ret & "(" & prs[i]->varName_ & "=" & prs[i]->value_ & "," & prs[i]->testCode_ & ")";
  
  return ret;
}
String JS::__condCompFinal(ParseRes_* pr)
{
  if(!_t(pr))
    return null;
  
  return String ("") & pr->varName_ & "=" & pr->value_ & ";\n";
}

String JS::__createVar(Int pos)
{
  return String("fpVar") & pos;
}
String JS::__boolVarTestCode(Const String& varName)
{
  return varName;
}
String JS::__varTestCode(Const String& varName)
{
  return String("_fpT(") & varName & ")";
}
  
} // namespace TouplParser

