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

#include "args.hpp"

Void ArgParser:: __parse(Const Char * arg)
{
  Const Char * p=arg;
  Bool isQuote=false;

  if(arg[0]=='\"')
  {
    //cout << "quote";
    isQuote=true;
    p++;
  }

  name__=p;

  Char * p2=strchr(p,':');

  if(!p2)
  {
    param__=p+strlen(p);
    paramEnd__=param__;
  }
  else
  {
    param__=p2+1;
    paramEnd__=param__+strlen(param__);

    if(isQuote && paramEnd__>param__)
      paramEnd__--;
  }

}

Bool ArgParser::_get(Const String& name, String& param)
{
  for(int i=1;i<argc_;i++)
  {
    if(__getName(argv_[i])==name)
    {
      param=__getParam(argv_[i]);

      return true;
    }
  }

  return false;
}
