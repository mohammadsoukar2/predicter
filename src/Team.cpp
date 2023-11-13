#include "Team.h"
//
//  Team.cpp
//  Final project
//
//  Created by Apple on 05/11/2023.
//


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

class Team{
private:
    std::string teamName;
    int score;

public:
    Team(const std::string& name) : teamName(name), score(0) {}

    std::string getTeamName() const {
        return teamName;
    }
    //method that returns the team's score.
    int getScore() const {
        return score;
    }
//increment the team's score by 1.
    void incrementScore() {
        ++score;
    }
};
