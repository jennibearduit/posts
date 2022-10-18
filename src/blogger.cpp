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
    eosio::check(itr->user == user, "Missing authority to delete this post");
    table.erase(itr);
}

void blogger::ratepost(uint64_t id, eosio::name user, int rating){
    require_auth(_self);
    post_table p_table(_self, _self.value);
    auto p_itr = p_table.find(id);
    eosio::check(p_itr != p_table.end(), "A post does not exist with this ID");
    rating_table r_table(_self, _self.value);
    auto r_itr = r_table.begin();
    while (r_itr != r_table.end()) {
        eosio::check(!(r_itr->post_id == id && r_itr->user == user),
            "There is already an existing rating for this post by user");
        ++ r_itr;
    }
    eosio::check(rating >= 1 && rating <= 5, "Rating must be an integer between 1 to 5");
    class rating tmp_rating(r_table.available_primary_key(), id, user, rating);
    r_table.emplace(_self, [&](auto & entry) {
        entry = tmp_rating;
    });
    require_recipient(p_itr->user);
}

void blogger::on_transfer(eosio::name from, eosio::name to, eosio::asset quantity, std::string memo){
    if (to != _self) return;
    uint64_t id = stoi(memo);
    post_table table(_self, _self.value);
    auto itr = table.find(id);
    eosio::check(itr != table.end(), "The post doesn't exist");
    eosio::action(eosio::permission_level(_self, eosio::name("active")), get_first_receiver(),
        eosio::name("transfer"), std::tuple(_self, itr->user, quantity, std::string("Donation complete"))).send();
}