#include "main.h"
#include "avoidance.h"

int Avoidance::checkScore()
{
    float distance = detect.ultrasonic();

    if (distance >= greenDistance) //if only the green lED is on...
    {
        score = 4; //give the righ direction a score of 4
    }
    else if (distance < greenDistance and distance >= blueDistance) //if the blue led is on..
    {
        score = 3;
    }
    else if (distance < blueDistance and distance >= YellowDistance) //if the yellow led is on..
    {
        score = 2;
    }
    else
    {
        score = 1;
    }
    return score;
}

void Avoidance::side_state_disturbed(int disturbed_side, int opposite_side)

{
    //this avoidance function is called when then any irsensors on the left / right side of the
    //system is triggered
    // this stragety is designed to be universal
    //view documentation in section .. for strategy follow

    //create pointer
    int opposite_side_state;
    int front_state;
    bool oposite_side_checked_state;

    if (myservo.read() == opposite_side)
    { //if the servo is allready facing opposite side.. just get the reading of score at once..
        Serial.println("Optimised Route used....");
        opposite_side_state = checkScore();
        oposite_side_checked_state = true; //set the state...
        Serial.println("opposite side scores =");
        Serial.print(opposite_side_state);
        myservo.write(90);
        delay(200);
    }

    if (myservo.read() == disturbed_side)
    {                      //if servo is facing left...
        myservo.write(90); //face it foward...
        delay(200);        //wait for it to face foward
    }

    front_state = checkScore(); // check the front and set the state
    Serial.println("front =");
    Serial.println(front_state);

    if (front_state == 4)
    { //if the front is clear..
        Serial.println("SLIGHTLY ROLL OPPOSITE DIRECTION AND CONTINUE FOWARD");
        switch (disturbed_side)
        {
        case left:                              //if disturbed side was left
            myMotor.command_drone_roll_right(); //command the motors to roll right
            delay(2000);
            myMotor.command_drone_hover();
            break;
        case right:
            myMotor.command_drone_roll_left();
            delay(2000);
            myMotor.command_drone_hover();
            break;
        default:
            break;
        }

        return;
    };

    //front  was not clear..

    if (oposite_side_checked_state == true)
    { //if the opposite side had already been checked...
        if (opposite_side_state == 4)
        { //and the opposite side was clear..
            Serial.println("ROLLING OPPOSITE DIRECTION TILL FRONT IS CLEAR..");
            switch (disturbed_side)
            {
            case left:
                while (front_state < 4)
                {
                    myMotor.command_drone_roll_right(); //command the motors to roll right until the front is clear
                    front_state = checkScore();
                }
                myMotor.command_drone_hover();
                break;
            case right:
                while (front_state < 4)
                {
                    myMotor.command_drone_roll_left(); //command the motors to roll right until the front is clear
                    front_state = checkScore();
                }

                myMotor.command_drone_hover();
                break;

            default:
                break;
            }
            return;
        }
    }

    if (oposite_side_checked_state == false)
    {                                 //if opposite side had not been checked..
        myservo.write(opposite_side); //turn the servo to the opposite side
        delay(200);                   //wait..

        opposite_side_state = checkScore();
        Serial.println("opposite side =");
        Serial.print(opposite_side_state);
    }

    if (opposite_side_state != 4)
    {
        Serial.println("DRONE STOPPED!");
        myMotor.command_drone_decend();
        delay(5000);
        myMotor.command_drone_hover();
        return;
    }
    if (opposite_side == 4)
    {                      //if opposite side is clear..
        myservo.write(90); //face servo to the front...
        delay(200);
        Serial.println("ROLLING OPPOSITE DIRECTION TILL FRONT IS CLEAR..");
        switch (disturbed_side)
        {
        case left:
            while (front_state < 4)
            {
                myMotor.command_drone_roll_right(); //command the motors to roll right until the front is clear
                front_state = checkScore();
            }
            myMotor.command_drone_hover();
            break;
        case right:
            while (front_state < 4)
            {
                myMotor.command_drone_roll_left(); //command the motors to roll right until the front is clear
                front_state = checkScore();
            }

            myMotor.command_drone_hover();
            break;

        default:
            break;
        }
        return;
    }
}

