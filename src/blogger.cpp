#include <blogger.hpp>

void blogger::addpost(eosio::name user, std::string post){
    post_table table(_self, _self.value);
    class post tmp_post(table.available_primary_key(), user, post);
    table.emplace(_self, [&](auto & entry) { 
        entry = tmp_post; 
    });
}

void blogger::deletepost(uint64_t id, eosio::name user){
    require_auth(_self);
    post_table table(_self, _self.value);
    auto itr = table.find(id);
    eosio::check(itr != table.end(), "A post does not exist with this ID");
    eosio::check(itr->get_user() == user, "Missing authority to delete this post");
    table.erase(itr);
}

void blogger::ratepost(uint64_t id, eosio::name user, int rating){
    require_auth(_self);
    rating_table table(user, user.value);
    auto itr = table.begin();
    while (itr != table.end()) {
        eosio::check(itr->get_post_id() != id, "There is already an existing rating for this post by user");
        ++ itr;
    }
    itr = table.begin();
    while (itr != table.end()) {
            if (itr->primary_key() == id) break;
            ++ itr;
    }
    eosio::check(itr != table.end(), "The post does not exist");
    eosio::check(rating >= 1 && rating <= 5, "Rating must be an integer between 1 to 5");
    class rating tmp_rating(table.available_primary_key(), id, user, rating);
    table.emplace(_self, [&](auto & entry) {
        entry = tmp_rating;
    });
    require_recipient(itr->get_user());
}

void blogger::on_transfer(eosio::name from, eosio::name to, eosio::asset quantity, std::string memo){
    if(to != _self) return;
    uint64_t id = stoi(memo);
    post_table table(_self, _self.value);
    auto itr = table.find(id);
    eosio::check(itr != table.end(), "A post does not exist with this ID");
    eosio::check(itr->get_user() == from, "Missing authority to transfer this post");
    table.modify(itr, _self, [&](auto & entry){
        entry.set_user(to);
    });
}
