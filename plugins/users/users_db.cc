//  Copyright (c) 2017-2018 The SWP Authors. All rights reserved.
//  Created on: 2017年2月12日 Author: kerry
#include <mysql.h>
#include "logic/logic_unit.h"
#include "users/users_db.h"
#include "basic/basic_util.h"

namespace users_logic {

UsersDB::UsersDB(config::FileConfig* config) {
  mysql_engine_ = base_logic::DataEngine::Create(MYSQL_TYPE);
  mysql_engine_->InitParam(config->mysql_db_list_);
}

UsersDB::~UsersDB() {
  if (mysql_engine_) {
    delete mysql_engine_;
    mysql_engine_ = NULL;
  }
}

bool UsersDB::CheckAccountExist(const std::string& phone) {
  bool r = false;
  base_logic::DictionaryValue* dict = new base_logic::DictionaryValue();
  base_logic::DictionaryValue *info_value = NULL;
  std::string sql;
  //call actuals.proc_CheckUserIsExist('18668163052')
  sql = "call proc_CheckUserIsExist('" + phone + "');";

  dict->SetString(L"sql", sql);
  r = mysql_engine_->ReadData(0, (base_logic::Value *) (dict),
                              CallCheckAccountExist);
  if (!r)
    return false;

  dict->GetDictionary(L"resultvalue", &info_value);
  int32 result = 0;
  r = info_value->GetInteger(L"result", &result);
  r = (r && result == 0) ? true : false; /*0表示不存在未注册*/
  if (dict) {
    delete dict;
    dict = NULL;
  }
  return r;
}

bool UsersDB::RegisterAccount(const std::string& phone_num,
                              const std::string& passwd, const int32 type,
                              int64& uid, int32& result, const std::string &agentid, 
			      const std::string &recommend, const std::string &device_id, 
			      const int64 member_id) {
  bool r = false;
  base_logic::DictionaryValue* dict = new base_logic::DictionaryValue();
  base_logic::DictionaryValue *info_value = NULL;
  std::string sql;
  int64 big_type = type;
  //call actuals.proc_RegisterAccount('18668169052','1234124123')
  sql = "call proc_RegisterAccountV20170519('" + phone_num + "','" + passwd + "',"
      + base::BasicUtil::StringUtil::Int64ToString(big_type)  + ","
      + base::BasicUtil::StringUtil::Int64ToString(member_id) 
      + ",'" + agentid + "','" + recommend + "','" + device_id 
      + "');";

  base_logic::ListValue *listvalue;
  dict->SetString(L"sql", sql);
  r = mysql_engine_->ReadData(0, (base_logic::Value *) (dict),
                              CallRegisterAccount);
  if (!r)
    return false;

  dict->GetDictionary(L"resultvalue", &info_value);

  r = info_value->GetBigInteger(L"uid", &uid);
  r = info_value->GetInteger(L"result", &result);
  r = (r && uid > 0) ? true : false;
  if (dict) {
    delete dict;
    dict = NULL;
  }
  return r;
}

bool UsersDB::WXBindAccount(const std::string& phone_num,
                              const std::string& passwd, const int32 type,
                              int64& uid, int32& result, const std::string &openid, 
			      const std::string &nick_name, const std::string &head_url,
			      const std::string &agent_id, const std::string &recommend,
			      const std::string &device_id, const int64 member_id) {
  bool r = false;
  base_logic::DictionaryValue* dict = new base_logic::DictionaryValue();
  base_logic::DictionaryValue *info_value = NULL;
  std::string sql;
  int64 big_type = type;
  //call actuals.proc_RegisterAccount('18668169052','1234124123')
  sql = "call proc_WXBindAccountV20170519('" + phone_num + "','" + passwd + "',"
      + base::BasicUtil::StringUtil::Int64ToString(big_type)  + ","
      + base::BasicUtil::StringUtil::Int64ToString(member_id)  + ",'"
      + head_url + "','" + nick_name + "','" + openid 
      + "','" + agent_id + "','" + recommend
      + "','" + device_id + "');";

  base_logic::ListValue *listvalue;
  dict->SetString(L"sql", sql);
  r = mysql_engine_->ReadData(0, (base_logic::Value *) (dict),
                              CallRegisterAccount);
  if (!r)
    return false;

  dict->GetDictionary(L"resultvalue", &info_value);

  r = info_value->GetBigInteger(L"uid", &uid);
  r = info_value->GetInteger(L"result", &result);
  r = (r && uid > 0) ? true : false;
  if (dict) {
    delete dict;
    dict = NULL;
  }
  return r;
}

bool UsersDB::GetUserInfo(const int64 uid, const std::string& ip,
                          swp_logic::UserInfo& userinfo) {

  bool r = false;
  base_logic::DictionaryValue* dict = new base_logic::DictionaryValue();
  base_logic::DictionaryValue *info_value = NULL;
  std::string sql;

  ////call actuals.proc_GetUserinfo(68,'127.0.0.1')
  sql = "call proc_GetUserinfo("
      + base::BasicUtil::StringUtil::Int64ToString(uid) + ",'" + ip + "')";

  base_logic::ListValue *listvalue;
  dict->SetString(L"sql", sql);
  r = mysql_engine_->ReadData(0, (base_logic::Value *) (dict),
                              CallLoginAccount);
  if (!r)
    return false;

  dict->GetDictionary(L"resultvalue", &info_value);

  userinfo.ValueSerialization(info_value);
  if (dict) {
    delete dict;
    dict = NULL;
  }
  return true;
}

bool UsersDB::LoginAccount(const std::string& phone_num,
                           const std::string& passwd, const std::string &device_id,
			   const std::string& ip, swp_logic::UserInfo& user) {
  bool r = false;
  base_logic::DictionaryValue* dict = new base_logic::DictionaryValue();
  base_logic::DictionaryValue *info_value = NULL;
  std::string sql;

  //call actuals.proc_LoginAccount('18668169052','4bcf73028a526f5ae6899759ab332c3d3b173855bef3b22b19224cd5233d39c0','127.0,0.1')
  sql = "call proc_LoginAccount('" + phone_num + "','" + passwd + "','"+ device_id + "','" + ip
      + "')";

  base_logic::ListValue *listvalue;
  dict->SetString(L"sql", sql);
  r = mysql_engine_->ReadData(0, (base_logic::Value *) (dict),
                              CallLoginAccount);
  if (!r)
    return false;

  dict->GetDictionary(L"resultvalue", &info_value);

  user.ValueSerialization(info_value);
  if (dict) {
    delete dict;
    dict = NULL;
  }
  return r;
}


bool UsersDB::LoginWiXin(const std::string& open_id,
                           const std::string &device_id,
			   const std::string& ip, swp_logic::UserInfo& user, std::string &passwd) {
  bool r = false;
  base_logic::DictionaryValue* dict = new base_logic::DictionaryValue();
  base_logic::DictionaryValue *info_value = NULL;
  std::string sql;

  //call actuals.proc_LoginAccount('18668169052','4bcf73028a526f5ae6899759ab332c3d3b173855bef3b22b19224cd5233d39c0','127.0,0.1')
  sql = "call proc_LoginWiXin('" + open_id + "','"+ device_id + "','" + ip
      + "')";

  dict->SetString(L"sql", sql);
  r = mysql_engine_->ReadData(0, (base_logic::Value *) (dict),
                              CallLoginAccount);
  if (!r)
    return false;

  dict->GetDictionary(L"resultvalue", &info_value);

  user.ValueSerialization(info_value);
  info_value->GetString(L"passwd", &passwd); 
  if (dict) {
    delete dict;
    dict = NULL;
  }
  return r;
}

bool UsersDB::ModifyPwd(const std::string &phone, const std::string &newpwd)
{

  bool r = false;
  base_logic::DictionaryValue* dict = new base_logic::DictionaryValue();
  base_logic::DictionaryValue *info_value = NULL;
  std::string sql;
try
{
  sql = "call proc_ModifyPwd('" + phone + "','" + newpwd + "');";
  //LOG_ERROR2("______________sql= %s, !!", sql.c_str());

  base_logic::ListValue *listvalue;
  dict->SetString(L"sql", sql);
  r = mysql_engine_->ReadData(0, (base_logic::Value *) (dict),
                              CallRegisterAccount);
  if (!r)
    return false;

  dict->GetDictionary(L"resultvalue", &info_value);
  int64 ruid = 0;
  int result = 0;
  r = info_value->GetBigInteger(L"uid", &ruid);
  r = info_value->GetInteger(L"result", &result);
  r = (r && ruid > 0) ? true : false;

  //LOG_ERROR2("______________result = %d, uid = %d!!!", result, ruid );
  //LOG_ERROR2("______________result = %d, uid = %d!!!", result, ruid );
  //r = info_value->GetReal(L"balance", &balance);
}
catch (...)
{
    LOG_ERROR("UsersDB::ModifyPwd Error!!!" );
    r = false;
}
  if (dict) {
    delete dict;
    dict = NULL;
  }
  return r;

}


bool UsersDB::GetVersion(const int32 type, users_logic::net_reply::TGetVersion &get_version)
{
  bool r = false;
  base_logic::DictionaryValue* dict = new base_logic::DictionaryValue();
  base_logic::DictionaryValue *info_value = NULL;
  std::string sql;
try
{
  sql = "call proc_GetVersion(" + base::BasicUtil::StringUtil::Int64ToString(type) +")";
  //sql = "SELECT APPNAME,VERSIONNAME,TYPE,SIZE,VERSIONCODE,UPDATEDESC,RELEASETIME,URL,ISFORCEUPDATE FROM version_info WHERE TYPE = "  
  //    + base::BasicUtil::StringUtil::Int64ToString(type);
  //LOG_ERROR2("______________sql= %s, !!", sql.c_str());

  base_logic::ListValue *listvalue;
  dict->SetString(L"sql", sql);
  r = mysql_engine_->ReadData(0, (base_logic::Value *) (dict),
                              CallGetVersion);
  if (!r)
    return false;

  dict->GetDictionary(L"resultvalue", &info_value);
  int64 tmp = 0;
  std::string temp = "";
  r = info_value->GetBigInteger(L"type", &tmp);
  get_version.set_type(tmp);
  r = info_value->GetBigInteger(L"isforceupdate", &tmp);
  get_version.set_is_forceupdate(tmp);
  r = info_value->GetBigInteger(L"size", &tmp);
  get_version.set_size(tmp);
  r = info_value->GetBigInteger(L"versioncode", &tmp);
  get_version.set_version_code(tmp);

  r = info_value->GetString(L"appname", &temp);
  get_version.set_app_name(temp);
  r = info_value->GetString(L"versionname", &temp);
  get_version.set_version_name(temp);
  r = info_value->GetString(L"updatedesc", &temp);
  get_version.set_update_desc(temp);
  r = info_value->GetString(L"releasetime", &temp);
  get_version.set_release_time(temp);
  r = info_value->GetString(L"url", &temp);
  get_version.set_url(temp);

  //r = info_value->GetReal(L"balance", &balance);
}
catch (...)
{
    LOG_ERROR("catch GetVersion Error!!!" );
    r = false;
}
  if (dict) {
    delete dict;
    dict = NULL;
  }
  return r;

}

bool UsersDB::AccountBalance(const int64 uid, double & balance) {
  bool r = false;
  base_logic::DictionaryValue* dict = new base_logic::DictionaryValue();
  base_logic::DictionaryValue *info_value = NULL;
  std::string sql;
try
{
//call actuals.proc_AccountBalance(68)
  sql = "call proc_AccountBalance("
      + base::BasicUtil::StringUtil::Int64ToString(uid) + ");";

  base_logic::ListValue *listvalue;
  dict->SetString(L"sql", sql);
  r = mysql_engine_->ReadData(0, (base_logic::Value *) (dict),
                              CallAccountBalance);
  if (!r)
    return false;

  dict->GetDictionary(L"resultvalue", &info_value);

  r = info_value->GetReal(L"balance", &balance);
}
catch (...)
{
    LOG_ERROR("UsersDB::AccountBalance Error!!!" );
    r = false;
}
  if (dict) {
    delete dict;
    dict = NULL;
  }
  return r;
}

void UsersDB::CallLoginAccount(void* param, base_logic::Value* value) {
  base_logic::DictionaryValue *dict = (base_logic::DictionaryValue *) (value);
  base_storage::DBStorageEngine *engine =
      (base_storage::DBStorageEngine *) (param);
  MYSQL_ROW rows;
  base_logic::DictionaryValue *info_value = new base_logic::DictionaryValue();
  int32 num = engine->RecordCount();
  if (num > 0) {
    while (rows = (*(MYSQL_ROW *) (engine->FetchRows())->proc)) {
      if (rows[0] != NULL)
        info_value->SetBigInteger(L"uid", atoll(rows[0]));
      if (rows[1] != NULL)
        info_value->SetString(L"member_id", rows[1]);
      if (rows[2] != NULL)
        info_value->SetReal(L"balance", atof(rows[2]));
      if (rows[3] != NULL)
        info_value->SetString(L"phone", rows[3]);
      if (rows[4] != NULL)
        info_value->SetInteger(L"type", atoi(rows[4]));
      if (rows[5] != NULL)
        info_value->SetString(L"nickname", rows[5]);
      if (rows[6] != NULL)
        info_value->SetString(L"head_url", rows[6]);
      if (rows[7] != NULL)
        info_value->SetString(L"passwd", rows[7]);
    }
  }
  dict->Set(L"resultvalue", (base_logic::Value *) (info_value));
}

void UsersDB::CallRegisterAccount(void* param, base_logic::Value* value) {
  base_logic::DictionaryValue *dict = (base_logic::DictionaryValue *) (value);
  base_storage::DBStorageEngine *engine =
      (base_storage::DBStorageEngine *) (param);
  MYSQL_ROW rows;
  base_logic::DictionaryValue *info_value = new base_logic::DictionaryValue();
  int32 num = engine->RecordCount();
  if (num > 0) {
    while (rows = (*(MYSQL_ROW *) (engine->FetchRows())->proc)) {
      if (rows[0] != NULL)
        info_value->SetInteger(L"result", atoi(rows[0]));
      if (rows[1] != NULL)
        info_value->SetBigInteger(L"uid", atoll(rows[1]));
    }
  }
  dict->Set(L"resultvalue", (base_logic::Value *) (info_value));
}


void UsersDB::CallGetVersion(void* param, base_logic::Value* value) {
  base_logic::DictionaryValue *dict = (base_logic::DictionaryValue *) (value);
  base_storage::DBStorageEngine *engine =
      (base_storage::DBStorageEngine *) (param);
  MYSQL_ROW rows;
  base_logic::DictionaryValue *info_value = new base_logic::DictionaryValue();
  int32 num = engine->RecordCount();
  if (num > 0) {
    while (rows = (*(MYSQL_ROW *) (engine->FetchRows())->proc)) {
      if (rows[0] != NULL)
        info_value->SetString(L"appname", (rows[0]));
      if (rows[1] != NULL)
        info_value->SetString(L"versionname", (rows[1]));
      if (rows[2] != NULL)
        info_value->SetInteger(L"type", atoi(rows[2]));
      if (rows[3] != NULL)
        info_value->SetBigInteger(L"size", atoll(rows[3]));
      if (rows[4] != NULL)
        info_value->SetBigInteger(L"versioncode", atoll(rows[4]));
      if (rows[5] != NULL)
        info_value->SetString(L"updatedesc", rows[5]);
      if (rows[6] != NULL)
        info_value->SetString(L"releasetime", rows[6]);
      if (rows[7] != NULL)
        info_value->SetString(L"url", rows[7]);
      if (rows[8] != NULL)
        info_value->SetInteger(L"isforceupdate", atoi(rows[8]));
    }
  }
  dict->Set(L"resultvalue", (base_logic::Value *) (info_value));
}

void UsersDB::CallAccountBalance(void* param, base_logic::Value* value) {
try
{
  base_logic::DictionaryValue *dict = (base_logic::DictionaryValue *) (value);
  base_storage::DBStorageEngine *engine =
      (base_storage::DBStorageEngine *) (param);
  MYSQL_ROW rows;
  base_logic::DictionaryValue *info_value = new base_logic::DictionaryValue();
  int32 num = engine->RecordCount();
  if (num > 0) {
    while (rows = (*(MYSQL_ROW *) (engine->FetchRows())->proc)) {
      if (rows[0] != NULL)
        info_value->SetReal(L"balance", atof(rows[0]));
    }
  }
  dict->Set(L"resultvalue", (base_logic::Value *) (info_value));
}
catch (...)
{
    LOG_ERROR("CallAccount Balance Error!!!" );
}
}

void UsersDB::CallCheckAccountExist(void* param, base_logic::Value* value) {
  base_logic::DictionaryValue *dict = (base_logic::DictionaryValue *) (value);
  base_storage::DBStorageEngine *engine =
      (base_storage::DBStorageEngine *) (param);
  MYSQL_ROW rows;
  base_logic::DictionaryValue *info_value = new base_logic::DictionaryValue();
  int32 num = engine->RecordCount();
  if (num > 0) {
    while (rows = (*(MYSQL_ROW *) (engine->FetchRows())->proc)) {
      if (rows[0] != NULL)
        info_value->SetInteger(L"result", atoi(rows[0]));
    }
  }
  dict->Set(L"resultvalue", (base_logic::Value *) (info_value));
}


}  // namespace history_logic

