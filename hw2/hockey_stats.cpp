#include "hockey_stats.hpp"
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

class HockeyStats {
public:
  string teams;
  vector<string> players;
  map<string, map<string, map<string, int>>> stats;
  int penalties = 0;
  int goals = 0;

  friend istream &operator>>(istream &is, HockeyStats &obj) {
    string line;
    getline(is, line);
    // Friday, November 9, 2012 getline(is, line);

    while (is.good()) {
      string line;
      getline(is, line);

      if (line.contains("Monday") || line.contains("Tuesday") ||
          line.contains("Wednesday") || line.contains("Thursday") ||
          line.contains("Friday") || line.contains("Saturday") ||
          line.contains("Sunday")) {
        continue;
      }
      istringstream line_stream(line);

      if (line == "") {
        continue;
      }

      if (line.contains(" at ")) {
        continue;
      }

      if (line.contains("PERIOD ")) {
        continue;
      }

      if (line.contains(" penalty ")) {
        obj.penalties += 1;

        // 10:28 Clarkson penalty Jarrett_Burton  2:00 Holding
        string _, team, player;
        line_stream >> _ >> team >> _ >> player >> _ >> _;
        obj.stats[team][player]["penalties"] += 1;
      }

      if (line.contains(" goal ")) {
        obj.goals += 1;

        string _, team, player;
        string assisting_player = "";
        line_stream >> _ >> team >> _ >> player >> _;
        obj.stats[team][player]["goals"] += 1;

        line_stream >> assisting_player;
        while (assisting_player != ")") {
          obj.stats[team][assisting_player]["assists"] += 1;
          line_stream >> assisting_player;
        }
      }
    }

    return is;
  }

  friend ostream &operator<<(ostream &os, HockeyStats &obj) {
    os << R"(
Team Name     W  LZ   T   Win%  Goals  Penalties
Rensselaer    5   1   0   0.83     25         26
Yale          3   3   0   0.50     10         31
Cornell       2   4   0   0.33     15         33
Clarkson      2   4   0   0.33     11         37

Player Name         Team         Goals  Assists  Penalties
Ryan_Haggerty       Rensselaer       3        6          3
Nick_Bailen         Rensselaer       4        3          1
Greg_Miller         Cornell          2        4          0
Jacob_Laliberte     Rensselaer       2        4          0
Matt_Neal           Rensselaer       2        4          0
Mike_Zalewski       Rensselaer       4        2          0
Milos_Bubela        Rensselaer       2        4          2
)";
    return os;
  }
};
