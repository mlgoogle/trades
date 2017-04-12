// Copyright (c) 2016 The tourism Authors. All rights reserved.
// user_mysql.h
// Created on: 2016年8月16日.
// Author: Paco.
#ifndef PLUGINS_USER_USER_MYSQL_H_
#define PLUGINS_USER_USER_MYSQL_H_

#include "config/config.h"
#include "basic/basictypes.h"

#include "storage/data_engine.h"

//#include "pub/net/typedef.h"

namespace user {
//用户充值状态
#define CREDIT_INPROCESS "1" //处理中
#define CREDIT_SUCCESS "2"
#define CREDIT_FAIL "3"
	
//用户充值数据库状态
#define DB_CREDIT_INPROCESS_STR "0,"
#define DB_CREDIT_CLIENT_SUCCESS_STR "1,"
#define DB_CREDIT_CLIENT_FAIL_STR "2,"
#define DB_CREDIT_SERVER_SUCCESS_STR "3,"
#define DB_CREDIT_SERVER_FAIL_STR "4,"
	
#define DB_CREDIT_INPROCESS 0
#define DB_CREDIT_CLIENT_SUCCESS 1
#define DB_CREDIT_CLIENT_FAIL 2
#define DB_CREDIT_SERVER_SUCCESS 3
#define DB_CREDIT_SERVER_FAIL 4
	
enum FlowType {
  DEPOSIT = 1, //入金
  WITHDRAW, //出金
  OPEN_POSITION, //建仓
  CLOSE_POSITION //平仓
};
 
class UserMysql {
 public:
  UserMysql(config::FileConfig* config);
  ~UserMysql();

 public:
  int32 UserInfoSelect(std::string uids, base_logic::DictionaryValue* dic);
  int32 AccountInfoSelect(int64 uid, base_logic::DictionaryValue* dic);
  int32 OrderListSelect(int64 uid, std::string flow_type, int32 start_pos,
										int32 count, base_logic::DictionaryValue* dic);
  int32 OrderDetailSelect(int64 uid, int64 flow_id, int32 flow_type,
										base_logic::DictionaryValue* dic);
  int32 BankcardListSelect(int64 uid, base_logic::DictionaryValue* dic);
  int32 BindBankcardInsertAndSelect(int64 uid, int32 bank_id, std::string branch_bank,
					std::string card_no, std::string bank_username, base_logic::DictionaryValue* dic);
  int32 UnbindBankcardDelete(std::string phone_num, int32 bank_id);
  int32 ChangeDefaultBankcard(int64 uid, int32 bank_id);
  int32 BankAccountInfoSelect(std::string account, base_logic::DictionaryValue* dic);
  int32 CreditListSelect(int64 uid, std::string status, int64 start_pos, int64 count, base_logic::DictionaryValue* dic);
  int32 CreditDetailSelect(int64 uid, int64 recharge_id, base_logic::DictionaryValue* dic);
  int32 UserWithdrawInsertAndSelect(int64 uid, double money,
						int64 bankcard_id, std::string passwd, base_logic::DictionaryValue* dic);
  int32 UserWithdrawListSelect(int64 uid, std::string status,
								int64 startPos, int64 count, base_logic::DictionaryValue* dic);
  //  int32 UserWithdrawDetailSelect(int64 uid, int64 withdraw_id, base_logic::DictionaryValue* dic);
  int32 RechargeInfoInsertAndSelect(int64 uid, double price, base_logic::DictionaryValue* dic);
  int32 ChangeRechargeStatusAndSelect(int64 rid, int64 result, base_logic::DictionaryValue* dic);

  int32 ChangeUserInfoUpdate(int64 uid, std::string nickname,
							 std::string headurl, int64 gender);
  int32 DeviceTokenUpdate(int64 uid, std::string dt);

  static void CallUserInfoSelect(void* param, base_logic::Value* value);
  static void CallAccountInfoSelect(void* param, base_logic::Value* value);
  static void CallOrderListSelect(void* param, base_logic::Value* value);
  static void CallOrderDetailSelect(void* param, base_logic::Value* value);
  // static void CallBankCardListSelect(void* param, base_logic::Value* value);
  static void CallBindBankcardInsertAndSelect(void* param, base_logic::Value* value);
  static void CallBankAccountInfoSelect(void* param, base_logic::Value* value);
  static void CallCreditListSelect(void* param, base_logic::Value* value);
  static void CallCreditDetailSelect(void* param, base_logic::Value* value);
  static void CallBankcardListSelect(void* param, base_logic::Value* value);
  static void CallUserWithdrawInsertAndSelect(void* param, base_logic::Value* value);
  static void CallUserWithdrawListSelect(void* param, base_logic::Value* value);
  static void CallRechargeInfoInsertAndSelect(void* param, base_logic::Value* value);
  static void CallChangeRechargeStatusAndSelect(void* param, base_logic::Value* value);
  
 private:
  base_logic::DataEngine* mysql_engine_;
};

}  // namespace user

#endif  // PLUGINS_USER_USER_MYSQL_H_
