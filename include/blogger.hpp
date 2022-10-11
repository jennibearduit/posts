#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>

#include <string>

class [[eosio::contract("blogger")]] blogger : public eosio::contract {
   public:
      using eosio::contract::contract;

      [[eosio::action]] void addpost(eosio::name user, std::string post);
      [[eosio::action]] void deletepost(uint64_t id, eosio::name user); // User here is the post creator, needed for require_auth
      [[eosio::action]] void ratepost(uint64_t id, eosio::name user, int rating); // User here is the person rating the post, needed for require_auth and table
      [[eosio::on_notify("*::transfer")]] void on_transfer(eosio::name from, eosio::name to, eosio::asset quantity, std::string memo);
};
