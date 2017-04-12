// Copyright (c) 2016 The tourism Authors. All rights reserved.
// user_mysql.cc
// Created on: 2016年8月16日.
// Author: Paco.

#include "user/user_mysql.h"

#include <mysql/mysql.h>
#include <sstream>

#include "storage/data_engine.h"
#include "comm/comm_head.h"

#include "logic/logic_comm.h"

namespace user {

UserMysql::UserMysql(config::FileConfig* config) {
  mysql_engine_ = base_logic::DataEngine::Create(MYSQL_TYPE);
  mysql_engine_->InitParam(config->mysql_db_list_);
}

UserMysql::~UserMysql() {
  if (mysql_engine_) {
    delete mysql_engine_;
  }
  mysql_engine_ = NULL;
}
  
int32 UserMysql::UserInfoSelect(std::string uids, base_logic::DictionaryValue* dic) {
  int32 err = 0;
  bool r = false;
  do {
    std::stringstream ss;
    ss << "call proc_UserInfoSelect('" << uids << "')";
    dic->SetString(L"sql", ss.str());
    LOG_DEBUG2("%s", ss.str().c_str());
    r = mysql_engine_->ReadData(0, (base_logic::Value *) (dic), CallUserInfoSelect);
    if (!r) {
      err = SQL_EXEC_ERR;
      break;
    }
    if (dic->empty()) {
      err = NO_USER;
      break;
    }
  } while (0);
  return err;
}

int32 UserMysql::AccountInfoSelect(int64 uid, base_logic::DictionaryValue* dic) {
  int32 err = 0;
  bool r = false;
  do {      
    std::stringstream ss;
    ss << "call proc_AccountInfoSelect(" << uid << ")";
    dic->SetString(L"sql", ss.str());
    LOG_DEBUG2("%s", ss.str().c_str());
    r = mysql_engine_->ReadData(0, (base_logic::Value *) (dic), CallAccountInfoSelect);
    if (!r) {
      err = SQL_EXEC_ERR;
      break;
    }
  } while (0);
  return err;
}

int32 UserMysql::OrderListSelect(int64 uid, std::string flow_type, int32 start_pos,
                    int32 count, base_logic::DictionaryValue* dic) {
  int32 err = 0;
  bool r = false;
  do {      
    std::stringstream ss;
    ss << "call proc_OrderListSelect(" << uid << ",'" << flow_type << "',"
            << start_pos << "," << count << ")";
    dic->SetString(L"sql", ss.str());
    LOG_DEBUG2("%s", ss.str().c_str());
    r = mysql_engine_->ReadData(0, (base_logic::Value *) (dic), CallOrderListSelect);
    if (!r) {
      err = SQL_EXEC_ERR;
      break;
    }
  } while (0);
  return err;
}

int32 UserMysql::OrderDetailSelect(int64 uid, int64 flow_id, int32 flow_type,
                    base_logic::DictionaryValue* dic) {
  int32 err = 0;
  bool r = false;
  do {      
    std::stringstream ss;
    ss << "call proc_OrderDetailSelect(" << uid << "," << flow_id << ","
                  << flow_type << ")";
    dic->SetString(L"sql", ss.str());
    LOG_DEBUG2("%s", ss.str().c_str());
    r = mysql_engine_->ReadData(0, (base_logic::Value *) (dic), CallOrderDetailSelect);
    if (!r) {
      err = SQL_EXEC_ERR;
      break;
    }
  } while (0);
  return err;
}
  
int32 UserMysql::BankcardListSelect(int64 uid, base_logic::DictionaryValue* dic) {
  int32 err = 0;
  bool r = false;
  do {      
    std::stringstream ss;
    ss << "call proc_BankcardListSelect(" << uid << ")";
    dic->SetString(L"sql", ss.str());
    LOG_DEBUG2("%s", ss.str().c_str());
    r = mysql_engine_->ReadData(0, (base_logic::Value *) (dic), CallBankcardListSelect);
    if (!r) {
      err = SQL_EXEC_ERR;
      break;
    }
  } while (0);
  return err;
}
  
int32 UserMysql::BindBankcardInsertAndSelect(int64 uid, int32 bank_id, std::string branch_bank,
                       std::string bankcard_num, std::string bank_username, base_logic::DictionaryValue* dic) {
  int32 err = 0;
  bool r = false;
  do {      
    std::stringstream ss;
    ss << "call proc_BindBankcardInsertAndSelect(" << uid << "," << bank_id << ",'" << branch_bank
     << "','" << bankcard_num << "','" << bank_username << "')";
    dic->SetString(L"sql", ss.str());
    LOG_DEBUG2("%s", ss.str().c_str());
    r = mysql_engine_->ReadData(0, (base_logic::Value *) (dic), CallBindBankcardInsertAndSelect);
    if (!r) {
      err = SQL_EXEC_ERR;
      break;
    }
  } while (0);
  return err;
}

int32 UserMysql::UnbindBankcardDelete(std::string phone_num, int32 bank_id) {
  int32 err = 0;
  bool r = false;
  do {      
    std::stringstream ss;
    ss << "call proc_UnbindBankcardDelete(" << phone_num << "," << bank_id << ")";
    base_logic::DictionaryValue dic;
    dic.SetString(L"sql", ss.str());
    LOG_DEBUG2("%s", ss.str().c_str());
    r = mysql_engine_->WriteData(0, (base_logic::Value *) (&dic));
    if (!r) {
      err = SQL_EXEC_ERR;
      break;
    }
  } while (0);
  return err;
}
  
int32 UserMysql::ChangeDefaultBankcard(int64 uid, int32 bank_id) {
  int32 err = 0;
  bool r = false;
  do {      
    std::stringstream ss;
    ss << "call proc_ChangeDefaultbankcardUpdate(" << uid << "," << bank_id << ")";
    base_logic::DictionaryValue* dic;
    dic->SetString(L"sql", ss.str());
    LOG_DEBUG2("%s", ss.str().c_str());
    r = mysql_engine_->WriteData(0, (base_logic::Value *) (&dic));
    if (!r) {
      err = SQL_EXEC_ERR;
      break;
    }
  } while (0);
  return err;
}
  
int32 UserMysql::BankAccountInfoSelect(std::string account, base_logic::DictionaryValue* dic) {
  int32 err = 0;
  bool r = false;
  do {
    std::stringstream ss;
    ss << "call proc_BankAccountInfoSelect('" << account << "')";
    dic->SetString(L"sql", ss.str());
    LOG_DEBUG2("%s", ss.str().c_str());
    r = mysql_engine_->ReadData(0, (base_logic::Value *) (dic), CallBankAccountInfoSelect);
    if (!r) {
      err = SQL_EXEC_ERR;
      break;
    }
  } while (0);
  return err;
}

int32 UserMysql::CreditListSelect(int64 uid, std::string status, int64 start_pos, int64 count, base_logic::DictionaryValue* dic) {
  int32 err = 0;
  bool r = false;
  do {      
    std::stringstream ss;
    ss << "call proc_CreditListSelect(" << uid << ",'" << status
     << "'," << start_pos << "," << count << ")";
    dic->SetString(L"sql", ss.str());
    LOG_DEBUG2("%s", ss.str().c_str());
    r = mysql_engine_->ReadData(0, (base_logic::Value *) (dic), CallCreditListSelect);
    if (!r) {
      err = SQL_EXEC_ERR;
      break;
    }
  } while (0);
  return err;
}
  
int32 UserMysql::CreditDetailSelect(int64 uid, int64 recharge_id, base_logic::DictionaryValue* dic) {
  int32 err = 0;
  bool r = false;
  do {      
    std::stringstream ss;
    ss << "call proc_CreditDetailSelect(" << uid << "," << recharge_id << ")";
    dic->SetString(L"sql", ss.str());
    LOG_DEBUG2("%s", ss.str().c_str());
    r = mysql_engine_->ReadData(0, (base_logic::Value *) (dic), CallCreditDetailSelect);
    if (!r) {
      err = SQL_EXEC_ERR;
      break;
    }
  } while (0);
  return err;
}
  
int32 UserMysql::UserWithdrawInsertAndSelect(int64 uid, double money,
            int64 bankcard_id, std::string passwd, base_logic::DictionaryValue* dic) {
  int32 err = 0;
  bool r = false;
  do {
    std::stringstream ss;
    ss << "call proc_UserWithdrawInsertAndSelect(" << uid << "," << money
      << "," << bankcard_id << ",'" << passwd << "')";
    dic->SetString(L"sql", ss.str());
    LOG_DEBUG2("%s", ss.str().c_str());
    r = mysql_engine_->ReadData(0, (base_logic::Value *) (dic), CallUserWithdrawInsertAndSelect);
    if (!r) {
      err = SQL_EXEC_ERR;
      break;
    }
  } while (0);
  return err;
}

int32 UserMysql::UserWithdrawListSelect(int64 uid, std::string status,
                int64 startPos, int64 count, base_logic::DictionaryValue* dic) {
  int32 err = 0;
  bool r = false;
  do {
    if (startPos < 0 || count <= 0) {
      err = SQL_EXEC_ERR;
      break;
    }

    std::stringstream ss;
    ss << "call proc_UserWithdrawListSelect(" << uid << ",'" << status
        << "'," << startPos << "," << count << ")";
    dic->SetString(L"sql", ss.str());
    LOG_DEBUG2("%s", ss.str().c_str());
    r = mysql_engine_->ReadData(0, (base_logic::Value *) (dic), CallUserWithdrawListSelect);
    if (!r) {
      err = SQL_EXEC_ERR;
      break;
    }
  } while (0);
  return err;
}
  
