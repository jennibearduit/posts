#ifndef RATING
#define RATING

class [[eosio::table, eosio::contract("blogger")]] rating {
  private:
    uint64_t rating_id;
    uint64_t post_id;
    eosio::name user;
    int score;

  public:
    uint64_t primary_key() const {return rating_id;}
    uint64_t get_post_id() const {return post_id;}
    eosio::name get_user() const {return user;}
    int get_score() const{return score;}

    void set_rating_id(uint64_t x) {rating_id = x;}
    void set_post_id(uint64_t x) {post_id = x;}
    void set_user(eosio::name x) {user = x;}
    void set_score(int x) {score = x;}

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
