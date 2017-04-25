﻿/*
* breeze License
* Copyright (C) 2015 - 2016 YaweiZhang <yawei.zhang@foxmail.com>.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/


#ifndef _ENTITY_H_
#define _ENTITY_H_
#include <common.h>
#include <utls.h>
#include <ProtoCommon.h>
#include <ProtoClient.h>
#include <ProtoSceneCommon.h>
#include <ProtoSceneServer.h>
#include <ProtoSceneClient.h>
#include <rvo2/RVO.h>

inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const RVO::Vector2 & v){stm << "[" << v.x() << "," << v.y() << "]";return stm;}
inline EPosition operator + (const EPosition & dst, const EPosition & org){return EPosition(dst.x + org.x, dst.y + org.y);}
inline EPosition operator * (const EPosition & dst, const EPosition & org){return EPosition(dst.x * org.x, dst.y * org.y);}
inline EPosition operator + (const EPosition & dst, double val){return EPosition(dst.x + val, dst.y + val);}
inline EPosition operator - (const EPosition & dst, double val){return EPosition(dst.x - val, dst.y - val);}
inline EPosition operator * (const EPosition & dst, double val){return EPosition(dst.x * val, dst.y * val);}
inline EPosition operator / (const EPosition & dst, double val){return EPosition(dst.x / val, dst.y * val);}
inline EPosition normalize(const EPosition & dst){if (std::abs(dst.x) > std::abs(dst.y)){return EPosition(dst.x / dst.x, dst.y / dst.x);}return EPosition(dst.x / dst.y, dst.y / dst.y);}
inline RVO::Vector2 toRVOVector2(const EPosition & pos){return RVO::Vector2(pos.x, pos.y);}
inline EPosition toEPoint(const RVO::Vector2 & pos){return EPosition(pos.x(), pos.y());}
inline double getDistance(const EPosition& pos1, const EPosition & pos2){return getDistance(pos1.x, pos1.y, pos2.x, pos2.y);}
inline DictProp operator + (const DictProp & ep1, const DictProp & ep2);
inline DictProp operator * (const DictProp & ep1, const DictProp & ep2);
inline DictProp operator * (const DictProp & ep, double df);



using DictID = unsigned long long;
const DictID InvalidDictID = -1;

struct EntitySkillInfo
{
    DictID dictID = InvalidDictID;
    double beginTime = 0.0; //技能开始释放时间
};



struct EntityControl //EntityControl  
{
    unsigned long long eid = InvalidEntityID;
    unsigned long long agentNo = RVO::RVO_ERROR; //agentNo.   
    double stateChageTime = 0.0;
    DictID activeSkillID = InvalidDictID; //激活的自动锁敌的技能ID
    std::map<DictID, EntitySkillInfo> skills;

    EPosition spawnpoint; //出生点
    double diedTime = 1E128; //实体死亡时间点 仅飞行道具类有效  
    ui64 hitTimes = -1; //实体碰撞, 仅飞行道具类有效  
    double blockMoveCount = 0; //移动被阻次数 
    EPosition lastClientPos; //最后一次客户端提交的坐标
};






class Entity
{
public:
    Entity();
    ~Entity();
    double getSpeed();
    double getSuckBlood();
    double getAttack();
    EntityFullData getFullData();
    DictProp _props;
    EntityState  _state;
    EntityMove  _move;
    EntityControl _control;
    EntityReport _report;
    SessionID _clientSessionID = InvalidSessionID;
    bool _isInfoDirty = false;
    bool _isMoveDirty = false;

};

using EntityPtr = std::shared_ptr<Entity>;
































inline DictProp operator + (const DictProp & ep1, const DictProp & ep2)
{
    DictProp ret;
    ret.hp = ep1.hp + ep2.hp;
    ret.attack = ep1.attack + ep2.attack;
    ret.moveSpeed = ep1.moveSpeed + ep2.moveSpeed;
    ret.attackSpeed = ep1.attackSpeed + ep2.attackSpeed;
    return ret;
}

inline DictProp operator * (const DictProp & ep1, const DictProp & ep2)
{
    DictProp ret;
    ret.hp = ep1.hp * ep2.hp;
    ret.attack = ep1.attack * ep2.attack;
    ret.moveSpeed = ep1.moveSpeed * ep2.moveSpeed;
    ret.attackSpeed = ep1.attackSpeed * ep2.attackSpeed;
    return ret;
}

inline DictProp operator * (const DictProp & ep, double df)
{
    DictProp ret;
    ret.hp = ep.hp * df;
    ret.attack = ep.attack * df;
    ret.moveSpeed = ep.moveSpeed * df;
    ret.attackSpeed = ep.attackSpeed * df;
    return ret;
}



#endif
