#include <iostream>
#include <string>
#include <sstream>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

#include "curl_easy.h"
#include "curl_form.h"
#include "curl_option.h"

#include "json11.h"

using curl::curl_easy;
using curl::curl_form;
using curl::make_option;

std::string getStringByUri(std::string uri);
std::vector<json11::Json> getVectorByUri(std::string uri);
std::string ISO8601toUnixTime(std::string datetime);


int main(int argc, const char **argv) {
    //資料庫
    mongocxx::instance inst{};
    mongocxx::client conn{};
    auto collection = conn["homework"]["crawlercpp"];

    //access_token 認證參數
    std::string uri="https://graph.facebook.com/oauth/access_token?client_id=&client_secret=&grant_type=client_credentials";

    //std::string access_token+=getContentByUri(uri); //app access_token
    std::string access_token="access_token=";

    std::string search="https://graph.facebook.com/v2.3/search?q=高級中學&type=group&" + access_token;

    std::vector<json11::Json> groups = getVectorByUri(search);
    for (auto &group : groups) {
      std::string gid = group["id"].string_value();
      std::string group_uri = "https://graph.facebook.com/" + gid;
      
      std::string err;
      std::string gstr = getStringByUri(group_uri);
      auto group_detail = json11::Json::parse(gstr, err);
      std::cout<<"fb group: "<<group["id"].string_value()<<", privacy: "<<group_detail["privacy"].string_value()<<std::endl;
      if (group_detail["privacy"].string_value()=="OPEN")
      {
        std::string feeds_uri = "https://graph.facebook.com/" + gid + "/feed?" + access_token;
        std::vector<json11::Json> feeds = getVectorByUri(feeds_uri);
        //std::cout<<"---------Group: "<<feeds.size()<<"----------"<<std::endl;
        for (auto &feed : feeds) {
          std::string strtime = ISO8601toUnixTime(feed["created_time"].string_value());
          int unixtime;
          std::istringstream(strtime)>> unixtime;

          //std::cout<<"body"<<feed["message"].string_value()<<std::endl;
          //std::cout<<"author"<<feed["from"]["name"].string_value()<<std::endl;
          //std::cout<<"timestamp"<<strtime<<std::endl;

          std::stringstream title_ss(feed["message"].string_value());
          std::string title;
          std::getline(title_ss,title);

          //std::cout<<"title"<<title<<std::endl;
          //std::cout<<"link"<<feed["link"].string_value()<<std::endl;
          //std::cout<<"board"<<group_detail["name"].string_value()<<std::endl;
          //std::cout<<"num_comments"<<std::to_string(feed["comments"]["data"].array_items().size())<<std::endl;
          //std::cout<<"id"<<feed["id"].string_value()<<std::endl;
          //std::cout<<"num_likes"<<std::to_string(feed["likes"]["data"].array_items().size())<<std::endl;

          //db insert
          if(unixtime>1404172800 && unixtime<1430956800){
            bsoncxx::builder::stream::document document{};
            document<<"body"<<feed["message"].string_value();
            document<<"author"<<feed["from"]["name"].string_value();
            document<<"timestamp"<<strtime;
            document<<"title"<<title;
            document<<"link"<<feed["link"].string_value();
            document<<"board"<<group_detail["name"].string_value();
            document<<"num_comments"<<std::to_string(feed["comments"]["data"].array_items().size());
            document<<"id"<<feed["id"].string_value();
            document<<"num_likes"<<std::to_string(feed["likes"]["data"].array_items().size());
            collection.insert_one(document.view());
          }
        }
      }
    }

    //auto cursor = collection.find({});
    //for (auto&& doc : cursor) {
    //    std::cout << bsoncxx::to_json(doc) << std::endl;
    //}

    return 0;
}

std::string getStringByUri(std::string uri){
    std::stringstream buffer;
    curl_writer writer(buffer);
    curl_easy easy(writer);
    
    easy.add<CURLOPT_URL>(uri.c_str());
    easy.add<CURLOPT_USERAGENT>("Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/35.0.1916.153 Safari/537.36");
    easy.add(curl_pair<CURLoption,bool>(CURLOPT_SSL_VERIFYPEER,true));
    easy.add<CURLOPT_FOLLOWLOCATION>(1L);
    
    try {
        easy.perform();
        std::string value;
        value=buffer.str();
        return value;
    }
    catch (curl_easy_exception error) {
        // If you want to get the entire error stack we can do:
        auto errors = error.what();
        // Otherwise we could print the stack like this:
        error.print_traceback();
        // Note that the printing the stack will erase it
    }

  return std::string("error");
}

std::vector<json11::Json> getVectorByUri(std::string uri){
  std::vector<json11::Json> pre;
  std::vector<json11::Json> cur;
  std::string group_list;
  std::string err;
  std::string query = uri;
  int i=0;
  do{

    group_list=getStringByUri(query);
    auto json = json11::Json::parse(group_list, err);

    if (!err.empty()) {
      printf("Failed: %s\n", err.c_str());
      break;
    }

    if (i!=0)
    {
      cur = json["data"].array_items();
      cur.insert(cur.begin(), pre.begin(), pre.end());;
      
      pre = cur;
    }
    else pre = json["data"].array_items();

    query = json["paging"]["next"].string_value();

    i++;
  }
  while(query!="");

  return cur;
}

std::string ISO8601toUnixTime(std::string datetime)
{
  struct tm tm;
  strptime(datetime.c_str(), "%FT%T%z", &tm);
  time_t t = mktime(&tm);
  std::string timestamp = std::to_string(t);
  return timestamp;
}
