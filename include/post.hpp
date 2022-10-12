#ifndef POST
#define POST

#include <string>

class [[eosio::table, eosio::contract("blogger")]] post {
  private:
    uint64_t post_id;
    eosio::name user;
    std::string content;

    uint64_t primary_key() const {return post_id;}
    eosio::name get_user() const {return user;}
    std::string get_contet() const {return content;}

    EOSLIB_SERIALIZE(post, (post_id)(user)(content));
};

typedef eosio::multi_index< "post"_n, post > post_table;

#endif
