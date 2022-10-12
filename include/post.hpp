#ifndef POST
#define POST

#include <string>

class [[eosio::table, eosio::contract("blogger")]] post {
  private:
    uint64_t post_id;
    eosio::name user;
    std::string content;

 public:
    uint64_t primary_key() const {return post_id;}
    eosio::name get_user() const {return user;}
    std::string get_content() const {return content;}

    void set_post_id(uint64_t x) {post_id = x;}
    void set_user(eosio::name x) {user = x;}
    void set_content(std::string x) {content = x;}

    post(){}
    post(uint64_t _post_id, eosio::name _user, std::string _content) {
      post_id = _post_id;
      user = _user;
      content = _content;
    }

    EOSLIB_SERIALIZE(post, (post_id)(user)(content));
};

typedef eosio::multi_index< "post"_n, post > post_table;

#endif
