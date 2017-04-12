// Copyright (c) 2016 The tourism Authors. All rights reserved.
// user_proto.h
// Created on: 2016年8月12日.
// Author: Paco.
#ifndef PLUGINS_USER_USER_PROTO_H_
#define PLUGINS_USER_USER_PROTO_H_

#include "net/proto_buf.h"
//#include "glog/logging.h"
namespace user {

namespace net_request {
  
class Heartbeat {
 public:
  Heartbeat()
    : uid_(NULL) {
  }
  
  ~Heartbeat() {
    if (uid_) {
      delete uid_;
      uid_ = NULL;
    }
  }
  
  int32 set_http_packet(base_logic::DictionaryValue* value);
  
  void set_uid(const int64 uid) {
    uid_ = new base_logic::FundamentalValue(uid);
  }

  const int64 uid() {
    int64 uid = 0;
    if (uid_)
      uid_->GetAsBigInteger(&uid);
    return uid;
  }
  
 private:
  base_logic::FundamentalValue* uid_;
};

class UserInfo {
 public:
  UserInfo()
    : uid_str_(NULL) {
  }

  ~UserInfo() {
    if (uid_str_) {
      delete uid_str_;
      uid_str_ = NULL;
    }
  }
  
  int32 set_http_packet(base_logic::DictionaryValue* value);
  
  void set_uid_str(const std::string& uid_str) {
    uid_str_ = new base_logic::StringValue(uid_str);
  }

  const std::string uid_str() const {
    std::string uid_str;
    if (uid_str_)
      uid_str_->GetAsString(&uid_str);
    return uid_str;
  }
  
 private:
  base_logic::StringValue* uid_str_;
};
  
class AccountInfo {
 public:
  AccountInfo()
    : uid_(NULL) {
  }
  
  ~AccountInfo() {
    if (uid_) {
      delete uid_;
    }
  }
  
  int32 set_http_packet(base_logic::DictionaryValue* value);
  
  void set_uid(const int64 uid) {
    uid_ = new base_logic::FundamentalValue(uid);
  }

  const int64 uid() {
    int64 uid = 0;
    if (uid_)
      uid_->GetAsBigInteger(&uid);
  return uid;
  }
  
 private:
  base_logic::FundamentalValue* uid_;
};

class OrderList {
 public:
  OrderList()
    : uid_(NULL),
    flow_type_(NULL),
    start_pos_(NULL),
    count_(NULL) {
  }
  
  ~OrderList() {
    if (uid_) {
      delete uid_;
      uid_ = NULL;
    }
    if (flow_type_) {
      delete flow_type_;
      flow_type_ = NULL;
    }
    if (start_pos_) {
      delete count_;
      count_ = NULL;
    }
  }
  
  int32 set_http_packet(base_logic::DictionaryValue* value);
  
  void set_uid(int64 uid) {
    uid_ = new base_logic::FundamentalValue(uid);
  }
  
  void set_flow_type(std::string& flow_type) {
    flow_type_ = new base_logic::StringValue(flow_type);
  } 
  
  void set_start_pos(int32 start_pos) {
    start_pos_ = new base_logic::FundamentalValue(start_pos);
  }

  void set_count(int32 count) {
    count_ = new base_logic::FundamentalValue(count);
  }

  int64 uid() {
    int64 uid;
    if (uid_)
      uid_->GetAsBigInteger(&uid);
  return uid;
  }

  std::string flow_type() {
    std::string flow_type;
    if (flow_type_)
      flow_type_->GetAsString(&flow_type);
    return flow_type;
  }

  int32 start_pos() {
    int32 start_pos;
    if (start_pos_)
      start_pos_->GetAsInteger(&start_pos);
    return start_pos;
  }
  
  int32 count() {
    int32 count;
    if (count_)
      count_->GetAsInteger(&count);
    return count;
  }
  
 private:
  base_logic::FundamentalValue* uid_;
  base_logic::StringValue* flow_type_;
  base_logic::FundamentalValue* start_pos_;
  base_logic::FundamentalValue* count_;
};

class OrderDetail {
 public:
  OrderDetail()
    : uid_(NULL),
      flow_id_(NULL),
      flow_type_(NULL) {
  }
  
