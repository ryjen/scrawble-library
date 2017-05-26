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
        player& push(const tile& tile);

        tile replace(size_t index, const tile& tile);

        player& pop(const tile& tile);

        tile pop(size_t index);

        tile get(size_t index);

        player& shuffle();

        const rack& get_rack() const;

        player& clear();

       private:
        rack rack_;
        int score_;
        std::string name_;
        int id_;
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
