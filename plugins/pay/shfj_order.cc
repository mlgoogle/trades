//  Copyright (c) 2017-2018 The SWP Authors. All rights reserved.
//  Created on: 2017年1月12日 Author: kerry

#include "pay/shfj_order.h"

#include <iostream>
#include <sstream>
#include "basic/md5sum.h"
#include "logic/logic_unit.h"
#include "logic/logic_comm.h"

namespace pay_logic {
///---
int32 GetSHFJCashStatus(const std::string &status)
{
  int32 r = 0;
  if (status == "PAYED")
    r = 2; //提现成功
  else if (status == "PYAING")
    r = 1; //提现中
  else if (status == "PAY_FAILED")
    r = 3; //付款失败
  else if (status == "REFUND")
    r = 4; //已退款
  return r;
}
const std::string PASSWORD = "hsx888";
SHFJOrder::SHFJOrder() {
  total_fee = 0;
  fee = 0;
  transfer_amount = 0;  
}

SHFJOrder::~SHFJOrder() {
}

std::string UrlDecode(const std::string& szToDecode)  
{  
  std::string result;  
  int hex = 0;  
  for (size_t i = 0; i < szToDecode.length(); ++i)  
  {   
    switch (szToDecode[i])  
    {   
      case '+':  
        result += ' ';  
        break;  
      case '%':  
        if (isxdigit(szToDecode[i + 1]) && isxdigit(szToDecode[i + 2]))  
        {   
          std::string hexStr = szToDecode.substr(i + 1, 2);  
          hex = strtol(hexStr.c_str(), 0, 16);//字母和数字[0-9a-zA-Z]、一些特殊符号[$-_.+!*'(),] 、以及某些保留字[$&+,/:;=?@] //可以不经过编码直接用于URL  
          if (!((hex >= 48 && hex <= 57) || //0-9  
	  (hex >=97 && hex <= 122) ||   //a-z  
	  (hex >=65 && hex <= 90) ||    //A-Z       //一些特殊符号及保留字[$-_.+!*'(),]  [$&+,/:;=?@]  
	  hex == 0x21 || hex == 0x24 || hex == 0x26 || hex == 0x27 || hex == 0x28 || hex == 0x29 
	  || hex == 0x2a || hex == 0x2b|| hex == 0x2c || hex == 0x2d || hex == 0x2e || hex == 0x2f 
	  || hex == 0x3A || hex == 0x3B|| hex == 0x3D || hex == 0x3f || hex == 0x40 || hex == 0x5f 
	  ))  
	  {   
            result += char(hex);
            i += 2;  
          }   
          else result += '%';  
        }
	else 
          result += '%';  
        break;  
      default:  
        result += szToDecode[i];  
        break;  
    }   
  }   
  return result;
}   


void SHFJOrder::InitWxVerify(const std::string& id, 
                           const std::string& p_type, 
                           const std::string& ctent) {
  appid = id;
  //mch_id = m_id;
  mch_id = T_MCH_ID;
  notify_url = T_NOTIFY_URL;
  pay_type = p_type;
  content = ctent;
//
  nonce_str = logic::SomeUtils::RandomString(32);
}

void SHFJOrder::InitWxVerify(const std::string& id) {
//cash use
  appid = id;
  mch_id = T_MCH_ID;
  notify_url = T_CASH_NOTIFY_URL;
}

static std::string Upper(std::string &text) {
  for (unsigned int i = 0; i < text.length(); i ++)
  {
	if (text[i] >= 'a' && text[i] <= 'z')
		text[i] = text[i] - 32;
  }
return text;
}

void SHFJOrder::PlaceOrderSign(const std::string &body, bool iscash) {
  std::stringstream ss;
  //std::string req_url = THIRD_URL+"";
  std::string req_url = THIRD_URL + "com.opentech.cloud.easypay.trade.create/0.0.1";
  if (iscash)
    req_url = THIRD_CASH_URL + "com.opentech.cloud.easypay.balance.pay/0.0.1";
  ss << req_url;


  ss << "&x-oapi-pv=0.0.1"
   << "&x-oapi-sdkv=0.0.1/c" 
   << "&x-oapi-sk=" << T_APP_KEY	  //证书key
   << "&x-oapi-sm=MD5"
   << "&" << body;

  ss << "&" << T_MD5_KEY;

  LOG_DEBUG2("THIRD_ORDER_SIGN before: %s",ss.str().c_str());
  base::MD5Sum md5sum(ss.str());
  LOG_DEBUG2("THIRD_ORDER_SIGN_MD5 after: %s",md5sum.GetHash().c_str());
  sign = md5sum.GetHash();
  Upper(sign);
  LOG_DEBUG2("THIRD_ORDER_SIGN_MD5 after2___________: %s",md5sum.GetHash().c_str());
}

/*
*/

std::string SHFJOrder::PostFiled(bool iscash) {
  base_logic::DictionaryValue dic;

  dic.SetBigInteger(L"amount", total_fee);
  dic.SetString(L"callbackURL", notify_url);
  if (iscash)
  {
    dic.SetString(L"merchantNo", mch_id);
    dic.SetString(L"outPayNo", out_trade_no);
    dic.SetString(L"payPassword", PASSWORD);
    dic.SetString(L"receiverAccountName", rec_account_name);
    dic.SetString(L"receiverBankName", rec_bank_name);
    dic.SetString(L"receiverBranchBankName", rec_branch_bank_name);
    dic.SetString(L"receiverCardNo", rec_card_no);
  }
  else
  {
    dic.SetString(L"content", content);
    dic.SetString(L"merchantNo", mch_id);
    dic.SetString(L"outTradeNo", out_trade_no);
    dic.SetString(L"payType", pay_type);
    dic.SetString(L"wechatOpenId", wechat_openid);
    dic.SetString(L"wechatAppId", wechat_appid);
  }

  std::string filed = "";
  base_logic::ValueSerializer* serializer = base_logic::ValueSerializer::Create(
      base_logic::IMPL_JSON, &filed);
  serializer->Serialize(dic);
  base_logic::ValueSerializer::DeleteSerializer(base_logic::IMPL_JSON,
                                                serializer);
  return filed;
}
void SHFJOrder::Set_Headers(http::HttpMethodPost &hmp)
{
  std::string headers = "x-oapi-pv: 0.0.1";
  hmp.SetHeaders(headers); //api version
  headers = "x-oapi-sdkv: 0.0.1/c"; 
  hmp.SetHeaders(headers);	  //sdk version

  headers = "x-oapi-sk: " + T_APP_KEY;	  //证书key
  hmp.SetHeaders(headers);
  headers = "x-oapi-sm: MD5";
  hmp.SetHeaders(headers);
  headers = "x-oapi-sign: " + sign;
  hmp.SetHeaders(headers);
//
  headers = "Accept: application/json";    
  hmp.SetHeaders(headers); 
  headers = "Content-Type: application/json";  
  hmp.SetHeaders(headers); 
  headers = "charsets: utf-8";     
  hmp.SetHeaders(headers); 
  headers = "User-Agent: easypay-api-sdk/c";     
  hmp.SetHeaders(headers); 
}

std::string SHFJOrder::CashPlaceOrder(const std::string& id) {
  InitWxVerify(id);
  std::string body = PostFiled(true);
  PlaceOrderSign(body ,true);

  std::string url = THIRD_CASH_URL + "com.opentech.cloud.easypay.balance.pay/0.0.1";
  http::HttpMethodPost hmp(url);
  Set_Headers(hmp);
///-------------
  hmp.Post(body.c_str());

////get header message
  std::string err_key = "x-oapi-error-code";
  MIG_VALUE err_value, mes_value;
  
  hmp.GetHeader(err_key, err_value);
  MIG_VALUE::iterator iter,msg_iter;
  for (iter = err_value.begin(); iter != err_value.end(); iter++)
    LOG_DEBUG2("err_value_____[%s]", iter->c_str());
  std::string msg_key = "x-oapi-msg";
  hmp.GetHeader(msg_key, mes_value);

  for (msg_iter = mes_value.begin(); msg_iter != mes_value.end(); msg_iter ++)
  {
    LOG_DEBUG2("msg_value_____[%s]", msg_iter->c_str());
    LOG_DEBUG2("msg_value_____[%s]", UrlDecode((*msg_iter)).c_str());

  }
/////
//
//----------------
  std::string result;
  hmp.GetContent(result);
  //LOG(INFO)<< "http post result:" << result;
  LOG_DEBUG2("http post result: %s", result.c_str());
  return result;
}

std::string SHFJOrder::PlaceOrder(const std::string& id, 
                                const std::string& pay_type,
                                const std::string& content) {
  LOG_ERROR("PlaceOrder start..................\n"); //tw test
  std::string url = THIRD_URL + "com.opentech.cloud.easypay.trade.create/0.0.1";
  InitWxVerify(id, pay_type, content);
  std::string body = PostFiled();
  PlaceOrderSign(body);
  http::HttpMethodPost hmp(url);
  Set_Headers(hmp);
///
  //hmp.Post(PostFiled().c_str());
  hmp.Post(body.c_str());
  std::string result;
  hmp.GetContent(result);

////get header message
  std::string err_key = "x-oapi-error-code";
  MIG_VALUE err_value, mes_value;
  
  hmp.GetHeader(err_key, err_value);
  MIG_VALUE::iterator iter, msg_iter;
  for (iter = err_value.begin(); iter != err_value.end(); iter++)
    LOG_DEBUG2("err_value_____[%s]", iter->c_str());

  std::string msg_key = "x-oapi-msg";
  hmp.GetHeader(msg_key, mes_value);

  for (msg_iter = mes_value.begin(); msg_iter != mes_value.end(); msg_iter ++)
  {
    LOG_DEBUG2("msg_value_____[%s]", msg_iter->c_str());
    LOG_DEBUG2("msg_value_____[%s]", UrlDecode((*msg_iter)).c_str());

  }
/////

  //LOG(INFO)<< "http post result:" << result;
  LOG_DEBUG2("http post result: %s", result.c_str());
  LOG_ERROR2("PlaceOrder end.......result[%s]...........\n", result.c_str()); //tw test
  LOG_ERROR("PlaceOrder end..................\n"); //tw test
  return result;
}

}//namespace pay_logic

