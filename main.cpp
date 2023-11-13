#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>



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

        std::vector<Team> teamsCopy = teams;
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



bool removeTeamFromFile(const std::string& filename, const std::string& teamNameToRemove) {
    std::ifstream inFile(filename);
    std::ofstream outFile("temp.txt"); // Create a temporary file

    if (!inFile.is_open() || !outFile.is_open()) {
        return false; // Error opening files
    }

    std::string line;
    bool teamRemoved = false;

    while (std::getline(inFile, line)) {
        if (line != teamNameToRemove) {
            outFile << line << "\n";
        } else {
            teamRemoved = true;
        }
    }

    inFile.close();
    outFile.close();

    if (teamRemoved) {
        std::remove(filename.c_str());       // Delete the original file
        std::rename("temp.txt", filename.c_str()); // Rename the temporary file
    } else {
        std::remove("temp.txt"); // Remove the temporary file
    }

    return teamRemoved;
}


bool isAdminLoggedIn() {
    int choose;
    std::cout << "--------------------------------------------\n";
    std::cout << "     Welcome to the Pizza Olympics & Sports   \n";
    std::cout << "--------------------------------------------\n";
    std::cout << "            Competition & Pizza               \n";
    std::cout << "--------------------------------------------\n";
    std::cout << "   🍕🏆 Choose your role: 🏆🍕\n";
    std::cout << "1) Pizza Chef (Admin)\n";
    std::cout << "2) Pizza Lover (Participant)\n";
    std::cout << "--------------------------------------------\n";
    std::cout << "Enter '1' to become a Pizza Chef: ";

    std::cin >> choose;

    if (choose == 1) {
        std::cout << "Admin login successful. Welcome, Admin!\n";
    } else {
        std::cout << "Participant login selected. Welcome, Pizza Lover!\n";
    }

    return (choose == 1);
}


void displayUserMenu() {
    std::cout << "User Menu:\n";
    std::cout << "1. Predict quarter-finalists\n";
    std::cout << "2. Predict semi-finalists\n";
    std::cout << "3. Predict the final winner\n";
    std::cout << "4. Exit\n";
    std::cout << "Enter your choice: ";
}

void displayAdminMenu() {
    std::cout << "Admin Menu:\n";
    std::cout << "1. List of the teams in the competition\n";
    std::cout << "2. Add team\n";
    std::cout << "3. remove team\n";
    std::cout << "4. Exit\n";
    std::cout << "Enter your choice: ";
}

void addTeam(Competition& competition) {
    std::string teamName;
    std::cout << "Enter team name: ";
    std::cin.ignore();
    std::getline(std::cin, teamName);
    Team team(teamName);
    competition.addTeam(team);
    std::cout << "Team added successfully!\n";
};


void loadTeamsFromFile(Competition &competition){
    // Read the list of teams from a text file
    std::ifstream inputFile("CppProject/teams.txt");
    if (!inputFile) {
        std::cout << "Failed to open teams.txt" << std::endl;
            return 1;
    }

    std::string teamName;
    while (std::getline(inputFile, teamName)) {
        // Create a team and add it to the competition
        Team team(teamName);
        competition.addTeam(team);
    }


}


int main() {
    Competition competition;  // Create a competition instance.


    if (!loadTeamsFromFile(competition)) {
        return 1;
    }


    // Check if an admin is logged in. You can add more logic for user vs. admin roles.
    bool isAdmin = isAdminLoggedIn();

    while (true) {
        try {
            if (isAdmin) {
                displayAdminMenu();  // Display the admin menu.
                int choice;
                std::cin >> choice;

                switch (choice) {
                    case 1:  //display list of

    std::cout << "List of teams in the competition:\n";
    for (const auto& team : competition.getTeams()) {
        std::cout << team.getName() << "\n";
                                                }

                        break;
                    case 2:
                        addTeam(competition);

                        break;
                    case 3:
       // Remove team --> have a for loop and compare the names of team to the name you want to remove and if it matches get the index of that team and then remove it from the teams vector.
                    break;
                    case 4:
                        break;


                    default:
                        std::cout << "Invalid choice. Please try again." << std::endl;
                }
            } else {
                displayUserMenu();  // Display the user menu.
                int choice;
                std::cin >> choice;

                switch (choice) {
                    case 1:  // Predict quarter-finalists.
                        std::vector<Team> quarterFinalists = competition.predictQuarterFinalists();
                        // Display or work with the quarter-finalists.
                        break;
                    case 2:  // Predict semi-finalists.
                        std::vector<Team> quarterFinalists = competition.predictQuarterFinalists();
                        std::vector<Team> semiFinalists = competition.predictSemiFinalists(quarterFinalists);
                        // Display or work with the semi-finalists.
                        break;
                    case 3:  // Predict the final winner.
                        std::vector<Team> quarterFinalists = competition.predictQuarterFinalists();
                        std::vector<Team> semiFinalists = competition.predictSemiFinalists(quarterFinalists);
                        std::string winner = competition.predictWinner(semiFinalists);
                        // Display or work with the winner.
                        break;
                    case 4:  // Exit.
                        break;
                    default:
                        std::cout << "Invalid choice. Please try again." << std::endl;
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}