  ~OrderDetail() {
    if (uid_) {
      delete uid_;
      uid_ = NULL;
    }
    if (flow_id_) {
      delete flow_id_;
      flow_id_ = NULL;
    }
    if (flow_type_) {
      delete flow_type_;
      flow_type_ = NULL;
    }
  }

  int32 set_http_packet(base_logic::DictionaryValue* value);
  
  void set_uid(int64 uid) {
    uid_ = new base_logic::FundamentalValue(uid);
  } 
  
  void set_flow_id(int32 flow_id) {
    flow_id_ = new base_logic::FundamentalValue(flow_id);
  }
  
  void set_flow_type(int32 flow_type) {
    flow_type_ = new base_logic::FundamentalValue(flow_type);
  }
  
  int64 uid() {
    int64 uid;
    if (uid_)
      uid_->GetAsBigInteger(&uid);
    return uid;
  }
  int64 flow_id() {
    int64 flow_id;
    if (flow_id_)
      flow_id_->GetAsBigInteger(&flow_id);
    return flow_id;
  }
  int32 flow_type() {
    int32 flow_type;
    if (flow_type_)
      flow_type_->GetAsInteger(&flow_type);
    return flow_type;
  }
 private:
  base_logic::FundamentalValue* uid_;
  base_logic::FundamentalValue* flow_id_;
  base_logic::FundamentalValue* flow_type_;
};

class BankcardList {
 public:
  BankcardList()
    : uid_(NULL) {
  }
  
  ~BankcardList() {
    if (uid_) {
      delete uid_;
      uid_ = NULL;
    }
  }
  
  int32 set_http_packet(base_logic::DictionaryValue* value);

  void set_uid(int64 uid) {
    uid_ = new base_logic::FundamentalValue(uid);
  }
  
  int64 uid() {
    int64 uid;
    if (uid_)
      uid_->GetAsBigInteger(&uid);
    return uid;
  }

 private:
  base_logic::FundamentalValue* uid_;
};

class BindBankcard {
 public:
  BindBankcard()
    : uid_(NULL), 
      bank_id_(NULL),
      branch_bank_(NULL),
      bankcard_num_(NULL),
      bank_username_(NULL) {
  }

  ~BindBankcard() {
    if (uid_) {
      delete uid_;
      uid_ = NULL;
    }
    if (bank_id_) {
      delete bank_id_;
      bank_id_ = NULL;
    }
    if (branch_bank_) {
      delete branch_bank_;
      branch_bank_ = NULL;
    }
    if (bankcard_num_) {
      delete bankcard_num_;
      bankcard_num_ = NULL;
    }
    if (bank_username_) {
      delete bank_username_;
      bank_username_ = NULL;
    }
  }
  
  int32 set_http_packet(base_logic::DictionaryValue* value);
  
  void set_uid(int64 uid) {
    uid_ = new base_logic::FundamentalValue(uid);
  }
  
  void set_bank_id(int64 bank_id) {
    bank_id_ = new base_logic::FundamentalValue(bank_id);
  }
  
  void set_branch_bank(std::string& branch_bank) {
    branch_bank_ = new base_logic::StringValue(branch_bank);
  }
  
  void set_bankcard_num(std::string& bankcard_num) {
    bankcard_num_ = new base_logic::StringValue(bankcard_num);
  }
  
  void set_bank_username(std::string& bank_username) {
    bank_username_ = new base_logic::StringValue(bank_username);
  }
  
  int64 uid() {
    int64 uid;
    if (uid_)
      uid_->GetAsBigInteger(&uid);
    return uid;
  }
  
  int64 bank_id() {
    int64 bank_id = 0;
    if (bank_id_)
      bank_id_->GetAsBigInteger(&bank_id);
    return bank_id;
  }
  
  std::string branch_bank() {
    std::string branch_bank;
    if (branch_bank_)
      branch_bank_->GetAsString(&branch_bank);
    return branch_bank;
  }
  
