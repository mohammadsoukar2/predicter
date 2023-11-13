#include "Competition.h"
//
//  Competition.cpp
//  Final project
//
//  Created by Apple on 05/11/2023.

#include <iostream>
#include "Team.h"
#include <vector>
#include <fstream>
#include <algorithm>

class Competition {
private:
    std::vector<Team> teams; //represents the collection of teams in the competition. These teams are stored in this vector.

public:
    //allows you to add a Team object to the teams vector. It takes a const Team& parameter, which is the team to be added to the competition.
    const std::vector <Team>& getTeams()const{
        return teams;
    }
    void addTeam(const Team& team) {
        //open file team read
        std::ifstream inputFile("teams.txt");
        inputFile.open("teams.txt");
        if (inputFile.is_open()) {
            std::string line;

            std::string teamName;
            while (std::getline(inputFile, teamName)) {
                Team newTeam(teamName);
                // Competition.addTeam(newTeam);
                teams.push_back(newTeam);
            }
            inputFile.close();
        }
        else {
            std::cerr << "Failed to open 'teams.txt' for reading." << std::endl;


        }
    }
    std::vector<Team> predictQuarterFinalists() const {
        std::vector<Team> quarterFinalists;
        // Team highestScore =teams[0];
        // for (size_t i = 0; i < 4 ; ++i) {

        std::vector<Team> teamsCopy{4} = teams;
 std::sort(teamsCopy.begin(), teamsCopy.end(), [](const Team& a, const Team& b) {
            return a.getScore() > b.getScore();
        });
        //push
        // Add the top 4 teams to the quarterFinalists vector.
        for (size_t i = 0; i < 4; ++i) {
            quarterFinalists.push_back(teamsCopy[i]);
        }
        return quarterFinalists;
    }


    std::vector<Team> predictSemiFinalists(const std::vector<Team>& quarterFinalists) const {
        std::vector<Team> semiFinalists;
        std::vector<Team> sortedQuarterFinalists = quarterFinalists;

          // Sort the quarterFinalists by score in descending order.
          std::sort(sortedQuarterFinalists.begin(), sortedQuarterFinalists.end(), [](const Team& a, const Team& b) {
              return a.getScore() > b.getScore();
          });

          // Add the top 2 teams from the sorted quarterFinalists vector to the semiFinalists vector.
          for (size_t i = 0; i < 2; ++i) {
              semiFinalists.push_back(sortedQuarterFinalists[i]);
          }

          return semiFinalists;
      }


    std::string predictWinner(const std::vector<Team>& semiFinalists) const {

        const Team* winner = &semiFinalists[0];

            for (size_t i = 1; i < semiFinalists.size(); ++i) {
                const Team& currentTeam = semiFinalists[i];

                if (currentTeam.getScore() > winner->getScore()) {
                    winner = &currentTeam;
                }
            }

            return winner->getTeamName();
        }



};

