#ifndef POST
#define POST

#include <string>

class [[eosio::table, eosio::contract("blogger")]] post {
  public:
    uint64_t post_id;
    eosio::name user;
    std::string content;

    uint64_t primary_key() const {return post_id;}

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