  std::string bankcard_num() {
    std::string bankcard_num;
    if (bankcard_num_)
      bankcard_num_->GetAsString(&bankcard_num);
    return bankcard_num;
  }
  
  std::string bank_username() {
    std::string bank_username;
    if (bank_username_)
      bank_username_->GetAsString(&bank_username);
    return bank_username;
  }
  
 private:
  base_logic::FundamentalValue* uid_;
  base_logic::FundamentalValue* bank_id_;
  base_logic::StringValue* branch_bank_;
  base_logic::StringValue* bankcard_num_;
  base_logic::StringValue* bank_username_;
};

class UnbindBankcard {
 public:
  UnbindBankcard()
    : phone_num_(NULL),
      bankcard_id_(NULL)/*,
      verify_code_(NULL),
      timestamp_(NULL),
      verify_token_(NULL)*/ {
  }
  
  ~UnbindBankcard() {
    if (phone_num_) {
      delete phone_num_;
      phone_num_ = NULL;
    }
    if (bankcard_id_) {
      delete bankcard_id_;
      bankcard_id_ = NULL;
    }
    /*if (verify_code_) {
      delete verify_code_;
      verify_code_ = NULL;
      }*/
  }
  
  int32 set_http_packet(base_logic::DictionaryValue* value);
  
  void set_phone_num(std::string& phone_num) {
    phone_num_ = new base_logic::StringValue(phone_num);
  }
  
  void set_bankcard_id(int64 bankcard_id) {
    bankcard_id_ = new base_logic::FundamentalValue(bankcard_id);
  }
  
  /*void set_verify_code(std::string& verify_code) {
    verify_code_ = new base_logic::StringValue(verify_code);
  }
  
  void set_timestamp(int64 timestamp) {
    timestamp_ = new base_logic::FundamentalValue(timestamp);
  }
  
  void set_verify_token(std::string& verify_token) {
    verify_token_ = new base_logic::StringValue(verify_token);
    }*/
  
  std::string phone_num() {
    std::string phone_num;
    if (phone_num_)
      phone_num_->GetAsString(&phone_num);
    return phone_num;
  }
  
  int64 bankcard_id() {
    int64 bankcard_id;
    if (bankcard_id_)
      bankcard_id_->GetAsBigInteger(&bankcard_id);
    return bankcard_id;
  }
  
  /*std::string verify_code() {
    std::string verify_code;
    if (verify_code_)
      verify_code_->GetAsString(&verify_code);
    return verify_code;
  }
  
  int64 timestamp() {
    int64 timestamp;
    if (timestamp_)
      timestamp_->GetAsBigInteger(&timestamp);
    return timestamp;
  }
  
  std::string verify_token() {
    std::string verify_token;
    if (verify_token_)
      verify_token_->GetAsString(&verify_token);
    return verify_token;
    }*/
  
 private:
  base_logic::StringValue* phone_num_;
  base_logic::FundamentalValue* bankcard_id_;
  /*base_logic::StringValue* verify_code_;
  base_logic::FundamentalValue* timestamp_;
  base_logic::StringValue* verify_token_;*/
};

class ChangeDefaultBankcard {
 public:
  ChangeDefaultBankcard()
    : uid_(NULL),
      bankcard_id_(NULL) {
  }
  
  ~ChangeDefaultBankcard() {
    if (uid_) { 
      delete uid_;
      uid_ = NULL;
    }
    if (bankcard_id_) {
      delete bankcard_id_;
      bankcard_id_ = NULL;
    }
  }

  int32 set_http_packet(base_logic::DictionaryValue* value);
  
  void set_uid(int64 uid) {
    uid_ = new base_logic::FundamentalValue(uid);
  }

  void set_bankcard_id(int64 bankcard_id) {
    bankcard_id_ = new base_logic::FundamentalValue(bankcard_id);
  }
  
  int64 uid() {
    int64 uid;
    if (uid_)
      uid_->GetAsBigInteger(&uid);
    return uid;
  }
  
