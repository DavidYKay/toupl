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

#ifndef ARGS_HPP
#define ARGS_HPP

#include "common.hpp"
#include "string.hpp"

class ArgParser
{
  public:

  Char Const **  argv_;
  Int argc_;

  private:

  Const Char * name__;
  Const Char * param__;
  Const Char * paramEnd__;
  Const Char * arg__;


  Bool __inCache(Const Char * arg)
  {
    return arg==arg__;
  }
  Void __parse(Const Char * arg);

  String __getName(Const Char * arg)
  {
    if(!__inCache(arg))
      __parse(arg);

    return String(name__,param__-name__-1);
  }
  String __getParam(Const Char * arg)
  {
    if(!__inCache(arg))
      __parse(arg);

    return String(param__,paramEnd__-param__);
  }

  public:

  Bool _get(Const String& name, String& param);
};

#endif
