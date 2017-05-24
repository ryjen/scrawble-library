#include <bandit/bandit.h>
#include <fcntl.h>
#include <scrawble/game_logic.h>
#include <util/file_reader.h>
#include <queue>

using namespace bandit;

class test_generator : public scrawble::bag::generator_type
{
   public:
    void letters(const std::initializer_list<char> &value)
    {
        for (auto letter : value) {
            specified_.push(letter);
        }
    }
    int next(const scrawble::bag::list_type &letters)
    {
        if (specified_.empty()) {
            throw std::out_of_range("no more specified letters");
        }

        auto next = specified_.front();
        specified_.pop();
        auto it = std::find(std::begin(letters), std::end(letters), next);
        if (it == letters.end()) {
            throw std::out_of_range("specified letter not found");
        }

        return std::distance(std::begin(letters), it);
    }

   private:
    std::queue<char> specified_;
};

class test_config : public scrawble::config
{
   public:
    constexpr static const char *ASSET_FOLDER = "tests/assets/";

    void load(const std::string &filepath)
    {
        file_reader input(filepath);

        nlohmann::json j = input.to_json();

        dictionary_ = j["dictionary"];

        auto tiles = j["tiles"];

        for (auto tile : tiles) {
            int score = tile["score"];

            auto distributions = tile["letter_distributions"];

            for (auto it = distributions.begin(); it != distributions.end(); ++it) {
                letters_.emplace_back(score, it.value(), it.key()[0]);
            }
        }
    }

    void load()
    {
        load(std::string(ASSET_FOLDER) + "english.json");
    }
};

class test_game : public scrawble::game_logic
{
   public:
    void init_dictionary(const std::string &fileName)
    {
        file_reader reader(test_config::ASSET_FOLDER + fileName);

        for (auto line : reader) {
            dictionary_.push(line);
        }
    }
};

go_bandit([]() {

    std::shared_ptr<test_game> game;

    test_generator generator;

    before_each([&game]() {

        test_config config;

        config.load();

        game = std::make_shared<test_game>();

        game->init(config);
    });

    describe("scrawble", [&game, &generator]() {

        it("can find the best move", [&game, &generator]() {
            generator.letters({'C', 'O', 'W', 'Z', 'A', 'D', 'R'});

            std::set<scrawble::lexicon::move> pool;

            game->search(scrawble::board::size / 2, scrawble::board::size / 2, game->get_player().rack(), pool);

            Assert::That(3, Equals(pool.size()));
        });

    });

});