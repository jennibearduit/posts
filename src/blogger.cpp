#include <blogger.hpp>

void blogger::addpost(eosio::name user, std::string content){
    deal_table table(_self, _self.value);
    deal tmp_post(table.available_primary_key(), user, content);
    table.emplace(_self, [&](auto & entry) { 
        entry = tmp_post; 
    })
}
void blogger::deletepost(uint64_t id, eosio::name user){
}
void blogger::ratepost(uint64_t id, eosio::name user, int rating){
}
void blogger::on_transfer(eosio::name from, eosio::name to, eosio::asset quantity, std::string memo){
}