  int64 bankcard_id() {
    int64 bankcard_id;
    if (bankcard_id_)
      bankcard_id_->GetAsBigInteger(&bankcard_id);
    return bankcard_id;
  }
  
 private:
  base_logic::FundamentalValue* uid_;
  base_logic::FundamentalValue* bankcard_id_;
};
  
class BankAccountInfo {
 public:
  BankAccountInfo()
    : bankcard_num_(NULL) {
  }
  
  ~BankAccountInfo() {
    if (bankcard_num_) {
      delete bankcard_num_;
      bankcard_num_ = NULL;
    }
  }

  int32 set_http_packet(base_logic::DictionaryValue* value);
  
  void set_bankcard_num(std::string bankcard_num) {
    bankcard_num_ = new base_logic::StringValue(bankcard_num);
  }
  
  std::string bankcard_num() {
    std::string bankcard_num;
    if (bankcard_num_)
      bankcard_num_->GetAsString(&bankcard_num);
    return bankcard_num;
  }
  
 private:
  base_logic::StringValue* bankcard_num_;
};

class CreditList {
 public:
  CreditList()
    : uid_(NULL),
      status_(NULL),
      start_pos_(NULL),
      count_(NULL) {
  }
  
  ~CreditList() {
    if (uid_) {
      delete uid_;
      uid_ = NULL;
    }
    if (status_) {
      delete status_;
      status_ = NULL;
    }
    if (start_pos_) {
      delete start_pos_;
      start_pos_ = NULL;
    }
    if (count_) {
      delete count_;
      count_ = NULL;
    }
  }
  
  int32 set_http_packet(base_logic::DictionaryValue* value);
  
  void set_uid(int64 uid) {
    uid_ = new base_logic::FundamentalValue(uid);
  }

  void set_status(std::string& status) {
    status_ = new base_logic::StringValue(status);
  }

  void set_start_pos(int64 start_pos) {
    start_pos_ = new base_logic::FundamentalValue(start_pos);
  }

  void set_count(int64 count) {
    count_ = new base_logic::FundamentalValue(count);
  }

  int64 uid() {
    int64 uid;
    if (uid_)
      uid_->GetAsBigInteger(&uid);
    return uid;
  }

  std::string status() {
    std::string status;
    if (status_)
      status_->GetAsString(&status);
    return status;
  }

  int64 start_pos() {
    int64 start_pos;
    if (start_pos_)
      start_pos_->GetAsBigInteger(&start_pos);
    return start_pos;
  }
  
  int64 count() {
    int64 count;
    if (count_)
      count_->GetAsBigInteger(&count);
    return count;
  }
  
 private:
  base_logic::FundamentalValue* uid_;
  base_logic::StringValue* status_;
  base_logic::FundamentalValue* start_pos_;
  base_logic::FundamentalValue* count_;
};

/*class CreditDetail {
 public:
  CreditDetail()
    : uid_(NULL),
     recharge_id_(NULL) {
  }
  
  ~C

  int64 uid() { return uid_; }
  int64 recharge_id() { return recharge_id_; }
  
 private:
  int64 uid_;
  int64 recharge_id_;
  };*/

class UserWithdraw {
 public:
  UserWithdraw()
    : uid_(NULL),
      money_(NULL),
      bankcard_id_(NULL),
      passwd_(NULL) {
  }
  
  ~UserWithdraw() {
    if (uid_) {
      delete uid_;
      uid_ = NULL;
    }
    if (money_) {
      delete money_;
      money_ = NULL;
    }
    if (bankcard_id_) {
      delete bankcard_id_;
      bankcard_id_ = NULL;
    }
    if (passwd_) {
      delete passwd_;
      passwd_ = NULL;
    }
  }
  
  int32 set_http_packet(base_logic::DictionaryValue* value);

  void set_uid(int64 uid) {
    uid_ = new base_logic::FundamentalValue(uid);
  }

  void set_money(double money) {
    money_ = new base_logic::FundamentalValue(money);
  }

