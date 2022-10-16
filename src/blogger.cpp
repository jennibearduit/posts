#include <blogger.hpp>

void blogger::addpost(eosio::name user, std::string post_content){
    post_table table(_self, _self.value);
    post tmp_post(table.available_primary_key(), user, post_content);
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

void blogger::ratepost(uint64_t id, eosio::name user, int rating_score){
    require_auth(_self);
    rating_table table(user, user.value);
    auto itr = table.begin();
    while (itr != table.end()) {
        eosio::check(itr->get_post_id() != id, "There is already an existing rating for this post by user");
        ++ itr;
    }
    eosio::check(rating_score >= 1 && rating_score <= 5, "Rating must be an integer between 1 to 5");
    rating tmp_rating(table.available_primary_key(), id, user, rating_score);
    table.emplace(_self, [&](auto & entry) {
        entry = tmp_rating;
    });
    // TODO: inform post creator
}

void blogger::on_transfer(eosio::name from, eosio::name to, eosio::asset quantity, std::string memo){

}
