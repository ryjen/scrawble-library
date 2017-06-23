#ifndef SCRAWBLE_PLAYER_H
#define SCRAWBLE_PLAYER_H

#include <scrawble/rack.h>
#include <scrawble/tile.h>
#include <string>
#include <vector>

namespace scrawble
{
    class Player
    {
       public:
        Player();

        const Rack &rack() const;

        Rack &rack();

        Player &add_score(int score);

        const std::string &name() const;

        const int score() const;

       private:
        Rack rack_;
        int score_;
        std::string name_;
    };

    class Opponent : public Player
    {
       public:
        virtual void play() = 0;
    };

    class ComputerPlayer : public Opponent
    {
       public:
        void play();
    };

    class NetworkPlayer : public Opponent
    {
       public:
        void play();
    };
}

#endif