  void set_bankcard_id(int64 bankcard_id) {
    bankcard_id_ = new base_logic::FundamentalValue(bankcard_id);
  }

  void set_passwd(std::string& passwd) {
    passwd_ = new base_logic::StringValue(passwd);
  }
  
  int64 uid() {
    int64 uid;
    if (uid_)
      uid_->GetAsBigInteger(&uid);
    return uid;
  }
  
  double money() {
    double money;
    if (money_)
      money_->GetAsReal(&money);
    return money;
  }
  
  int64 bankcard_id() {
    int64 bankcard_id;
    if (bankcard_id_)
      bankcard_id_->GetAsBigInteger(&bankcard_id);
    return bankcard_id;
  }
  
  std::string passwd() {
    std::string passwd;
    if (passwd_)
      passwd_->GetAsString(&passwd);
    return passwd;
  }
  
 private:
  base_logic::FundamentalValue* uid_;
  base_logic::FundamentalValue* money_;
  base_logic::FundamentalValue* bankcard_id_;
  base_logic::StringValue* passwd_;
};
 
class UserWithdrawList {
 public:
  UserWithdrawList()
    : uid_(NULL),
      status_(NULL),
      start_pos_(NULL),
      count_(NULL) {
  }
  
  ~UserWithdrawList() {
    if (uid_) {
      delete uid_;
      uid_ = NULL;
    }
    if (status_) {
      delete status_;
      status_ = NULL;
    }
    if (start_pos_) {
      delete start_pos_;
      start_pos_ = NULL;
    }
    if (count_) {
      delete count_;
      count_ = NULL;
    }
  }
  
  int32 set_http_packet(base_logic::DictionaryValue* value);
  
  void set_uid(int64 uid) {
    uid_ = new base_logic::FundamentalValue(uid);
  }

  void set_status(std::string& status) {
    if (status == "")
      status = "1,2,3"; //所有记录
    status_ = new base_logic::StringValue(status);
  }

  void set_start_pos(int64 start_pos) {
    start_pos_ = new base_logic::FundamentalValue(start_pos);
  }

  void set_count(int64 count) {
    count_ = new base_logic::FundamentalValue(count);
  }

  int64 uid() {
    int64 uid;
    if (uid_)
      uid_->GetAsBigInteger(&uid);
    return uid;
  }

  std::string status() {
    std::string status;
    if (status_)
      status_->GetAsString(&status);
    return status;
  }

  int64 start_pos() {
    int64 start_pos;
    if (start_pos_)
      start_pos_->GetAsBigInteger(&start_pos);
    return start_pos;
  }
  
  int64 count() {
    int64 count;
    if (count_)
      count_->GetAsBigInteger(&count);
    return count;
  }
  
 private:
  base_logic::FundamentalValue* uid_;
  base_logic::StringValue* status_;
  base_logic::FundamentalValue* start_pos_;
  base_logic::FundamentalValue* count_;
};
 
class ChangeUserInfo {
 public:
  ChangeUserInfo()
    : uid_(NULL),
      nickname_(NULL),
      gender_(NULL),
      head_url_(NULL) {
  }
  
  ~ChangeUserInfo() {
    if (uid_) {
      delete uid_;
      uid_ = NULL;
    }
    if (nickname_) {
      delete nickname_;
      nickname_ = NULL;
    }
    if (gender_) {
      delete gender_;
      gender_ = NULL;
    }
    if (head_url_) {
      delete head_url_;
      head_url_ = NULL;
    }
  }
  
  int32 set_http_packet(base_logic::DictionaryValue* value);

  void set_uid(int64 uid) {
    uid_ = new base_logic::FundamentalValue(uid);
  }

  void set_nickname(std::string& nickname) {
    nickname_ = new base_logic::StringValue(nickname);
  }

  void set_gender(int32 gender) {
    gender_ = new base_logic::FundamentalValue(gender);
  }

  void set_head_url(std::string& head_url) {
    head_url_ = new base_logic::StringValue(head_url);
  }

  int64 uid() {
    int64 uid;
    if (uid_)
      uid_->GetAsBigInteger(&uid);
    return uid;
  }
  
