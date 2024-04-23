#pragma once
#include <string>
#include <algorithm>
#include <fstream>
struct Score {
    int scoreInt = 0;
    char score[32];
    char highscore[32];
    int highscoreInt = LoadHighScore();
    int bestscore[5];
    int num = 5;




    bool is_empty(std::ifstream& pFile)
    {
        return pFile.peek() == std::ifstream::traits_type::eof();
    }

    int LoadHighScore()
    {
        std::ifstream input("Score.txt", std::ios::app);
        int s;
        if (is_empty(input))
        {
            s = 0;
            std::cout << "ERROR" << std::endl;
            sprintf_s(highscore, "BEST: %d", highscoreInt);
        }
        else
        {
            sprintf_s(highscore, "BEST: %d", highscoreInt);
            input >> s;
            input.close();
        }
        return s;
    }


    void SaveHighScore() {
        std::ofstream output("Score.txt");
        output << highscoreInt;
        output.close();
    }

    void addScore(int amount)
    {
        scoreInt += amount;
        if (scoreInt < 10) {
            sprintf_s(score, "00%d", scoreInt);
        }
        else if (scoreInt < 100)
        {
            sprintf_s(score, "0%d", scoreInt);
        }
        else
        {
            sprintf_s(score, "%d", scoreInt);
        }
        if (scoreInt > highscoreInt) {
            highscoreInt = scoreInt;
            sprintf_s(highscore, "BEST: %d", highscoreInt);
            SaveHighScore();
        }
    }

    void resetScore() {
        scoreInt = 0;
        sprintf_s(score, "00%d", scoreInt);

    }

};