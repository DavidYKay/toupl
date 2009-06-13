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

#include "quoted.hpp"

String _quote(Const String& s,Const Char * rp)
{
  String res;
  
  res._requreCap(s.length);
  
  Char* i=s._cStr(false),* iEnd=i+s.length;
  
  while(i<iEnd)
  {
    Char c=*i;
    
    Const Char* j=rp;
    
    while(*j)
    {
      if(*j==c)
        break;
      
      while(*j)
        ++j;
      ++j;
      while(*j)
        ++j;
      ++j;  
    }
    
    if(*j==0)
    {
      res+=c;
    }
    else
    {
      while(*j)
        ++j;
      ++j;
     res+=j;   
    }
    
    ++i;
  }
  
  return res;
}