void Avoidance::back_state_disturbed()
{
    //this evation strategy is exicuted the the back state of the drone is disturbed

    //constructor.......
    int front_state;
    int left_side_state = 0;  //30
    int right_side_state = 0; //150

    //Main...........

    if (myservo.read() == left)
    {                                    //if servo is allready facing right
        right_side_state = checkScore(); //set state..
        if (right_side_state == 4)
        { //if the right side is clear...
            Serial.println("Right Side is clear...");
            Serial.println("ROLL RIGHT");
            myMotor.command_drone_roll_right();
            delay(2000);
            myMotor.command_drone_hover();
            return;
        }                  //else
        myservo.write(90); //face it foward...
        delay(200);        //wait....
    }

    if (myservo.read() == right)
    {                                   //if servo is allready facing left
        left_side_state = checkScore(); //set state..
        if (left_side_state == 4)
        { //if the right side is clear...
            Serial.println("Left Side is clear...");
            Serial.println("ROLLING  LEFT....");
            myMotor.command_drone_roll_left();
            delay(2000);
            myMotor.command_drone_hover();
            return;
        }                  //else
        myservo.write(90); //face it foward...
        delay(200);        //wait...
    }

    front_state = checkScore(); //set state..

    //set the state for any side that hasnt been checked..
    if (left_side_state == 0)
    {                                    //if the left state hasnt been checked
        myservo.write(right);            //turn the servo left
        delay(200);                      //wait
        left_side_state == checkScore(); //check state
        if (left_side_state == 4)
        {
            Serial.println("Left is clear..");
            Serial.println("ROLLING LEFT....");
            myMotor.command_drone_roll_left();
            delay(2000);
            myMotor.command_drone_hover();
            return;
        } //else
    }

    if (right_side_state == 0)
    {                                     //if the left state hasnt been checked
        myservo.write(left);              //turn the servo left
        delay(200);                       //wait
        right_side_state == checkScore(); //check state
        if (right_side_state == 4)
        {
            Serial.println("Right is clear..");
            Serial.println("Rolling Right...");
            myMotor.command_drone_roll_right();
            delay(2000);
            myMotor.command_drone_hover();
            return;
        } //else
    }

    //check if both sides are blocked..
    if (right_side_state < 3 && left_side_state < 3 && front_state < 3)
    {

        Serial.println("All sides blocked..");
        Serial.println("Vertical Movements only allowed");
        Serial.println("Gainning Altitute...");
        myMotor.command_drone_climb();
        delay(2000);
        myMotor.command_drone_hover();
        return;
    }

    if (right_side_state < 3 && left_side_state < 3)
    {

        Serial.println("Both sides blocked..");
        Serial.println(" foward or Vertical Movements only allows");
        Serial.println("Moving Foward...");
        myMotor.command_drone_foward();
        delay(2000);
        return;
    }

    //both sides are clear=3 so
    if (right_side_state > left_side_state)
    {
        Serial.println("ROLLING RIGHT...");
        myMotor.command_drone_roll_right();
        delay(2000);
        myMotor.command_drone_hover();
        return;
    }
    else if (right_side_state < left_side_state)
    {
        Serial.println("ROLLING LEFT...");
        myMotor.command_drone_roll_left();
        delay(2000);
        myMotor.command_drone_hover();
        return;
    }
}

void Avoidance::avoidance()
{

    int statusSensor1 = digitalRead(IRSensor1);
    int statusSensor2 = digitalRead(IRSensor2);
    int statusSensor3 = digitalRead(IRSensor3);
    int statusSensor4 = digitalRead(IRSensor4);
    int statusSensor5 = digitalRead(IRSensor5);
    int statusSensor6 = digitalRead(IRSensor6);
    int statusSensor7 = digitalRead(IRSensor7);
    //this fuction will execute the appropriate avoidance strategy

    if (statusSensor5 == 0)
    {

        side_state_disturbed(right, left);
        return;
    }

    // if (statusSensor7 == 0 || statusSensor3 == 0)
    // {
    //     // side_state_disturbed(left, right);
    //     Serial.println("true2");
    //     //return;
    // }

    if (statusSensor4 == 0)
    {

        back_state_disturbed();
        return;
    }

    else
    {
        detect.orientation(); //allways faces the Ultrasonic sensor to the direction of motion. it uses data from the imu
                              // delta_v();//
    }
}
