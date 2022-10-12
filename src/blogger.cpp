#include <blogger.hpp>

// dfthomework3
void blogger::addpost(eosio::name user, std::string content){
    deal_table table(_self, _self.value);
    deal tmp_post(table.available_primary_key(), user, content);
    table.emplace(_self, [&](auto & entry) { 
        entry = tmp_post; 
    })
}
void blogger::deletepost(uint64_t id, eosio::name user){
    require_auth(_self);
    deal_table table(_self, _self.value);
    auto itr = table.find(id);
    eosio::check(itr != table.end(), "A post does not exist with this ID");
    eosio::check(has_auth(itr->get_user()) || has_auth(_self), "Missing authority to cancel this deal");
    table.erase(itr);
}
void blogger::ratepost(uint64_t id, eosio::name user, int rating){
    require_auth(_self);
    deal_table table(_self, _self.value);
}
void blogger::on_transfer(eosio::name from, eosio::name to, eosio::asset quantity, std::string memo){
}
