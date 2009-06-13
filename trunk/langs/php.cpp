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

#include "php.hpp"

Lang phpLang=
{
  &(::_createLangClass<TouplParser::PHP>),
  "php",
  {".php",null}
  
};


namespace TouplParser
{

String PHP::__addText(Const String& text)
{
  return text; //String("$fpText+=\"") & _quote(text) & "\";\n";
}
String PHP::__addValue(Const String& value)
{
  Char * ptr=value._cStr(false);
  
  return String("<?php echo ") & (_t(ptr) && *ptr!='$'?"$":"") & value & "?>\n";
}
String PHP::__declareVar(Const String& varName,Const String& varType)
{
  /*
  String type;
  if(varType=="String")
    type=stringClassName;
  else if(varType=="Bool")
    type="bool";
  */
  return String("");// & type & " " & varName & ";\n";
}
String PHP::__condBegin(Const String& varName)
{
  return String("<?php if(") & varName & ")\n{\n?>";
}
String PHP::__condEnd(Const String& varName)
{
  return String("<?php } ?>");
}
// simple. only AND operations
String PHP::__condComp(Const Vector<ParseRes_*>& prs)
{
  if(prs.size()==0)
    return null;
  
  String ret="";
  Vector<ParseRes_*>::size_type i;
  Bool isNotComplex;
  Char *ptr;
  
  for(i=0;i<prs.size()-1;++i)
  {
    ptr=prs[i]->value_._cStr(false);
    
    ret & "(" & prs[i]->varName_ & "=" & (_t(ptr) && *ptr!='(' ?"$":"") & 
    prs[i]->value_ & "," & prs[i]->testCode_ & ") && ";
  }

  ptr=prs[i]->value_._cStr(false);

  ret & "(" & prs[i]->varName_ & "=" & (_t(ptr) && *ptr!='(' ?"$":"" ?"$":"") & 
  prs[i]->value_ & "," & prs[i]->testCode_ & ")";
  
  return ret;
}
String PHP::__condCompFinal(ParseRes_* pr)
{
  if(!_t(pr))
    return null;
  
  return String ("<?php ") & pr->varName_ & "=" & pr->value_ & "?>";
}

String PHP::__createVar(Int pos)
{
  return String("$fpVar") & pos;
}
String PHP::__boolVarTestCode(Const String& varName)
{
  return varName;
}
String PHP::__varTestCode(Const String& varName)
{
  return String("_fpT(") & varName & ")";
}
Void PHP::_setup(ArgParser * argp)
{
  /*
  if(!argp->_get("-stringclassname",stringClassName))
    stringClassName="std::string";
  */
  Base::_setup(argp);
}
  
} // namespace TouplParser

