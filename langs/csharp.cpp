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

#include "csharp.hpp"

Lang cSharpLang=
{
  &(::_createLangClass<TouplParser::CSharp>),
  "csharp",
  {".cs",null}
  
};


namespace TouplParser
{

String CSharp::__addText(Const String& text)
{
  return String("fpText+=\"") & _quote(text) & "\";\n";
}
String CSharp::__addValue(Const String& value)
{
  return String("fpText+=") & value & ";\n";
}
String CSharp::__declareVar(Const String& varName,Const String& varType)
{
  String type;
  
  if(varType=="String")
    type="String";
  if(varType=="Bool")
    type="Boolean";

  return String("") & type & " " & varName & ";\n";
}
String CSharp::__condBegin(Const String& varName)
{
  return String("if(") & varName & ")\n{\n";
}
String CSharp::__condEnd(Const String& varName)
{
  return String("}\n");
}
// simple. only AND operations
String CSharp::__condComp(Const Vector<ParseRes_*>& prs)
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
String CSharp::__condCompFinal(ParseRes_* pr)
{
  if(!_t(pr))
    return null;
  
  return String ("") & pr->varName_ & "=" & pr->value_ & ";\n";
}

String CSharp::__createVar(Int pos)
{
  return String("fpVar") & pos;
}
String CSharp::__boolVarTestCode(Const String& varName)
{
  return varName;
}
String CSharp::__varTestCode(Const String& varName)
{
  return String("_fpT(") & varName & ")";
}
Void CSharp::_setup(ArgParser * argp)
{
  Base::_setup(argp);
}
  
} // namespace TouplParser

