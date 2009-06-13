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

#include "common.hpp"

#include <stdio.h>

#include "string.hpp"
#include "quoted.hpp"
#include "parser.hpp"
#include "touplparser.hpp"
#include "args.hpp"

#include "langs/js.hpp"
#include "langs/cpp.hpp"
#include "langs/java.hpp"
#include "langs/csharp.hpp"
#include "langs/python.hpp"
#include "langs/php.hpp"
#include "langs/lua.hpp"
#include "langs/vb.hpp"


Lang* langs[]=
{
  &jsLang,
  &cppLang,
  &javaLang,
  &cSharpLang,
  &pythonLang,
  &phpLang,
  &luaLang,
  &vbLang
};


using namespace std;

Const Char* slash="\\";

Void _log(Const String& msg)
{
  fwrite(msg._cStr(false),msg.length,1,stdout);
  fputc('\n',stdout);
}
Void _log(Const Char* msg)
{
  fputs(msg,stdout);
  fputc('\n',stdout);
}

LineAndCol _posToLineAndCol(String& str,Int pos,Int tabSpacesLength)
{
  LineAndCol lc={1,1};
  
  if(pos<=0)
    return lc;
  
  Int i=0,j;
  Int line=-1;
  String temp;
  
  temp._set("\n");
  while(i!=-1 && i<pos)
  {
    j=i;
    i=str.indexOf(temp,i+1);
    ++line;
  }
  
  Int col=0;

  i=j;
  
  temp._set("\t");

  while(i!=-1 && i<pos)
  {
    col+=i-j;
    j=i;
    i=str.indexOf(temp,i+1);
    col+=tabSpacesLength;
  }
  
  col+=pos-j;
  
  col-=tabSpacesLength;
  
  lc.line_=line+1;
  lc.col_=col;
  
  return lc;
}

Const Char* help=""
"Toupl v 0.9\n"
"Usage toupl {param:value|\"param:value_with_whitespaces\"}\n"
"Params:\n"
"\t-infile\t\tInput file\n"
"\t-outfile\tOutput file or \"auto\"(cut .toupl extention) else stdout\n"
"\t-lang\t\tInput file language or auto (by extention)\n"
"List of supported languages:\n"
"\tname\t\t-lang option\n"
"\tJavaScript\tjavascript\n"
"\tC++\t\tcpp\n"
"\tJava\t\tjava\n"
"\tC#\t\tcsharp\n"
"\tPython\t\tpython\n"
"\tPHP\t\tphp\n"
"\tLua\t\tlua\n"
"\tVisualBasic\tvb\n"
"C++ Params\n"
"\t-stringclassname\t\tWork string class or std::string\n"
"Python Params\n"
"\t-indent\t\t{s|t}count,s=space,t=tabs\n";


Int main(Int argc, Char ** argv )
{
  // config
  String selfExt(".toupl");
  
  ArgParser argp;
  
  argp.argc_=argc;
  argp.argv_=(Const Char**)argv;
  
  String temp;

  // Input file
  FILE* inFile=null;
  
  if(argp._get("-infile",temp))
  {
    temp._makeSelf();
    inFile=fopen(temp._cStr(),"rt");
  }
  if(!_t(inFile))
  {
    _log(help);
    
    return 1;
  }

  // Output file
  FILE* outFile=null;

  if(argp._get("-outfile",temp))
  {
    if(temp=="auto")
    {
      argp._get("-infile",temp);
      
      Int i=temp.lastIndexOf(slash);
      Int j=temp.lastIndexOf(".");
      
      if(i==-1)
        i=0;
      if(j==-1)
        j=temp.length;
      if(i>=j)
        j=i;
      
      temp=temp.substring(i,j);
    }
    
    temp._makeSelf();
    outFile=fopen(temp._cStr(),"wt");
  }
  if(!_t(outFile))
  {
    _log("Output File not pointed or can not open for write. Using stdout");
    
    outFile=stdout;
  }


  // Language option
  Int langIndex=-1;
  
  if(argp._get("-lang",temp))
  {
    temp._makeSelf();
  
    Int i=0,iEnd=sizeof(langs)/sizeof(langs[0]);
    
    while(i<iEnd)
    {
      if(strcmp(langs[i]->name_,temp._cStr())==0)
        break;
      ++i;  
    }
    
    if(i<iEnd)
      langIndex=i;
  }
  else
  {
    String ext;
    Int i=temp.length,j;
    Int k=temp.lastIndexOf(slash);
    
    if(k==-1)
      k=0;
    
    do
    {
      j=i;
      i=temp.lastIndexOf(".",i-1);
      
      if(i==-1)
        i=k;

      ext=temp.substring(i,j);
    }
    while(i>k && ext==selfExt);
    
    Int iEnd=sizeof(langs)/sizeof(langs[0]);
    
    ext._makeSelf();
    i=0;
    
    while(i<iEnd)
    {
      Char ** langExts=langs[i]->exts_;
      
      j=0;
      
      while(_t(langExts[j]))
      {
        if(strcmp(langExts[j],ext._cStr())==0)
          break;
        ++j;
      }
      
      if(_t(langExts[j]))
        break;
      
      ++i;  
    }
    
    if(i<iEnd)
      langIndex=i;

  }
  
  if(langIndex==-1)
  {
    _log("Can not detect language. Use option -lang or correct file extention.");
    
    return 2;
  }
  else
  {
    _log("Using language ");
    _log(langs[langIndex]->name_);
  }
  
  // create parser class
  
  _log("Creating parser class");
  TouplParser::Base* parser=langs[langIndex]->_create();
  
  parser->_setup(&argp);

  
  // read input file
  Long inFileSize;
  
  fseek(inFile,0,SEEK_END);
  inFileSize=ftell(inFile);
  
  String text;
  
  text._requreCap(inFileSize+1);
  
  _log("Reading input file");
  
  fseek(inFile,0,SEEK_SET);
  
  Int inFileReadedSize=fread(text._cStr(),1,inFileSize,inFile);
  
  text.length=inFileReadedSize;
  *(text._cStr()+inFileReadedSize)=0;
  
  // parse input file
  
  TouplParser::Base::ParseRes_* pr=null;//* parser->_createParseResClass();
  
  _log("Begin parsing input file...");
  
  pr=(TouplParser::Base::ParseRes_ *)parser->_parse(text);
  
  if(_t(pr))
  {
    pr->res_._makeSelf();
    fwrite(pr->res_._cStr(),1,pr->res_.length,outFile);
    
    delete pr;
  }
  else
    _log("Error parsing input file");
  
  // free all
  
  delete parser;
  
  fclose(inFile);
  
  if(outFile!=stdout)
    fclose(outFile);
   
  STRING_PROFILE(printf("String::Buffer_::allocCount_ = %d\n",String::Buffer_::allocCount_); )
  STRING_PROFILE(printf("String::totalCopy_= %d\n",String::totalCopy_);)
  
  return 0;
}
