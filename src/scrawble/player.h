#ifndef SCRAWBLE_PLAYER_H
#define SCRAWBLE_PLAYER_H

#include <scrawble/tile.h>
#include <string>
#include <vector>

class player
{
   public:
    static const int rack_size = 7;

    void print(std::ostream& out);

    player& push(const tile& tile);

    player& pop(const tile& tile);

   private:
    std::vector<tile> rack_;
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

#endif