  /*int32 UserMysql::UserWithdrawDetailSelect(int64 uid, int64 withdraw_id, base_logic::DictionaryValue* dic) {
  int32 err = 0;
  bool r = false;
  do {
    std::stringstream ss;
    ss << "call proc_UserWithdrawDetailSelect(" << uid << "," << withdraw_id << ")";
    dic->SetString(L"sql", ss.str());
    LOG_DEBUG2("%s", ss.str().c_str());
    r = mysql_engine_->ReadData(0, (base_logic::Value *) (dic), CallUserWithdrawDetailSelect);
    if (!r) {
      err = SQL_EXEC_ERR;
      break;
    }
  } while (0);
  return err;
  }*/
  
int32 UserMysql::ChangeUserInfoUpdate(int64 uid, std::string nickname,
                    std::string headurl, int64 gender) {
  int32 err = 0;
  bool r = false;
  do {
    std::stringstream ss;
    ss << "call proc_ChangeUserInfoUpdate(" << uid << ",'"
       << nickname << "','" << headurl << "'," << gender << ")";
    base_logic::DictionaryValue dic;
    dic.SetString(L"sql", ss.str());
    LOG_DEBUG2("%s", ss.str().c_str());
    r = mysql_engine_->WriteData(0, (base_logic::Value *) (&dic));
    if (!r) {
      err = SQL_EXEC_ERR;
      break;
    }
  } while (0);
  return err;
}

int32 UserMysql::RechargeInfoInsertAndSelect(int64 uid, double price,
                       base_logic::DictionaryValue* dic) {
  int32 err = 0;
  bool r = false;
  do {
    std::stringstream ss;
    ss << "call proc_RechargeInfoInsertAndSelect(" << uid << "," << price
       << ")";
    dic->SetString(L"sql", ss.str());
    LOG_DEBUG2("%s", ss.str().c_str());
    r = mysql_engine_->ReadData(0, (base_logic::Value *) (dic), CallRechargeInfoInsertAndSelect);
    if (!r || dic->empty()) {
      err = SQL_EXEC_ERR;
      break;
    }
  } while (0);
  return err;
}
  
int32 UserMysql::ChangeRechargeStatusAndSelect(int64 rid, int64 result,
                         base_logic::DictionaryValue* dic) {
  int32 err = 0;
  bool r = false;
  do {
    std::stringstream ss;
    ss << "call proc_ChangeRechargeStatusAndSelect(" << rid << "," << result
       << ")";
    dic->SetString(L"sql", ss.str());
    LOG_DEBUG2("%s", ss.str().c_str());
    r = mysql_engine_->ReadData(0, (base_logic::Value *) (dic),
              CallChangeRechargeStatusAndSelect);
    if (!r || dic->empty()) {
      err = SQL_EXEC_ERR;
      break;
    }
  } while (0);
  return err;
}
  
int32 UserMysql::DeviceTokenUpdate(int64 uid, std::string dt) {
  int32 err = 0;
  bool r = false;
  do {
    std::stringstream ss;
    ss << "call proc_DeviceTokenUpdate(" << uid << ",'" << dt << "')";
    base_logic::DictionaryValue* dic;
    dic->SetString(L"sql", ss.str());
    LOG_DEBUG2("%s", ss.str().c_str());
    r = mysql_engine_->WriteData(0, (base_logic::Value *) (&dic));
    if (!r) {
      err = SQL_EXEC_ERR;
      break;
    }
  } while (0);
  return err;
}
  
void UserMysql::CallUserInfoSelect(void* param, base_logic::Value* value) {
  base_storage::DBStorageEngine* engine =
    (base_storage::DBStorageEngine*) (param);
  MYSQL_ROW rows;
  int32 num = engine->RecordCount();
  base_logic::DictionaryValue* info = reinterpret_cast<base_logic::DictionaryValue*>(value);
  if (num > 0) {
    base_logic::ListValue* list = new base_logic::ListValue();
    while (rows = (*(MYSQL_ROW*) (engine->FetchRows())->proc)) {
      base_logic::DictionaryValue* dict = new base_logic::DictionaryValue();
      if (rows[0] != NULL)
        dict->SetBigInteger(L"id", atoll(rows[0]));
      if (rows[1] != NULL)
        dict->SetString(L"phone", rows[1]);
      if (rows[2] != NULL)
        dict->SetString(L"screenName", rows[2]);
      if (rows[3] != NULL)
        dict->SetString(L"avatarLarge", rows[3]);
      if (rows[4] != NULL)
        dict->SetCharInteger(L"gender", atoi(rows[4]));
      list->Append(dict);
    }
    info->Set(L"userinfoList", list);
  } else {
    LOG_ERROR ("CallUserInfoSelect count < 0");
  }
    info->Remove(L"sql", &value);
}
  
void UserMysql::CallAccountInfoSelect(void* param, base_logic::Value* value) {
  base_storage::DBStorageEngine* engine =
      (base_storage::DBStorageEngine*) (param);
  MYSQL_ROW rows;
  int32 num = engine->RecordCount();
  base_logic::DictionaryValue* dict = reinterpret_cast<base_logic::DictionaryValue*>(value);
  if (num > 0) {
    while (rows = (*(MYSQL_ROW*) (engine->FetchRows())->proc)) {
    if (rows[0] != NULL) {
      dict->SetReal(L"balance", atof(rows[0]));
    }
  }
  } else {
    LOG_ERROR ("CallAccountInfoSelect count < 0");
  }
    dict->Remove(L"sql", &value);
}

void UserMysql::CallOrderListSelect(void* param, base_logic::Value* value) {
  base_storage::DBStorageEngine* engine =
      (base_storage::DBStorageEngine*) (param);
  MYSQL_ROW rows;
  int32 num = engine->RecordCount();
  base_logic::DictionaryValue* info = reinterpret_cast<base_logic::DictionaryValue*>(value);
  if (num > 0) {
    base_logic::ListValue* list = new base_logic::ListValue();
    while (rows = (*(MYSQL_ROW*) (engine->FetchRows())->proc)) {
      base_logic::DictionaryValue* dict = new base_logic::DictionaryValue();
      if (rows[0] != NULL)
    dict->SetBigInteger(L"flowId", atoll(rows[0]));
      if (rows[1] != NULL)
    dict->SetBigInteger(L"flowType", atoll(rows[1]));
      if (rows[2] != NULL)
        dict->SetString(L"flowName", rows[2]);
      if (rows[3] != NULL)
    dict->SetBigInteger("inOut", atoll(rows[3]));
      if (rows[4] != NULL)
    dict->SetReal("amount", atoll(rows[4]));
      if (rows[5] != NULL)
    dict->SetReal("balance", atoll(rows[5]));
      if (rows[6] != NULL)
    dict->SetReal("flowTime", atoll(rows[6]));
      if (rows[7] != NULL)
    dict->SetString("comment", rows[7]);
    list->Append(dict); 
    }
    info->Set("orders", list);
  } else {
    LOG_ERROR ("CallOrderListSelect count < 0");
  }
    info->Remove(L"sql", &value);
}

void UserMysql::CallOrderDetailSelect(void* param, base_logic::Value* value) {
  base_storage::DBStorageEngine* engine =
      (base_storage::DBStorageEngine*) (param);
  MYSQL_ROW rows;
  int32 num = engine->RecordCount();
  base_logic::DictionaryValue* dict = reinterpret_cast<base_logic::DictionaryValue*>(value);
  if (num > 0) {
  base_logic::DictionaryValue* basic = new base_logic::DictionaryValue();
  int32 flow_type;
  while (rows = (*(MYSQL_ROW*) (engine->FetchRows())->proc)) {
    if (rows[0] != NULL)
    basic->SetBigInteger(L"id", atoll(rows[0]));
    if (rows[1] != NULL)
    basic->SetBigInteger(L"flowId", atoll(rows[1]));
    if (rows[2] != NULL) {
    flow_type = atoll(rows[2]);
    basic->SetInteger(L"flowType", flow_type);
    }
    if (rows[3] != NULL)
    basic->SetString(L"flowName", rows[3]);
      if (rows[4] != NULL)
    dict->SetBigInteger("inOut", atoll(rows[4]));
      if (rows[5] != NULL)
    dict->SetReal("amount", atoll(rows[5]));
      if (rows[6] != NULL)
    dict->SetReal("balance", atoll(rows[6]));
      if (rows[7] != NULL)
    dict->SetReal("flowTime", atoll(rows[7]));
      if (rows[8] != NULL)
    dict->SetString("comment", rows[8]);
    
    switch (flow_type) {
    case DEPOSIT:
        if (rows[9] != NULL)
      dict->SetString("depositType", rows[9]);
        if (rows[10] != NULL)
      dict->SetString("depositName", rows[10]);
    break;
    case WITHDRAW:
        if (rows[9] != NULL)
      dict->SetString("bank", rows[9]);
        if (rows[10] != NULL)
      dict->SetString("bank", rows[10]);
        if (rows[11] != NULL)
      dict->SetString("name", rows[11]);
        if (rows[12] != NULL)
      dict->SetCharInteger("status", atoi(rows[12]));
        if (rows[13] != NULL)
      dict->SetReal("withdrawAmount", atof(rows[13]));
        if (rows[14] != NULL)
      dict->SetReal("withdrawCharge", atof(rows[14]));
    break;
    case OPEN_POSITION:
    case CLOSE_POSITION: 
        if (rows[9] != NULL)
      dict->SetString("goodsName", rows[9]);
        if (rows[10] != NULL)
      dict->SetCharInteger("buySell", atoi(rows[10]));
        if (rows[11] != NULL)
      dict->SetInteger("positionAmount", atoi(rows[11]));
        if (rows[12] != NULL)
      dict->SetReal("openPrice", atof(rows[12]));
        if (rows[13] != NULL)
      dict->SetBigInteger("positionTime", atoll(rows[13]));
        if (rows[14] != NULL)
      dict->SetReal("openCost", atof(rows[14]));
        if (rows[15] != NULL)
      dict->SetReal("openCharge", atof(rows[15]));
        if (rows[16] != NULL)
      dict->SetReal("closePrice", atof(rows[16]));
        if (rows[17] != NULL)
      dict->SetBigInteger("closeTime", atoll(rows[17]));
        if (rows[18] != NULL)
      dict->SetReal("closeIncome", atof(rows[18]));
        if (rows[19] != NULL)
      dict->SetReal("closeCharge", atof(rows[19]));
        if (rows[20] != NULL)
      dict->SetCharInteger("closeType", atoi(rows[20]));
        if (rows[21] != NULL)
      dict->SetString("closeName", rows[21]);
        break;
    }
  }
  } else {
    LOG_ERROR ("CallOrderDetailSelect count < 0");
  }
  dict->Remove(L"sql", &value);
}

void UserMysql::CallBankcardListSelect(void* param, base_logic::Value* value) {
  base_storage::DBStorageEngine* engine =
      (base_storage::DBStorageEngine*) (param);
  MYSQL_ROW rows;
  int32 num = engine->RecordCount();
  base_logic::DictionaryValue* info = reinterpret_cast<base_logic::DictionaryValue*>(value);
  if (num > 0) {
    base_logic::ListValue* list = new base_logic::ListValue();
    while (rows = (*(MYSQL_ROW*) (engine->FetchRows())->proc)) {
      base_logic::DictionaryValue* dict = new base_logic::DictionaryValue();
      if (rows[0] != NULL)
    dict->SetBigInteger(L"bid", atoll(rows[0]));
      if (rows[1] != NULL)
    dict->SetBigInteger(L"id", atoll(rows[1]));
      if (rows[2] != NULL)
        dict->SetString(L"bank", rows[2]);
      if (rows[3] != NULL)
    dict->SetString("branchBank", rows[3]);
      if (rows[4] != NULL)
    dict->SetString("cardNo", rows[4]);
      if (rows[5] != NULL)
    dict->SetString("name", rows[5]);
    list->Append(dict); 
    }
  info->Set("cardlist", list);
  } else {
    LOG_ERROR ("CallBankcardListSelect count < 0");
  }
  info->Remove(L"sql", &value);
}

void UserMysql::CallBindBankcardInsertAndSelect(void* param, base_logic::Value* value) {
  base_storage::DBStorageEngine* engine =
      (base_storage::DBStorageEngine*) (param);
  MYSQL_ROW rows;
  int32 num = engine->RecordCount();
  base_logic::DictionaryValue* dict = reinterpret_cast<base_logic::DictionaryValue*>(value);
  if (num > 0) {
    while (rows = (*(MYSQL_ROW*) (engine->FetchRows())->proc)) {
      if (rows[0] != NULL)
    dict->SetBigInteger(L"bid", atoll(rows[0]));
      if (rows[1] != NULL)
    dict->SetBigInteger(L"id", atoll(rows[1]));
      if (rows[2] != NULL)
        dict->SetString(L"bank", rows[2]);
      if (rows[3] != NULL)
    dict->SetString("branchBank", rows[3]);
      if (rows[4] != NULL)
    dict->SetString("cardNo", rows[4]);
      if (rows[5] != NULL)
    dict->SetString("name", rows[5]);
    }
  } else {
    LOG_ERROR ("CallBindBankcardInsertAndSelect count < 0");
  }
    dict->Remove(L"sql", &value);
}
  
void UserMysql::CallBankAccountInfoSelect(void* param, base_logic::Value* value) {
  base_storage::DBStorageEngine* engine =
    (base_storage::DBStorageEngine*) (param);
  MYSQL_ROW rows;
  int32 num = engine->RecordCount();
  base_logic::DictionaryValue* dict = reinterpret_cast<base_logic::DictionaryValue*>(value);
  if (num > 0) {
    while (rows = (*(MYSQL_ROW*) (engine->FetchRows())->proc)) {
    int result = atoi(rows[0]);
      if (rows[0] != NULL)
        dict->SetInteger(L"result", result);
    if (result == 0) {
        if (rows[1] != NULL)
          dict->SetBigInteger(L"bankId", atoll(rows[1]));
        if (rows[2] != NULL)
          dict->SetString(L"bankName", rows[2]);
    }
    }
  } else {
    LOG_ERROR ("CallBankAccountInfoSelect count < 0");
  }
    dict->Remove(L"sql", &value);
}
  
void UserMysql::CallCreditListSelect(void* param, base_logic::Value* value) {
  base_storage::DBStorageEngine* engine =
      (base_storage::DBStorageEngine*) (param);
  MYSQL_ROW rows;
  int32 num = engine->RecordCount();
  base_logic::DictionaryValue* info = reinterpret_cast<base_logic::DictionaryValue*>(value);
  if (num > 0) {
    base_logic::ListValue* list = new base_logic::ListValue();
    while (rows = (*(MYSQL_ROW*) (engine->FetchRows())->proc)) {
      base_logic::DictionaryValue* dict = new base_logic::DictionaryValue();
      if (rows[0] != NULL)
    dict->SetBigInteger(L"rid", atoll(rows[0]));
      if (rows[1] != NULL)
    dict->SetBigInteger(L"id", atoll(rows[1]));
      if (rows[2] != NULL)
    dict->SetReal(L"amount", atof(rows[2]));
      if (rows[3] != NULL)
    dict->SetString("depositTime", rows[3]);
      if (rows[4] != NULL)
    dict->SetCharInteger("depositType", atoi(rows[4]));
      //if (rows[5] != NULL)
    //dict->SetString("depositName", rows[5]);
      if (rows[5] != NULL) {
    int32 status = atoi(rows[5]);
        const char* ret_status;
    switch (status) {
      case DB_CREDIT_INPROCESS:
      case DB_CREDIT_CLIENT_SUCCESS:
      ret_status = CREDIT_INPROCESS;
      break;
      case DB_CREDIT_CLIENT_FAIL:
      case DB_CREDIT_SERVER_FAIL:
      ret_status = CREDIT_FAIL;
      break;
      case DB_CREDIT_SERVER_SUCCESS:
      ret_status = CREDIT_SUCCESS;
      break;
      }
    dict->SetCharInteger("status", atoi(rows[5]));
      }
    list->Append(dict); 
    }
    info->Set("depositsinfo", list);
  } else {
    LOG_ERROR ("CallCreditListSelect count < 0");
  }
    info->Remove(L"sql", &value);
}

void UserMysql::CallCreditDetailSelect(void* param, base_logic::Value* value) {
  base_storage::DBStorageEngine* engine =
      (base_storage::DBStorageEngine*) (param);
  MYSQL_ROW rows;
  int32 num = engine->RecordCount();
  base_logic::DictionaryValue* dict = reinterpret_cast<base_logic::DictionaryValue*>(value);
  if (num > 0) {
  base_logic::DictionaryValue* basic = new base_logic::DictionaryValue();
  int32 flow_type;
    while (rows = (*(MYSQL_ROW*) (engine->FetchRows())->proc)) {
    if (rows[0] != NULL)
    basic->SetBigInteger(L"rid", atoll(rows[0]));
    if (rows[1] != NULL)
    basic->SetBigInteger(L"id", atoll(rows[1]));
    if (rows[2] != NULL)
    basic->SetReal(L"amount", atoll(rows[2]));
    if (rows[3] != NULL)
    basic->SetBigInteger(L"depositTime", atoll(rows[3]));
      if (rows[4] != NULL)
    dict->SetCharInteger(L"depositType", atoi(rows[4]));
      if (rows[5] != NULL)
    dict->SetString(L"depositName", rows[5]);
      if (rows[6] != NULL)
    dict->SetCharInteger(L"status", atoi(rows[6]));
  }
  } else {
    LOG_ERROR ("CallCreditDetailSelect count < 0");
  }
    dict->Remove(L"sql", &value);
}

void UserMysql::CallUserWithdrawInsertAndSelect(void* param, base_logic::Value* value) {
  base_storage::DBStorageEngine* engine =
      (base_storage::DBStorageEngine*) (param);
  MYSQL_ROW rows;
  int32 num = engine->RecordCount();
  base_logic::DictionaryValue* dict = reinterpret_cast<base_logic::DictionaryValue*>(value);
  if (num > 0) {
    while (rows = (*(MYSQL_ROW*) (engine->FetchRows())->proc)) {
    int result; 
    if (rows[0] != NULL)
      result = atoi(rows[0]);
    if (result == 0) {
      if (rows[1] != NULL)
        dict->SetBigInteger(L"wid", atoll(rows[1]));
      if (rows[2] != NULL)
        dict->SetBigInteger(L"id", atoll(rows[2]));
      if (rows[3] != NULL)
        dict->SetReal(L"amount", atof(rows[3]));
      if (rows[4] != NULL)
        dict->SetReal(L"charge", atof(rows[4]));
      if (rows[5] != NULL)
        dict->SetString(L"withdrawTime", rows[5]);
      if (rows[6] != NULL)
        dict->SetString(L"handleTime", rows[6]);
      if (rows[7] != NULL)
        dict->SetString(L"bank", rows[7]);
      if (rows[8] != NULL)
        dict->SetString(L"branchBank", rows[8]);
      if (rows[9] != NULL)
        dict->SetString(L"cardNo", rows[9]);
      if (rows[10] != NULL)
        dict->SetString(L"name", rows[10]);
      if (rows[11] != NULL)
        dict->SetString(L"comment", rows[11]);
      if (rows[12] != NULL) {
      dict->SetCharInteger(L"status", atoi(rows[12]));
      }
    } else
      dict->SetCharInteger(L"status", result);
    }
  } else {
    LOG_ERROR ("CallUserWithdrawInsertAndSelect count < 0");
  }
    dict->Remove(L"sql", &value);
}

void UserMysql::CallUserWithdrawListSelect(void* param, base_logic::Value* value) {
  base_storage::DBStorageEngine* engine =
      (base_storage::DBStorageEngine*) (param);
  MYSQL_ROW rows;
  int32 num = engine->RecordCount();
  base_logic::DictionaryValue* info = reinterpret_cast<base_logic::DictionaryValue*>(value);
  if (num > 0) {
    base_logic::ListValue* list = new base_logic::ListValue();
    while (rows = (*(MYSQL_ROW*) (engine->FetchRows())->proc)) {
      base_logic::DictionaryValue* dict = new base_logic::DictionaryValue();
    if (rows[0] != NULL)
      dict->SetBigInteger(L"wid", atoll(rows[0]));
    if (rows[1] != NULL)
      dict->SetBigInteger(L"id", atoll(rows[1]));
    if (rows[2] != NULL)
      dict->SetReal(L"amount", atof(rows[2]));
    if (rows[3] != NULL)
      dict->SetReal(L"charge", atof(rows[3]));
    if (rows[4] != NULL)
      dict->SetString(L"withdrawTime", rows[4]);
    if (rows[5] != NULL)
      dict->SetString(L"handleTime", rows[5]);
    if (rows[6] != NULL)
      dict->SetString(L"bank", rows[6]);
    if (rows[7] != NULL)
      dict->SetString(L"branchBank", rows[7]);
    if (rows[8] != NULL)
      dict->SetString(L"cardNo", rows[8]);
    if (rows[9] != NULL)
      dict->SetString(L"name", rows[9]);
    if (rows[10] != NULL)
      dict->SetString(L"comment", rows[10]);
    if (rows[11] != NULL)
      dict->SetCharInteger(L"status", atoi(rows[11]));
      list->Append(dict); 
    }
    info->Set("withdrawList", list);
  } else {
    LOG_ERROR ("CallUserWithdrawListSelect count < 0");
  }
    info->Remove(L"sql", &value);
}

