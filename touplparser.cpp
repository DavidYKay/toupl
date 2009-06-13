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

#include "touplparser.hpp"

namespace TouplParser
{

Base::SeekRet_* Base::_seekDefaultOp(Int begin,Base::SeekRet_* nextSR,Base::Op_* op)
{
  if(!_t(op))
    op=(Op_* )opMap_["default"];
  
  SeekRet_* sr=_createSeekRetClass();
  
  sr->pos_=begin;
  sr->op_=op;
  sr->nextSR_=nextSR;
  
  return sr;
}


Base::ParseRes_* Base::__parseDefaultToText(Base::SeekRet_* selfSR)
{
  Op_* selfOp=(Op_* )selfSR->op_;
  Int begin=selfSR->pos_;

  DEBUG(_logDebug(begin,"__parseDefaultToText");)

  ParseRes_* pr=_createParseResClass();
  SeekRet_* sr=(SeekRet_*)_seekMultiLast(2,selfSR->nextSR_,_seekTextEnd());
  
  // if(!_t(sr))
    // pr.endPos_=text_.length;
  // else
  pr->endPos_=sr->pos_;
  
  pr->res_=text_.substring(selfSR->pos_,pr->endPos_);
  
  return pr;
}
Base::ParseRes_* Base::__parseDefault(Base::SeekRet_* selfSR)
{
  Op_* selfOp=(Op_*)selfSR->op_;
  Int begin=selfSR->pos_;

  DEBUG(_logDebug(begin,"__parseDefault");)

  ParseRes_* pr=(ParseRes_*)(this->*(selfOp->_parseToText))(selfSR);
  
  if(!_t(pr))
    return pr;
  
  pr->res_=__addText(pr->res_);
  
  return pr;
}
Base::ParseRes_* Base::__parseBlockCommentToText(Base::SeekRet_* selfSR)
{
  Op_* selfOp=(Op_*)selfSR->op_;
  Int begin=selfSR->pos_;
  
  DEBUG(_logDebug(begin,"__parseBlockCommentToText");)

  ParseRes_* pr=_createParseResClass();
  SeekRet_* sr=(SeekRet_*)_seekOpEnd(begin,selfOp);
  
  if(!_t(sr))
  {
    _logError(begin,"block comment not ends");
    _delete(pr);
    
    return null;
  }  
  
  pr->res_="";
  pr->endPos_=sr->pos_+selfOp->lexEnd_.length;
  
  return pr;
}
Base::ParseRes_* Base::__parseBlockComment(Base::SeekRet_* selfSR)
{
  Op_* selfOp=(Op_*)selfSR->op_;
  Int begin=selfSR->pos_;

  DEBUG(_logDebug(begin,"__parseBlockComment");)

  ParseRes_* pr=(ParseRes_*)(this->*(selfOp->_parseToText))(selfSR);
  
  if(!_t(pr))
    return pr;
  
  //pr->var_="true";
  
  return pr;
}

Base::ParseRes_* Base::__parseLineCommentToText(Base::SeekRet_* selfSR)
{
  Op_* selfOp=(Op_*)selfSR->op_;
  Int begin=selfSR->pos_;

  DEBUG(_logDebug(begin,"__parseLineCommentToText");)

  ParseRes_* pr=_createParseResClass();
  SeekRet_* sr=(SeekRet_*)_seekMultiLast(2,_seekOpEnd(begin,selfOp),_seekTextEnd());
  
  if(!_t(sr))
    _logError(begin,"line comment not ends");
    
  pr->res_="";
  pr->endPos_=sr->pos_;//+selfOp->lexEnd_->length;
  
  return pr;
}
Base::ParseRes_* Base::__parseLineComment(Base::SeekRet_* selfSR)
{
  Op_* selfOp=(Op_*)selfSR->op_;
  Int begin=selfSR->pos_;

  DEBUG(_logDebug(begin,"__parseLineComment");)

  ParseRes_* pr=(ParseRes_*)(this->*(selfOp->_parseToText))(selfSR);
  
  if(!_t(pr))
    return pr;
  
  return pr;
}

Base::ParseRes_* Base::__parseIgnoreOpToText(Base::SeekRet_* selfSR)
{
  Op_* selfOp=(Op_*)selfSR->op_;
  Int begin=selfSR->pos_;

  DEBUG(_logDebug(begin,"__parseIgnoreOpToText");)

  ParseRes_* pr=_createParseResClass();
  SeekRet_* sr=null;
  Int i=begin+selfOp->lexBegin_.length;

  pr->res_="";

  do
  {
    _delete(sr);
    sr=(SeekRet_*)_seekOpEnd(i,selfOp);
    
    if(!_t(sr))
      break;
    
    pr->res_+=text_.substring(i,sr->pos_);
    i=sr->pos_;
    i+=selfOp->lexEnd_.length;
    
    if(text_.substr(i,selfOp->lexEnd_.length)==selfOp->lexEnd_)
    {
      pr->res_+=selfOp->lexEnd_;
      i+=selfOp->lexEnd_.length;
    }
    else
      break;

  }
  while(_t(sr));
  
  if(!_t(sr))
  {
    _logError(begin,"ignoreOp not ends");
    _delete(pr);
    
    return null;
  }
  
  pr->endPos_=i;
  
  return pr;
}
Base::ParseRes_* Base::__parseIgnoreOp(Base::SeekRet_* selfSR)
{
  Op_* selfOp=(Op_*)selfSR->op_;
  Int begin=selfSR->pos_;

  DEBUG(_logDebug(begin,"__parseIgnoreOp");)
  
  ParseRes_* pr=(ParseRes_*)(this->*(selfOp->_parseToText))(selfSR);
  
  if(!_t(pr))
    return pr;
  
  pr->res_=__addText(pr->res_);
  
  return pr;
}

Base::ParseRes_* Base::__parseCond(Base::SeekRet_* selfSR)
{
  Op_* selfOp=(Op_*)selfSR->op_;
  Int begin=selfSR->pos_;

  DEBUG(_logDebug(begin,"__parseCond");)
  
  ParseRes_* pr=_createParseResClass();
  ParseRes_* prTemp=_createParseResClass();
  SeekRet_* sr=null,* endSR=null,* groupSR=null,* defaultSR=null;
  Int i=begin+selfOp->lexBegin_.length;
  vector<ParseRes_*> prs;
  prs.reserve(4);
  
  pr->varName_=__createVar(begin);
  pr->decVarsCode_=__declareVar(pr->varName_,"Bool");
  pr->res_=__condBegin(pr->varName_);
      
  do
  {
    endSR=(SeekRet_*)_noDelete(_seekOpEnd(i,selfOp));
    groupSR=(SeekRet_*)_noDelete(_seekOpGroup(i,opGroupMap_["all"]));
    sr=(SeekRet_*)_seekMultiLast(2,groupSR,endSR);
    defaultSR=(SeekRet_*)_noDelete(_seekDefaultOp(i,sr));
    sr=(SeekRet_*)_seekMultiFirst(2,sr,defaultSR);

    if(!_t(sr))
      break;
      
    if(sr==endSR)
      break;
      
    DEBUG(_logDebug(sr->pos_,String("__parseCond:: op=") & sr->op_->selfName_ & " begins");)

    prTemp=(ParseRes_*)(this->*(sr->op_->_parse))(sr);

    if(!_t(prTemp))
      break;
    
    DEBUG(_logDebug(prTemp->endPos_,String("__parseCond:: op=") & sr->op_->selfName_ & " ends");)
    //cout << prTemp << " " << prTemp->varName_ << "\n";
    pr->res_+=prTemp->res_;
          
    i=prTemp->endPos_;
    
    if(_t(prTemp->varName_))
    {
      prs.push_back(prTemp);
      //cout << prTemp << " " << prTemp->varName_ << "\n";
      pr->decVarsCode_+=prTemp->decVarsCode_;
    }
    else
      _delete(prTemp);
    
    _delete(groupSR);
    _delete(endSR);
    _delete(defaultSR);
          
  }
  while(/* _t(sr) &&  _t(prTemp) && */ i<text_.length );

  Bool isNotEnd=!_t(sr) || sr!=endSR;
  
  _delete(groupSR);
  _delete(endSR);
  _delete(defaultSR);


  if(isNotEnd)
  {
    _logError(begin,"if not ends");
    _delete(pr);
    
    return null;
  }
  
  //cout << prs.size() << "\n";
  pr->value_=__condComp(prs);
  
  if(_t(pr->value_))
  {
    pr->testCode_=__boolVarTestCode(pr->varName_);
  }
  else
  {
    pr->value_="true";
    pr->testCode_="true";
  }

  pr->res_+=__condEnd(pr->varName_);
  
  pr->endPos_=i+selfOp->lexEnd_.length;
  
  return pr;
}


Base::ParseRes_* Base::__parseText(Base::SeekRet_* selfSR)
{
  Op_* selfOp=(Op_*)selfSR->op_;
  Int begin=selfSR->pos_;

  DEBUG(_logDebug(begin,"__parseText");)

  ParseRes_* pr=_createParseResClass();
  ParseRes_* prTemp=null;
  SeekRet_* sr=null,* endSR=null,* defaultSR=null,* groupSR=null;
  Int i=begin+selfOp->lexBegin_.length;
  
  pr->res_="";
  
  do
  {
    endSR=(SeekRet_*)_noDelete(_seekOpEnd(i,selfOp));
    groupSR=(SeekRet_*)_noDelete(_seekOpGroup(i,opGroupMap_["nonOp"]));
    sr=(SeekRet_*)_seekMultiLast(2,groupSR,endSR);
    defaultSR=(SeekRet_*)_noDelete(_seekDefaultOp(i,sr));
    sr=(SeekRet_*)_seekMultiFirst(2,sr,defaultSR);
    
    //cout << "groupSR " << groupSR << "\n";
    //cout << "endSR " << endSR << "\n";
    //cout << "defaultSR " << defaultSR << "\n";

    if(!_t(sr))
      break;
    
    if(sr==endSR)
      break;

    DEBUG(_logDebug(sr->pos_,String("__parseText:: op=") & sr->op_->selfName_ & " begins");)

    prTemp=(ParseRes_*)(this->*(static_cast<Op_*>(sr->op_)->_parseToText))(sr);
    if(!_t(prTemp))
      break;
    
    DEBUG(_logDebug(prTemp->endPos_,String("__parseText:: op=") & sr->op_->selfName_ & " ends");)

    pr->res_+=prTemp->res_;
    i=prTemp->endPos_;
    
    _delete(prTemp);
    
    _delete(groupSR);
    _delete(endSR);
    _delete(defaultSR);

  }
  while(/* _t(sr) &&  _t(prTemp) && */i<text_.length );

  Bool isNotEnd=!_t(sr) || sr!=endSR;

  // cleanup
  _delete(groupSR);
  _delete(endSR);
  _delete(defaultSR);
  _delete(prTemp);


  if(isNotEnd)
  {
    _delete(pr);
    
    return null;
  }
    
  pr->endPos_=i+selfOp->lexEnd_.length;
  
  return pr;
}

Base::ParseRes_* Base::__parseCode(Base::SeekRet_* selfSR)
{
  Op_* selfOp=(Op_*)selfSR->op_;
  Int begin=selfSR->pos_;

  DEBUG(_logDebug(begin,"__parseCode");)

  ParseRes_* pr=__parseText(selfSR);
  
  if(!_t(pr))
  {
    _logError(begin,"code not ends");

    return pr;
  }
  
  return pr;
}

Base::ParseRes_* Base::__parseValue(Base::SeekRet_* selfSR)
{
  Op_* selfOp=(Op_*)selfSR->op_;
  Int begin=selfSR->pos_;

  DEBUG(_logDebug(begin,"__parseValue");)

  ParseRes_* pr=__parseText(selfSR);
  
  if(!_t(pr))
  {
    _logError(begin,"value not ends");

    return pr;
  }
  
  pr->res_=__addValue(pr->res_);
  
  return pr;
}

Base::ParseRes_* Base::__parseCondOpAnd(Base::SeekRet_* selfSR)
{
  Op_* selfOp=(Op_*)selfSR->op_;
  Int begin=selfSR->pos_;

  DEBUG(_logDebug(begin,"__parseCondOpAnd");)

  ParseRes_* pr=__parseText(selfSR);
  
  if(!_t(pr))
  {
    _logError(begin,"ifOpAnd not ends");

    return pr;
  }
  
  if(pr->res_.length>0)
  {
    pr->varName_=__createVar(begin);
    pr->value_=pr->res_;
    pr->testCode_=__varTestCode(pr->varName_);
    pr->res_=__addValue(pr->varName_);
    pr->decVarsCode_=__declareVar(pr->varName_,"String");
  }
  else
  {
    pr->varName_=null;
    pr->res_="";
  }
  
  return pr;
}


Base::ParseRes_* Base::__parseRoot(Base::SeekRet_* selfSR)
{
  Op_* selfOp=(Op_*)selfSR->op_;
  Int begin=selfSR->pos_;

  DEBUG(_logDebug(begin,"__parseRoot");)
  ParseRes_* pr=_createParseResClass();
  ParseRes_* prTemp=null;
  SeekRet_* sr=null;//,* srTemp;
  Int i=begin;
  
  pr->res_="";
  //pr->res_+="function()\n{var _fpText=\"\";\n";
  
  do
  {
    sr=(SeekRet_*)_seekOpGroup(i,opGroupMap_["all"]);
    sr=(SeekRet_*)_seekMultiFirst(2,new SeekRet_(*sr),_seekDefaultOp(i,sr));
    
    if(!_t(sr))
      break;
    
    DEBUG(_logDebug(sr->pos_,String("__parseRoot:: op=") & sr->op_->selfName_ & " begins");)

    prTemp=(ParseRes_*)(this->*(static_cast<Op_*>(sr->op_)->_parse))(sr);
    if(!_t(prTemp))
      break;
      
    DEBUG(_logDebug(prTemp->endPos_,String("__parseRoot:: op=") & sr->op_->selfName_ & " ends");)

    // if support
    if(_t(prTemp->varName_))
    {
      pr->res_+=prTemp->decVarsCode_;
      pr->res_+=__condCompFinal(prTemp);
    }

    pr->res_+=prTemp->res_;
    i=prTemp->endPos_;
    
    _delete(prTemp);
    _delete(sr);
  }
  while(/* _t(sr) && _t(prTemp) &&*/ i<text_.length );

  _delete(sr);
  _delete(prTemp);

  //pr->res_+="return _fpText;\n}";
  
  pr->endPos_=i;
  
  return pr;
}
Void Base::_setup(ArgParser * argp)
{
  __addOp("blockComment","/%","%/",reinterpret_cast<ParseFunc_>(&Base::__parseBlockComment));
  ((Op_*)(opMap_["blockComment"]))->_parseToText=reinterpret_cast<ParseFunc_>(&Base::__parseBlockCommentToText);
  __addOp("lineComment","//%","\n",reinterpret_cast<ParseFunc_>(&Base::__parseLineComment));
  ((Op_*)(opMap_["lineComment"]))->_parseToText=reinterpret_cast<ParseFunc_>(&Base::__parseLineCommentToText);
  __addOp("ignoreOp","!%","%!",reinterpret_cast<ParseFunc_>(&Base::__parseIgnoreOp));
  ((Op_*)(opMap_["ignoreOp"]))->_parseToText=reinterpret_cast<ParseFunc_>(&Base::__parseIgnoreOpToText);

  __addOp("cond","[%","%]",reinterpret_cast<ParseFunc_>(&Base::__parseCond));
  __addOp("condOpAnd","&%","%&",reinterpret_cast<ParseFunc_>(&Base::__parseCondOpAnd));
  __addOp("code","?%","%?",reinterpret_cast<ParseFunc_>(&Base::__parseCode));
  __addOp("value","%","%",reinterpret_cast<ParseFunc_>(&Base::__parseValue));
  __addOp("default",null,null,reinterpret_cast<ParseFunc_>(&Base::__parseDefault));
  ((Op_*)(opMap_["default"]))->_parseToText=reinterpret_cast<ParseFunc_>(&Base::__parseDefaultToText);
  __addOp("root",null,null,reinterpret_cast<ParseFunc_>(&Base::__parseRoot));
  
  __addOp("textEnd",null,null,null);

  
  opGroupMap_["nonOp"]=new OpMap_();
  __addOpToOpGroup(opGroupMap_["nonOp"],opMap_["blockComment"]);
  __addOpToOpGroup(opGroupMap_["nonOp"],opMap_["lineComment"]);
  __addOpToOpGroup(opGroupMap_["nonOp"],opMap_["ignoreOp"]);
  
  Parser::_setup(argp);
}

} // namespace TouplParser



