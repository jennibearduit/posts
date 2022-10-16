#include <blogger.hpp>

void blogger::addpost(eosio::name user, std::string content){
    post_table table(_self, _self.value);
    post tmp_post(table.available_primary_key(), user, content);
    table.emplace(_self, [&](auto & entry) { 
        entry = tmp_post; 
    });
}
void blogger::deletepost(uint64_t id, eosio::name user){
    require_auth(_self); // only post creator can delete
    post_table table(_self, _self.value);
    auto itr = table.find(id);
    eosio::check(itr != table.end(), "A post does not exist with this ID");
    eosio::check(has_auth(itr->get_user()) || has_auth(_self), "Missing authority to delete this post");
    table.erase(itr);
}

void blogger::ratepost(uint64_t id, eosio::name user, int rating_score){
    require_auth(_self);
    rating_table table(_self, _self.value);
    rating tmp_rating(table.available_primary_key(), id, user, rating_score);
    auto itr = table.find(id); // find if there's existing rating for the post id
    eosio::check(itr == table.end(), "There is already an existing rating for this post");
    eosio::check(rating_score >= 1 && rating_score <= 5, "Rating must be an integer between 1 to 5");
    table.emplace(_self, [&](auto & entry) {
        entry = tmp_rating;
    });
    require_recipient(user);
}
void blogger::on_transfer(eosio::name from, eosio::name to, eosio::asset quantity, std::string memo){
}