  /*void UserMysql::CallCreditDetailSelect(void* param, base_logic::Value* value) {
  base_storage::DBStorageEngine* engine =
      (base_storage::DBStorageEngine*) (param);
  MYSQL_ROW rows;
  int32 num = engine->RecordCount();
  base_logic::DictionaryValue* dict = reinterpret_cast<base_logic::DictionaryValue*>(value);
  if (num > 0) {
  base_logic::DictionaryValue* basic = new base_logic::DictionaryValue();
  int32 flow_type;
    while (rows = (*(MYSQL_ROW*) (engine->FetchRows())->proc)) {
    if (rows[0] != NULL)
    badic->SetBigInteger(L"rid", atoll(rows[0]));
    if (rows[1] != NULL)
    basic->SetBigInteger(L"id", atoll(rows[1]));
    if (rows[2] != NULL)
    basic->SetReal(L"amount", atoll(rows[2]));
    if (rows[3] != NULL)
    basic->SetBigInteger(L"depositTime", atoll(rows[3]));
      if (rows[4] != NULL)
    dict->SetCharInteger(L"depositType", atoi(rows[4]));
      if (rows[5] != NULL)
    dict->SetString(L"depositName", rows[5]);
      if (rows[6] != NULL)
    dict->SetCharInteger(L"status", atoi(rows[6]));
  }
  } else {
    LOG_ERROR ("CallCreditDetailSelect count < 0");
  }
  }*/
  
void UserMysql::CallRechargeInfoInsertAndSelect(void* param, base_logic::Value* value) {
  base_storage::DBStorageEngine* engine =
    (base_storage::DBStorageEngine*) (param);
  MYSQL_ROW rows;
  int32 num = engine->RecordCount();
  base_logic::DictionaryValue* dict = reinterpret_cast<base_logic::DictionaryValue*>(value);
  if (num > 0) {
    while (rows = (*(MYSQL_ROW*) (engine->FetchRows())->proc)) {
      if (rows[0] != NULL) {
        //dict->SetBigInteger(L"rid", atoll(rows[0]));
        dict->SetString(L"rid",rows[0]);
      }
    }
  } else {
    LOG_ERROR ("CallRechargeInfoInsertAndSelect count < 0");
  }
    dict->Remove(L"sql", &value);
}

void UserMysql::CallChangeRechargeStatusAndSelect(void* param, base_logic::Value* value) {
  base_storage::DBStorageEngine* engine =
    (base_storage::DBStorageEngine*) (param);
  MYSQL_ROW rows;
  int32 num = engine->RecordCount();
  base_logic::DictionaryValue* dict = reinterpret_cast<base_logic::DictionaryValue*>(value);
  if (num > 0) {
    while (rows = (*(MYSQL_ROW*) (engine->FetchRows())->proc)) {
      if (rows[0] != NULL) {
        dict->SetBigInteger(L"returnCode", atoll(rows[0]));
      }
      if (rows[1] != NULL) {
        dict->SetReal(L"balance", atof(rows[1]));
      }
      if (rows[2] != NULL) {
        dict->SetBigInteger(L"id", atoll(rows[2]));
      }
    }
  } else {
    LOG_ERROR ("CallChangeRechargeStatusAndSelect count < 0");
  }
    dict->Remove(L"sql", &value);
}

} // namespace user