  std::string nickname() {
    std::string nickname;
    if (nickname_)
      nickname_->GetAsString(&nickname);
    return nickname;
  }
  
  int32 gender() {
    int32 gender;
    if (gender_)
      gender_->GetAsInteger(&gender);
    return gender;
  }
  
  std::string head_url() {
    std::string head_url;
    if (head_url_)
      head_url_->GetAsString(&head_url);
    return head_url;
  }

 private:
  base_logic::FundamentalValue* uid_;
  base_logic::StringValue* nickname_;
  base_logic::FundamentalValue* gender_;
  base_logic::StringValue* head_url_;
};

class WXPlaceOrder {
 public:
  WXPlaceOrder()
    : uid_(NULL),
      title_(NULL),
      price_(NULL) {
  }
  
  ~WXPlaceOrder() {
    if (uid_) {
      delete uid_;
      uid_ = NULL;
    }
    if (title_) {
      delete title_;
      title_ = NULL;
    }
    if (price_) {
      delete price_;
      price_ = NULL;
    }
  }
  
  int32 set_http_packet(base_logic::DictionaryValue* value);
    
  void set_uid(int64 uid) {
    uid_ = new base_logic::FundamentalValue(uid);
  }

  void set_title(std::string& title) {
    title_ = new base_logic::StringValue(title);
  }

  void set_price(double price) {
    price_ = new base_logic::FundamentalValue(price);
  }

  int64 uid() {
    int64 uid;
    if (uid_)
      uid_->GetAsBigInteger(&uid);
    return uid;
  }

  std::string title() {
    std::string title;
    if (title_)
      title_->GetAsString(&title);
    return title;
  }
  
  double price() {
    double price;
    if (price_)
      price_->GetAsReal(&price);
    return price;
  }
  
 private:
  base_logic::FundamentalValue* uid_;
  base_logic::StringValue* title_; //应用名-商品名 eg.V领队-高级服务
  base_logic::FundamentalValue* price_; // 订单总价  单位 分
};

class WXPayClient {
 public:
  WXPayClient()
    : uid_(NULL),
      recharge_id_(NULL),
      pay_result_(NULL) {
  }
  
  ~WXPayClient() { 
    if (uid_) {
      delete uid_;
      uid_ = NULL;
    }
    if (recharge_id_) {
      delete recharge_id_;
      recharge_id_ = NULL;
    }
    if (pay_result_) {
      delete pay_result_;
      pay_result_ = NULL;
    }
  }
  
  int32 set_http_packet(base_logic::DictionaryValue* value);
  
  void set_uid(int64 uid) {
    uid_ = new base_logic::FundamentalValue(uid);
  }

  void set_recharge_id(int64 recharge_id) {
    recharge_id_ = new base_logic::FundamentalValue(recharge_id);
  }

  void set_pay_result(int64 pay_result) {
    pay_result_ = new base_logic::FundamentalValue(pay_result);
  }

  int64 uid() {
    int64 uid;
    if (uid_)
      uid_->GetAsBigInteger(&uid);
    return uid;
  }
  
  int64 recharge_id() {
    int64 recharge_id;
    if (recharge_id_)
      recharge_id_->GetAsBigInteger(&recharge_id);
    return recharge_id;
  }
  
  int64 pay_result() {
    int64 pay_result;
    if (pay_result_)
      pay_result_->GetAsBigInteger(&pay_result);
    return pay_result;
  }
  
 private:
  base_logic::FundamentalValue* uid_;
  base_logic::FundamentalValue* recharge_id_;
  base_logic::FundamentalValue* pay_result_; //1-成功 2-取消
};

class WXPayServer {
 public:
  WXPayServer()
    : appid_(NULL), 
      mch_id_(NULL),
    //      xml_str_(NULL),
      total_fee_(NULL),
      recharge_id_(NULL),
      pay_result_(NULL),
      transaction_id_(NULL),
      time_end_(NULL) {
  }
  
