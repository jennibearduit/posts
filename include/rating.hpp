#ifndef RATING
#define RATING

class [[eosio::table, eosio::contract("blogger")]] rating {
  private:
    uint64_t rating_id;
    uint64_t post_id;
    eosio::name user;
    int score;

    uint64_t primary_key() const {return rating_id;}
    uint64_t get_post_id() const {return post_id;}
    eosio::name get_user() const {return user;}
    int get_score() const {return score;}

    EOSLIB_SERIALIZE(rating, (rating_id)(post_id)(user)(score));
};

typedef eosio::multi_index< "rating"_n, rating > rating_table;

#endif
