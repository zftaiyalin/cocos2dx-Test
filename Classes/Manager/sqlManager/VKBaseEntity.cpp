//
//  VKBaseEntity.cpp
//  SqliteSample
//
//  Created by Kasajima Yasuo on 2013/01/26.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.
//

#include "VKBaseEntity.h"

using namespace cocos2d;

//bool VKBaseEntity::init(){
//    return true;
//}
//
//VKBaseEntity::VKBaseEntity()
//{
//}
//
//VKBaseEntity::~VKBaseEntity()
//{
//}
//
//
//
//
//
//void VKBaseEntity::setId(int idNum){
//    __String *string = __String::createWithFormat("%d",idNum);
//    this -> setObject(string, idKey);
//}
//
//int VKBaseEntity::getId(){
//    __String *string = (__String *)this -> objectForKey(idKey);
//    if (string) {
//        return string -> intValue();
//    }else{
//        return 0;
//    }
//    
//}
//
//const char* VKBaseEntity::toString(){
//    DictElement *element = NULL;
//    __String *string = __String::create("");
//    CCDICT_FOREACH(this, element){
//        __String *value = (__String *)element -> getObject();
//        string = __String::createWithFormat("%s %s = %s :",string->getCString(), element->getStrKey(), value->getCString());
//    }
//    return string->getCString();
//}