  ~WXPayServer() {
    if (appid_) {
      delete appid_;
      appid_ = NULL;
    }
    if (mch_id_) {
      delete mch_id_;
      mch_id_ = NULL;
    }
    /*if (xml_str_) {
      delete xml_str_;
      xml_str_ = NULL:
      }*/
    if (total_fee_) {
      delete total_fee_;
      total_fee_ = NULL;
    }
    if (recharge_id_) {
      delete recharge_id_;
      recharge_id_ = NULL;
    }
    if (pay_result_) {
      delete pay_result_;
      pay_result_ = NULL;
    }
    if (transaction_id_) {
      delete transaction_id_;
      transaction_id_ = NULL;
    }
    if (time_end_) {
      delete time_end_;
      time_end_ = NULL;
    }
  }
  
  int32 set_http_packet(base_logic::DictionaryValue* value);
    
  void set_appid(std::string appid) {
    appid_ = new base_logic::StringValue(appid);
  }

  void set_mch_id(std::string mch_id) {
    mch_id_ = new base_logic::StringValue(mch_id);
  }

  /*void set_xml_str(std::string& xml_str) {
    xml_str_ = new base_logic::StringValue(xml_str);
    }*/

  void set_total_fee(int64 total_fee) {
    total_fee_ = new base_logic::FundamentalValue(total_fee);
  }

  void set_recharge_id(int64 recharge_id) {
    recharge_id_ = new base_logic::FundamentalValue(recharge_id);
  }

  void set_pay_result(int64 pay_result) {
    pay_result_ = new base_logic::FundamentalValue(pay_result);
  }

  void set_transaction_id(std::string transaction_id) {
    transaction_id_ = new base_logic::StringValue(transaction_id);
  }

  void set_time_end(std::string& time_end) {
    time_end_ = new base_logic::StringValue(time_end);
  }

  std::string appid() {
    std::string appid;
    if (appid_)
      appid_->GetAsString(&appid);
    return appid;
  }
  
  std::string mch_id() {
    std::string mch_id;
    if (mch_id_)
      mch_id_->GetAsString(&mch_id);
    return mch_id;
  }
  
  int64 total_fee() {
    int64 total_fee;
    if (total_fee_)
      total_fee_->GetAsBigInteger(&total_fee);
    return total_fee;
  }
  
  int64 recharge_id() {
    int64 recharge_id;
    if (recharge_id_)
      recharge_id_->GetAsBigInteger(&recharge_id);
    return recharge_id;
  }

  int64 pay_result() {
    int64 pay_result;
    if (pay_result_)
      pay_result_->GetAsBigInteger(&pay_result);
    return pay_result;
  }
  
 private:
  base_logic::StringValue* appid_;
  base_logic::StringValue* mch_id_;
  //  base_logic::StringValue* xml_str_;
  base_logic::FundamentalValue* total_fee_;
  base_logic::FundamentalValue* recharge_id_;
  base_logic::FundamentalValue* pay_result_; //1 - 支付成功
  base_logic::StringValue* transaction_id_;
  base_logic::StringValue* time_end_;
};

class UnionpayPlaceOrder {
 public:
  UnionpayPlaceOrder()
    : uid_(NULL),
      title_(NULL),
      price_(NULL) {
  }
  
  ~UnionpayPlaceOrder() {
    if (uid_) {
      delete uid_;
      uid_ = NULL;
    }
    if (title_) {
      delete title_;
      title_ = NULL;
    }
    if (price_) {
      delete price_;
      price_ = NULL;
    }
  }
  
  int32 set_http_packet(base_logic::DictionaryValue* value);
    
  void set_uid(int64 uid) {
    uid_ = new base_logic::FundamentalValue(uid);
  }

  void set_title(std::string& title) {
    title_ = new base_logic::StringValue(title);
  }

  void set_price(double price) {
    price_ = new base_logic::FundamentalValue(price);
  }

  int64 uid() {
    int64 uid;
    if (uid_)
      uid_->GetAsBigInteger(&uid);
    return uid;
  }

  std::string title() {
    std::string title;
    if (title_)
      title_->GetAsString(&title);
    return title;
  }
  
