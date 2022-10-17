#ifndef RATING
#define RATING

class [[eosio::table, eosio::contract("blogger")]] rating {
  public:
    uint64_t rating_id;
    uint64_t post_id;
    eosio::name user;
    int score;

    uint64_t primary_key() const {return rating_id;}

    rating(){}
    rating(uint64_t _rating_id, uint64_t _post_id, eosio::name _user, int _score) {
        rating_id = _rating_id;
        post_id = _post_id;
        user = _user;
        score = _score;
    }

    EOSLIB_SERIALIZE(rating, (rating_id)(post_id)(user)(score));
};

typedef eosio::multi_index< "rating"_n, rating > rating_table;

#endif