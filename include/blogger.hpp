#include <eosio/eosio.hpp>

#include <string>

class [[eosio::contract("blogger")]] blogger : public eosio::contract {
   public:
      using eosio::contract::contract;

      [[eosio::action]] void addpost(eosio::name user, std::string post);
};
