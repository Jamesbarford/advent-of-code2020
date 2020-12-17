#include <vector>

#define SHINY_GOLD "shinygold"
#define NO_BAGS "noother"

typedef std::vector<std::string> BagCountCollection;

class BagMap
{

public:
    void insert(std::string key);
    void insert(std::string key, BagCountCollection bags);
    void add(std::string key, std::string bag);
    void add(std::string bag);
    void set_current_key(std::string);
    void unset_current_key();
    void print();
    bool is_empty_value(std::string key);
    bool has(std::string key);
    int get_bag_count(std::string current_bag);
    BagCountCollection at(std::string key);

private:
    std::map<std::string, BagCountCollection> bag_map;
    std::optional<std::string> current_key;
};
