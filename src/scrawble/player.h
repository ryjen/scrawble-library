#ifndef SCRAWBLE_PLAYER_H
#define SCRAWBLE_PLAYER_H

#include <scrawble/rack.h>
#include <scrawble/tile.h>
#include <string>
#include <vector>

namespace scrawble
{
    class player
    {
       public:
        player();

        const scrawble::rack &rack() const;

        scrawble::rack &rack();

        player &add_score(int score);

        const std::string &name() const;

        const int score() const;

       private:
        scrawble::rack rack_;
        int score_;
        std::string name_;
    };

    class opponent : public player
    {
       public:
        virtual void play() = 0;
    };

    class computer_player : public opponent
    {
       public:
        void play();
    };

    class network_player : public opponent
    {
       public:
        void play();
    };
}

#endif
