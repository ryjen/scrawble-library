#include <bandit/bandit.h>
#include <fcntl.h>
#include <scrawble/arc.h>
#include <scrawble/gaddag.h>
#include <scrawble/game_logic.h>
#include <util/file_reader.h>
#include <queue>

using namespace bandit;

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
    scrawble::gaddag dictionary_;

   public:
    void init_dictionary(const std::string &fileName)
    {
        file_reader reader(test_config::ASSET_FOLDER + fileName);

        for (auto line : reader) {
            dictionary_.push(line);
        }
    }

    std::set<std::string> hints() const
    {
        return dictionary_.find(player().rack().to_string());
    }

    void set_player_rack(const std::initializer_list<char> &list)
    {
        for (auto ch : list) {
            player().rack().push(bag().next(ch));
        }
    }
};

go_bandit([]() {

    std::shared_ptr<test_game> game;

    before_each([&game]() {

        test_config config;

        config.load();

        game = std::make_shared<test_game>();

        game->init(config);
    });

    describe("scrawble", [&game]() {

        // it("can find the best move", [&game]() {
        //     game->set_player_rack({'C', 'O', 'F', 'Z', 'A', 'D', 'R'});

        //     game->board().place(scrawble::board::size / 2, scrawble::board::size / 2, game->bag().next('W'));

        //     game->board().place(scrawble::board::size / 2, scrawble::board::size / 2 + 1, game->bag().next('E'));

        //     game->search(scrawble::board::size / 2, scrawble::board::size / 2, game->player().rack(), pool);

        //     Assert::That(pool.size(), Equals(2));

        //     std::set<scrawble::lexicon::move, order_by_score> best_move;

        //     best_move.insert(pool.begin(), pool.end());

        //     auto best = *best_move.begin();

        //     Assert::That(best.score(), Equals(6));

        //     Assert::That(best.word(), Equals("WOAD"));
        // });

        it("can find best word", [&game]() {
            game->set_player_rack({'C', 'O', 'F', 'Z', 'A', 'D', 'R'});

            auto hints = game->hints();

            Assert::That(hints.size(), Equals(2));

        });
    });

});
