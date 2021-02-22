#pragma once //makes sure the header file is not included more than on in a file

class Avoidance
{
private:
    int score;


private:
    int checkScore();

    void side_state_disturbed(int disturbed_side, int opposite_side);

    void back_state_disturbed();

public:
    void avoidance();
};
