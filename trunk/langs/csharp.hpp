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

#ifndef CSHARP_HPP
#define CSHARP_HPP

#include "../common.hpp"
#include "../string.hpp"
#include "../touplparser.hpp"
#include "../quoted.hpp"

extern Lang cSharpLang;

namespace TouplParser
{

class CSharp:
public Base
{
  public:
  
  Virtual String __addText(Const String& text);
  Virtual String __addValue(Const String& value);
  Virtual String __declareVar(Const String& varName,Const String& varType);
  Virtual String __condBegin(Const String& varName);
  Virtual String __condEnd(Const String& varName);
  Virtual String __condComp(Const Vector<ParseRes_*>& prs);
  Virtual String __condCompFinal(ParseRes_* pr);

  Virtual String __createVar(Int pos);
  Virtual String __boolVarTestCode(Const String& varName);
  Virtual String __varTestCode(Const String& varName);

  Virtual Void _setup(ArgParser * argp);
  
};// class CSharp
} // namespace TouplParser

#endif
