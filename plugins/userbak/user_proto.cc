// Copyright (c) 2016 The tourism Authors. All rights reserved.
// user_proto.cc
// Created on: 2016年8月12日.
// Author: Paco.

#include "user/user_proto.h"

#include <typeinfo>

//#include "glog/logging.h"
#include "logic/base_values.h"
#include "basic/md5sum.h"

#include "comm/comm_head.h"
#include "util/util.h"
#include "logic/logic_comm.h"

namespace user {

namespace net_request {

int32 Heartbeat::set_http_packet(base_logic::DictionaryValue* value) {
  int32 err = 0;
  bool r = false;
  int64 uid;
  do {
    if (value != NULL) {
      r = value->GetBigInteger(L"uid_", &uid);
      if (r)
        set_uid(uid);
      if (!r) LOG_ERROR("Heartbeat::uid_ parse error");
    } else {
      LOG_ERROR("Heartbeat set_http_packet error");
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  return err;
}

int32 UserInfo::set_http_packet(base_logic::DictionaryValue* value) {
  int32 err = 0;
  bool r = false;
  std::string uid_str;
  do {
    if (value != NULL) {
      r = value->GetString(L"uidStr", &uid_str);
      if (r)
        set_uid_str(uid_str);
      if (!r) LOG_ERROR("UserInfo::uid_str_ parse error");
    } else {
      LOG_ERROR("UserInfo set_http_packet error");
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  return err;
}

int32 AccountInfo::set_http_packet(base_logic::DictionaryValue* value) {
  int32 err = 0;
  bool r = false;
  int64 uid;
  do {
    if (value != NULL) {
      r = value->GetBigInteger(L"id", &uid);
      if (r)
        set_uid(uid);
      if (!r) LOG_ERROR("AccountInfo::uid_ parse error");
    } else {
      LOG_ERROR("AccountInfo set_http_packet error");
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  return err;
}
	
int32 OrderList::set_http_packet(base_logic::DictionaryValue* value) {
  int32 err = 0;
  bool r = false;
  int64 uid;
  std::string flow_type;
  int32 start_pos;
  int32 count;
  do {
    if (value != NULL) {
      r = value->GetBigInteger(L"id", &uid);
      if (r)
        set_uid(uid);
      if (!r) LOG_ERROR("OrderList::uid_ parse error");
      r = value->GetString(L"flowType", &flow_type);
      if (r)
        set_flow_type(flow_type);
      if (!r) LOG_ERROR("OrderDetail::flow_type_ parse error");
      r = value->GetInteger(L"startPos", &start_pos);
      if (r)
        set_start_pos(start_pos);
      if (!r) LOG_ERROR("OrderDetail::start_pos_ parse error");
      r = value->GetInteger(L"count", &count);
      if (r)
        set_count(count);
      if (!r) LOG_ERROR("OrderDetail::count_ parse error");
    } else {
      LOG_ERROR("OrderDetail set_http_packet error");
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  return err;
}
	
int32 OrderDetail::set_http_packet(base_logic::DictionaryValue* value) {
  int32 err = 0;
  bool r = false;
  int64 uid;
  int64 flow_id;
  int32 flow_type;
  do {
    if (value != NULL) {
      r = value->GetBigInteger(L"id", &uid);
      if (r)
        set_uid(uid);
      if (!r) LOG_ERROR("OrderDetail::uid_ parse error");
      r = value->GetBigInteger(L"flowId", &flow_id);
      if (r)
        set_flow_id(flow_id);
      if (!r) LOG_ERROR("OrderDetail::flow_id_ parse error");
      r = value->GetInteger(L"flowType", &flow_type);
      if (r)
        set_flow_type(flow_type);
      if (!r) LOG_ERROR("OrderDetail::flow_type_ parse error");
    } else {
      LOG_ERROR("OrderDetail set_http_packet error");
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  return err;
}
	
int32 BankcardList::set_http_packet(base_logic::DictionaryValue* value) {
  int32 err = 0;
  bool r = false;
  int64 uid;
  do {
    if (value != NULL) {
      r = value->GetBigInteger(L"id", &uid);
      if (r)
        set_uid(uid);
      if (!r) LOG_ERROR("BankcardList::uid_ parse error");
    } else {
      LOG_ERROR("BankcardList set_http_packet error");
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  return err;
}
	
int32 BindBankcard::set_http_packet(base_logic::DictionaryValue* value) {
  int32 err = 0;
  bool r = false;
  int64 uid;
  int64 bank_id;
  std::string branch_bank;
  std::string bankcard_num;
  std::string bank_username;
  
  do {
    if (value != NULL) {
      r = value->GetBigInteger(L"id", &uid);
      if (r)
        set_uid(uid);
      if (!r) LOG_ERROR("BindBankcard::uid_ parse error");
      r = value->GetBigInteger(L"bankId", &bank_id);
      if (r)
        set_bank_id(bank_id);
      if (!r) LOG_ERROR("BindBankcard::bank_id_ parse error");
      r = value->GetString(L"branchBank", &branch_bank);
      if (r)
        set_branch_bank(branch_bank);
      if (!r) LOG_ERROR("BindBankcard::branch_bank_ parse error");
      r = value->GetString(L"cardNo", &bankcard_num);
      if (r)
        set_bankcard_num(bankcard_num);
      if (!r) LOG_ERROR("BindBankcard::bankcard_num_ parse error");
      r = value->GetString(L"name", &bank_username);
      if (r)
        set_bank_username(bank_username);
      if (!r) LOG_ERROR("BindBankcard::bank_username_ parse error");
    } else {
      LOG_ERROR("BindBankcard set_http_packet error");
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  return err;
}
	
int32 UnbindBankcard::set_http_packet(base_logic::DictionaryValue* value) {
  int32 err = 0;
  bool r = false;
  std::string phone_num;
  int64 bankcard_id;
  std::string verify_code;
  int64 timestamp;
  std::string verify_token;
  do {
    if (value != NULL) {
      r = value->GetString(L"phone", &phone_num);
      if (r)
        set_phone_num(phone_num);
      if (!r) LOG_ERROR("UnbindBankcard::phone_num_ parse error");
      r = value->GetBigInteger(L"bid", &bankcard_id);
      if (r)
        set_bankcard_id(bankcard_id);
      if (!r) LOG_ERROR("UnbindBankcard::bankcard_id_ parse error");
      /*r = value->GetString(L"vCode", &verify_code);
      if (r)
        set_verify_code(verify_code);
      if (!r) LOG_ERROR("UnbindBankcard::verify_code_ parse error");
      r = value->GetBigInteger(L"timestamp", &timestamp);
      if (r)
        set_timestamp(timestamp);
      if (!r) LOG_ERROR("UnbindBankcard::timestamp_ parse error");
      r = value->GetString(L"vToken", &verify_token);
      if (r)
        set_verify_token(verify_token);
        if (!r) LOG_ERROR("UnbindBankcard::verify_token_ parse error");*/
    } else {
      LOG_ERROR("UnbindBankcard set_http_packet error");
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  return err;
}
	
int32 ChangeDefaultBankcard::set_http_packet(base_logic::DictionaryValue* value) {
  int32 err = 0;
  bool r = false;
  int64 uid;
  int64 bankcard_id;
  do {
    if (value != NULL) {
      r = value->GetBigInteger(L"id", &uid);
      if (r)
        set_uid(uid);
      if (!r) LOG_ERROR("ChangeDefaultBankcard::uid_ parse error");
      r = value->GetBigInteger(L"bid", &bankcard_id);
      if (r)
        set_bankcard_id(bankcard_id);
      if (!r) LOG_ERROR("ChangeDefaultBankcard::bankcard_id_ parse error");
    } else {
      LOG_ERROR("ChangeDefaultBankcard set_http_packet error");
  		err = JSON_FORMAT_ERR;
  		break;
  	}
  }while (0);
  return err;
}
	
int32 CreditList::set_http_packet(base_logic::DictionaryValue* value) {
  int32 err = 0;
  bool r = false;
  int64 uid;
  std::string status;
  int64 start_pos; 
  int64 count;
  do {
    if (value != NULL) {
      r = value->GetBigInteger(L"id", &uid);
      if (r)
        set_uid(uid);
      if (!r) LOG_ERROR("CreditList::uid_ parse error");
      r = value->GetString(L"status", &status);
      if (r)
        set_status(status);
      if (!r) LOG_ERROR("CreditList::status_ parse error");
      r = value->GetBigInteger(L"startPos", &start_pos);
      if (r)
        set_start_pos(start_pos);
      if (!r) LOG_ERROR("CreditList::start_pos_ parse error");
      r = value->GetBigInteger(L"count", &count);
      if (r)
        set_count(count);
      if (!r) LOG_ERROR("CreditList::count_ parse error");
    } else {
      LOG_ERROR("CreditList set_http_packet error");
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  return err;
}
	
  /*int32 CreditDetail::set_http_packet(base_logic::DictionaryValue* value) {
  int32 err = 0;
  bool r = false;
  int64 uid;
  int64 recharge_id;
  do {
    if (value != NULL) {
      r = value->GetBigInteger(L"id", &uid);
      if (r)
        set_uid(uid);
      if (!r) LOG_ERROR("CreditDetail::uid_ parse error");
      r = value->GetBigInteger(L"rid", &recharge_id);
      if (r)
        set_recharge_id(recharge_id);
      if (!r) LOG_ERROR("CreditDetail::recharge_id_ parse error");
    } else {
      LOG_ERROR("CreditDetail set_http_packet error");
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  return err;
  }*/
	
int32 UserWithdraw::set_http_packet(base_logic::DictionaryValue* value) {
  int32 err = 0;
  bool r = false;
  int64 uid;
  double money;
  int64 bankcard_id;
  std::string passwd;
  do {
    if (value != NULL) {
      r = value->GetBigInteger(L"id", &uid);
      if (r)
        set_uid(uid);
      if (!r) LOG_ERROR("UserWithdraw::uid_ parse error");
      r = value->GetReal(L"money", &money);
      if (r)
        set_money(money);
      if (!r) LOG_ERROR("UserWithdraw::money_ parse error");
      r = value->GetBigInteger(L"bid", &bankcard_id);
      if (r)
        set_bankcard_id(bankcard_id);
      if (!r) LOG_ERROR("UserWithdraw::bankcard_id_ parse error");
      r = value->GetString(L"pwd", &passwd);
      if (r)
        set_passwd(passwd);
      if (!r) LOG_ERROR("UserWithdraw::passwd_ parse error");
    } else {
      LOG_ERROR("UserWithdraw set_http_packet error");
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  return err;
}

int32 UserWithdrawList::set_http_packet(base_logic::DictionaryValue* value) {
  int32 err = 0;
  bool r = false;
  int64 uid;
  std::string status; 
  int64 start_pos;
  int64 count;
  do {
    if (value != NULL) {
      r = value->GetBigInteger(L"id", &uid);
      if (r)
        set_uid(uid);
      if (!r) LOG_ERROR("UserWithdrawList::uid_ parse error");
      r = value->GetString(L"status", &status);
      if (r)
        set_status(status);
      if (!r) LOG_ERROR("UserWithdrawList::status_ parse error");
      r = value->GetBigInteger(L"startPos", &start_pos);
      if (r)
        set_start_pos(start_pos);
      if (!r) LOG_ERROR("UserWithdrawList::start_pos_ parse error");
      r = value->GetBigInteger(L"count", &count);
      if (r)
        set_count(count);
      if (!r) LOG_ERROR("UserWithdrawList::count_ parse error");
    } else {
      LOG_ERROR("UserWithdrawList set_http_packet error");
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  return err;
}

int32 ObtainVerifyCode::set_http_packet(base_logic::DictionaryValue* value) {
  int32 err = 0;
  bool r = false;
  int64 verify_type;
  std::string phone_num;
  do {
    if (value != NULL) {
      r = value->GetBigInteger(L"verifyType", &verify_type);
      if (r)
        set_verify_type(verify_type);
      if (!r) LOG_ERROR("ObtainVerifyCode::verify_type_ parse error");
      r = value->GetString(L"phone", &phone_num);
      if (r)
        set_phone_num(phone_num);
      if (!r) LOG_ERROR("ObtainVerifyCode::phone_num_ parse error");
    } else {
      LOG_ERROR("ObtainVerifyCode set_http_packet error");
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  return err;
}
	
int32 ChangeUserInfo::set_http_packet(base_logic::DictionaryValue* value) {
  int32 err = 0;
  bool r = false;
  int64 uid;
  std::string nickname;
  int64 gender;
  std::string head_url;
  do {
    if (value != NULL) {
      r = value->GetBigInteger(L"id", &uid);
      if (r)
        set_uid(uid);
      if (!r) LOG_ERROR("ChangeUserInfo::uid_ parse error");
      r = value->GetString(L"screenName", &nickname);
      if (r)
        set_nickname(nickname);
      if (!r) LOG_ERROR("ChangeUserInfo::nickname_ parse error");
      r = value->GetBigInteger(L"gender", &gender);
      if (r)
        set_gender(gender);
      if (!r) LOG_ERROR("ChangeUserInfo::gender_ parse error");
      r = value->GetString(L"avatarLarge", &head_url);
      if (r)
        set_head_url(head_url);
      if (!r) LOG_ERROR("ChangeUserInfo::head_url_ parse error");
    } else {
      LOG_ERROR("ChangeUserInfo set_http_packet error");
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  return err;
}

int32 WXPlaceOrder::set_http_packet(base_logic::DictionaryValue* value) {
  int32 err = 0;
  bool r = false;
  int64 uid;
  std::string title;
  double price;
  do {
    if (value != NULL) {
      r = value->GetBigInteger(L"id", &uid);
      if (r)
        set_uid(uid);
      if (!r) LOG_ERROR("WXPlaceOrder::uid_ parse error");
      r = value->GetString(L"title", &title);
      if (r)
        set_title(title);
      if (!r) LOG_ERROR("WXPlaceOrder::title_ parse error");
      r = value->GetReal(L"price", &price);
      if (r)
        set_price(price);
      if (!r) LOG_ERROR("WXPlaceOrder::price_ parse error");
    } else {
      LOG_ERROR("WXPlaceOrder set_http_packet error");
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  return err;
}

int32 WXPayClient::set_http_packet(base_logic::DictionaryValue* value) {
  int32 err = 0;
  bool r = false;
  int64 uid;
  int64 recharge_id;
  int64 pay_result;
  do {
    if (value != NULL) {
      r = value->GetBigInteger(L"id", &uid);
      if (r)
        set_uid(uid);
      if (!r) LOG_ERROR("WXPayClient::uid_ parse error");
      r = value->GetBigInteger(L"rid", &recharge_id);
      if (r)
        set_recharge_id(recharge_id);
      if (!r) LOG_ERROR("WXPayClient::recharge_id_ parse error");
      r = value->GetBigInteger(L"payResult", &pay_result);
      if (r)
        set_pay_result(pay_result);
      if (!r) LOG_ERROR("WXPayClient::pay_result_ parse error");
    } else {
      LOG_ERROR("WXPlaceOrder set_http_packet error");
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  return err;
}

int32 WXPayServer::set_http_packet(base_logic::DictionaryValue* value) {
  int32 err = 0;
  bool r = false;
  std::string err_str;
  std::string xml_str;
  std::string appid;
  std::string mch_id;
  int64 total_fee;
  std::string transaction_id; 
  do {
    if (value != NULL) {
      r = value->GetString(L"result", &xml_str);
      if (!r) LOG_ERROR("WXPayServer::xml_str parse error");
      LOG_MSG2("WXPAY SERVER RESULT***%s***", xml_str.c_str());
      if (r && xml_str.length() > 5) {
        base_logic::ValueSerializer* deserializer =
            base_logic::ValueSerializer::Create(base_logic::IMPL_XML,
                                                &xml_str);
        int32 err = 0;
        DicValue* xml_value = (DicValue*) deserializer->Deserialize(&err, &err_str);
        if (xml_value != NULL) {
          r = xml_value->GetString(L"appid", &appid);
          if (r)
            set_appid(util::GetWxpayXmlValue(appid));
          r = xml_value->GetString(L"mch_id", &mch_id);
          if (r)
            set_mch_id(util::GetWxpayXmlValue(mch_id));
          std::string return_code;
          xml_value->GetString(L"return_code", &return_code);
          //通信成功标识
          if (return_code.find("SUCCESS") != std::string::npos) {
            std::string result_code;
            xml_value->GetString(L"result_code", &result_code);

            //订单总金额
            r = xml_value->GetBigInteger(L"total_fee", &total_fee);
            if (r)
              set_total_fee(total_fee);
            //支付总金额
            r = xml_value->GetString(L"transaction_id", &transaction_id);
            if (r)
              set_transaction_id(util::GetWxpayXmlValue(transaction_id));
            //本平台订单号
            std::string out_trade_no;
            r = xml_value->GetString(L"out_trade_no", &out_trade_no);
            if (r) {
              int npos1 = out_trade_no.find("<![CDATA[");
              int npos2 = out_trade_no.find("]]>");
              out_trade_no = out_trade_no.substr(npos1 + 9,
                                               npos2 - npos1 - 9 - 6);
              set_recharge_id(atol(out_trade_no.c_str()));
            }
            //支付成功标识
            if (result_code.find("SUCCESS") != std::string::npos) {
              set_pay_result(1);
            } else {
              set_pay_result(-1);
            }
          }
        } else {
          LOG_ERROR("WXPlaceOrder xml  set_http_packet error");
        }
        base_logic::ValueSerializer::DeleteSerializer(base_logic::IMPL_XML,
                                                      deserializer);
      }
    } else {
      LOG_ERROR("WXPlaceOrder json set_http_packet error");
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  return err;
}

int32 UnionpayPlaceOrder::set_http_packet(base_logic::DictionaryValue* value) {
  int32 err = 0;
  bool r = false;
  int64 uid;
  std::string title;
  double price;
  do {
    if (value != NULL) {
      r = value->GetBigInteger(L"id", &uid);
      if (r)
        set_uid(uid);
      if (!r) LOG_ERROR("UnionpayPlaceOrder::uid_ parse error");
      r = value->GetString(L"title", &title);
      if (r)
        set_title(title);
      if (!r) LOG_ERROR("UnionpayPlaceOrder::title_ parse error");
      r = value->GetReal(L"price", &price);
      if (r)
        set_price(price);
      if (!r) LOG_ERROR("UnionpayPlaceOrder::price_ parse error");
    } else {
      LOG_ERROR("UnionpayPlaceOrder set_http_packet error");
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  return err;
}

  /*int32 SMSCodeLogin::set_http_packet(base_logic::DictionaryValue* value) {
  int32 err = 0;
  bool r = false;
  int64 timestamp;
  int64 verify_code;
  int64 user_type;
  std::string phone_num;
  std::string token;
  do {
    if (value != NULL) {
      r = value->GetBigInteger(L"timestamp_", &timestamp);
      if (r)
        set_timestamp(timestamp);
      if (!r) LOG_ERROR("SMSCodeLogin::timestamp_ parse error");
      r = value->GetBigInteger(L"verify_code_", &verify_code);
      if (r)
        set_uid(uid);
      if (!r) LOG_ERROR("SMSCodeLogin::verify_code_ parse error");
      r = value->GetBigInteger(L"user_type_", &user_type);
      if (!r) LOG_ERROR("SMSCodeLogin::user_type_ parse error");
      r = value->GetString(L"phone_num_", &phone_num);
      if (!r) LOG_ERROR("SMSCodeLogin::phone_num_ parse error");
      r = value->GetString(L"token_", &token);
      if (!r) LOG_ERROR("SMSCodeLogin::token_ parse error");
    } else {
      LOG_ERROR("SMSCodeLogin set_http_packet error");
      err = JSON_FORMAT_ERR;
      break;
    }
    }while (0);
  return err;
}*/

int32 DeviceToken::set_http_packet(base_logic::DictionaryValue* value) {
  int32 err = 0;
  bool r = false;
  int64 uid;
  std::string device_token;
  do {
    if (value != NULL) {
      r = value->GetBigInteger(L"uid_", &uid);
      if (r)
        set_uid(uid);
      if (!r) LOG_ERROR("DeviceToken::uid_ parse error");
      r = value->GetString(L"device_token_", &device_token);
      if (r)
        set_device_token(device_token);
      if (!r) LOG_ERROR("DeviceToken::device_token_ parse error");
    } else {
      LOG_ERROR("DeviceToken set_http_packet error");
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  return err;
}

  /*int32 UserCash::set_http_packet(base_logic::DictionaryValue* value) {
  int32 err = 0;
  bool r = false;
  int64 uid;
  do {
    if (value != NULL) {
      r = value->GetBigInteger(L"uid_", &uid);
      if (r)
        set_uid(uid);
      if (!r) LOG_ERROR("UserCash::uid_ parse error");
    } else {
      LOG_ERROR("UserCash set_http_packet error");
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  return err;
  }*/

  /*int32 CheckSMSCode::set_http_packet(base_logic::DictionaryValue* value) {
  int32 err = 0;
  bool r = false;
  do {
    if (value != NULL) {
      r = value->GetBigInteger(L"timestamp_", &timestamp);
      if (!r) LOG_ERROR("CheckSMSCode::timestamp_ parse error");
      r = value->GetBigInteger(L"verify_code_", &verify_code);
      if (!r) LOG_ERROR("CheckSMSCode::verify_code_ parse error");
      r = value->GetBigInteger(L"verify_type_", &verify_type);
      if (!r) LOG_ERROR("CheckSMSCode::verify_type_ parse error");
      r = value->GetString(L"phone_num_", &phone_num);
      if (!r) LOG_ERROR("CheckSMSCode::phone_num_ parse error");
      r = value->GetString(L"token_", &token);
      if (!r) LOG_ERROR("CheckSMSCode::token_ parse error");
    } else {
      LOG_ERROR("CheckSMSCode set_http_packet error");
      err = JSON_FORMAT_ERR;
      break;
    }
    }while (0);
  return err;
  }*/
} // namespace net_request

}  // namespace user

