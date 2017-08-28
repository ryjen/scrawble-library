#include <bandit/bandit.h>
#include <fcntl.h>
#include <scrawble/core/gaddag.h>
#include <scrawble/core/node.h>
#include <scrawble/core/trie.h>
#include <scrawble/core/trie_factory.h>
#include <scrawble/game_logic.h>
#include <util/file_reader.h>
#include <queue>

using namespace bandit;

class TestConfig : public scrawble::Config
{
   public:
    constexpr static const char *ASSET_FOLDER = "tests/assets/";

    void load(const std::string &filepath)
    {
        FileReader input(filepath);

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

class TestGame : public scrawble::GameLogic
{
    std::shared_ptr<scrawble::Gaddag> dictionary_;

   public:
    void init_dictionary(const std::string &fileName)
    {
        scrawble::FileBasedTrieFactory factory(TestConfig::ASSET_FOLDER + fileName);

        dictionary_ = std::make_shared<scrawble::Gaddag>(factory);
    }

    std::set<std::string> hints() const
    {
        auto moves = dictionary_->calculateHighestScorePlacement(board(), player().rack());
        std::string buf;
        for (auto &move : moves) {
            buf += move.letter();
        }
        std::set<std::string> rval;
        rval.insert(buf);
        return rval;
    }

    void set_player_rack(const std::initializer_list<char> &list)
    {
        for (auto ch : list) {
            player().rack().push(bag().next(ch));
        }
    }
};

go_bandit([]() {

    std::shared_ptr<TestGame> game;

    before_each([&game]() {

        TestConfig config;

        config.load();

        game = std::make_shared<TestGame>();

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