  double price() {
    double price;
    if (price_)
      price_->GetAsReal(&price);
    return price;
  }
  
 private:
  base_logic::FundamentalValue* uid_;
  base_logic::StringValue* title_; //应用名-商品名 eg.V领队-高级服务
  base_logic::FundamentalValue* price_; // 订单总价  单位 分
};

/*class SMSCodeLogin {
 public:
  SMSCodeLogin();
  int64 timestamp() { return timestamp_; }
  int64 verify_code() { return verify_code_; }
  std::string phone_num() { return phone_num_; }
  std::string token() { return token_; }
  int64 user_type() { return user_type_; }
 private:
  int64 timestamp_;
  int64 verify_code_;
  int64 user_type_;
  std::string phone_num_;
  std::string token_;
  };*/

class ObtainVerifyCode {
 public:
  ObtainVerifyCode()
    : verify_type_(NULL),
      phone_num_(NULL) {
  }
  
  ~ObtainVerifyCode() {
    if (verify_type_) {
      delete verify_type_;
      verify_type_ = NULL;
    }
    if (phone_num_) {
      delete phone_num_;
      phone_num_ = NULL;
    }
  }
  
  int32 set_http_packet(base_logic::DictionaryValue* value);
  
  void set_verify_type(int32 verify_type) {
    verify_type_ = new base_logic::FundamentalValue(verify_type);
  }

  void set_phone_num(std::string& phone_num) {
    phone_num_ = new base_logic::StringValue(phone_num);
  }

  int32 verify_type() {
    int32 verify_type;
    if (verify_type_)
      verify_type_->GetAsInteger(&verify_type);
    return verify_type;
  }
  
  std::string phone_num() {
    std::string phone_num;
    if (phone_num_)
      phone_num_->GetAsString(&phone_num);
    return phone_num;
  }
  
 private:
  base_logic::FundamentalValue* verify_type_;
  base_logic::StringValue* phone_num_;
};

/*class DeviceToken {
 public:
  DeviceToken();

  int64 uid() { return uid_; }
  std::string device_token() { return device_token_; }
 private:
  int64 uid_;
  std::string device_token_;
  };*/

class DeviceToken {
 public:
  DeviceToken()
    : uid_(NULL),
      device_token_(NULL) {
  }
  
  ~DeviceToken() {
    if (uid_) {
      delete uid_;
      uid_ = NULL;
    }
    if (device_token_) {
      delete device_token_;
      device_token_ = NULL;
    }
  }
  
  int32 set_http_packet(base_logic::DictionaryValue* value);
  
  void set_uid(const int64 uid) {
    uid_ = new base_logic::FundamentalValue(uid);
  }

  void set_device_token(const std::string& device_token) {
    device_token_ = new base_logic::StringValue(device_token);
  }

  const int64 uid() {
    int64 uid = 0;
    if (uid_)
      uid_->GetAsBigInteger(&uid);
    return uid;
  }
  
  const std::string device_token() {
    std::string device_token;
    if (device_token_)
      device_token_->GetAsString(&device_token);
    return device_token;
  }
  
 private:
  base_logic::FundamentalValue* uid_;
  base_logic::StringValue* device_token_;
};

/*class UserCash {
 public:
  UserCash();

  int64 uid() { return uid_; }
 private:
  int64 uid_;
  };*/
//send


/*class CheckSMSCode {
 public:
  CheckSMSCode ();

  int64 verify_code() { return verify_code_; }
  int64 verify_type() { return verify_type_; }
  int64 timestamp() { return timestamp_; }
  std::string phone_num() { return phone_num_; }
  std::string token() { return token_; }
 private:
  int64 verify_code_;
  int64 verify_type_; //0-注册 1-登录 2-更新服务
  int64 timestamp_; //时间戳
  std::string phone_num_;
  std::string token_;
  };*/

} //namespace net_request
 
namespace net_reply {
  
  

}
 
} //namespace user

#endif  // PLUGINS_USER_USER_PROTO_H_
