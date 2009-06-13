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

#include "vb.hpp"

Lang vbLang=
{
  &(::_createLangClass<TouplParser::VB>),
  "vb",
  {".bas",".vb",null}
  
};


namespace TouplParser
{

String VB::__addText(Const String& text)
{
  return String("fpStringBuilder.Append(\"") & _quote(text,quotedParam_) & "\")\n";
}
String VB::__addValue(Const String& value)
{
  return String("fpStringBuilder.Append(") & value & ")\n";
}
String VB::__declareVar(Const String& varName,Const String& varType)
{
  String type;
  
  if(varType=="String")
    type="String";
  else if(varType=="Bool")
    type="Boolean";

  return String("Dim ") & varName & " As " & type & " "  & "\n";
}
String VB::__condBegin(Const String& varName)
{
  return String("If ") & varName & " Then\n";
}
String VB::__condEnd(Const String& varName)
{
  return String("End If\n");
}
// simple. only AND operations
String VB::__condComp(Const Vector<ParseRes_*>& prs)
{
  if(prs.size()==0)
    return null;
  
  String loopId="\'fpVBLoop\n"; 
  String ret="";
  ret & loopId;
  Vector<ParseRes_*>::size_type i;
  
  for(i=0;i<prs.size();++i)
  {
    if(prs[i]->value_.substr(0,loopId.length)==loopId)
      ret & "Do\n" & prs[i]->value_ & prs[i]->varName_ & "=True" & "\nLoop Until True\n";
    else  
      ret & prs[i]->varName_ & "=" & prs[i]->value_ & "\nIf NOT " & prs[i]->testCode_ & " Then Exit Do\n";
  }

  return ret;
}
String VB::__condCompFinal(ParseRes_* pr)
{
  if(!_t(pr))
    return null;

  return String ("Do\n") & pr->value_ & pr->varName_ & "=True" & "\nLoop Until True\n";
}

String VB::__createVar(Int pos)
{
  return String("fpVar") & pos;
}
String VB::__boolVarTestCode(Const String& varName)
{
  return varName;
}
String VB::__varTestCode(Const String& varName)
{
  return String("_fpT(") & varName & ")";
}
Void VB::_setup(ArgParser * argp)
{
  Base::_setup(argp);
}
  
} // namespace TouplParser

