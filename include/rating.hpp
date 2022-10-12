#ifndef RATING
#define RATING

class [[eosio::table, eosio::contract("blogger")]] rating {
  private:
    uint64_t rating_id;
    uint64_t post_id;
    eosio::name user;
    int score;

    uint64_t primary_key() const {return rating_id;}

    EOSLIB_SERIALIZE(rating, (rating_id)(post_id)(user)(score));
};

typedef eosio::multi_index< "rating"_n, rating > rating_table;

#endif
