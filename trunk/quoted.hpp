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

#ifndef QUOTED_HPP
#define QUOTED_HPP

#include "common.hpp"
#include "string.hpp"

String _quote(Const String& s,Const Char * rp=""
"\n\0\\n\0"
"\r\0\\r\0"
"\\\0\\\\\0"
"\'\0\\\'\0"
"\"\0\\\"\0"
"\t\0\\t\0"
"\f\0\\f\0"
"\b\0\\b\0"
"\a\0\\a\0"
"\v\0\\v\0\0"
);

#endif
