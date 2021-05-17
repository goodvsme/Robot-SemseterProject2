#include "controller.h"

Controller::Controller()
{

}


vector<QString> Controller::setup(int testin){
    vector<QString> s;
    robots = d.getRobots();
    gripperports = d.getGrippers();

    //test_id = ui->spinBox->value();
    test_id = testin;


    for(unsigned long i = 0; i<gripperports.size();i++){
        gripper g;
        grippers.push_back(g);
        grippers[i].setAddress(gripperports[i]);
    }
    for(unsigned long i = 0; i<robots.size();i++){
        robots[i].modbusConnect();
        robots[i].setFinished(0);
        robots[i].modbusUpdateCoords();

    }

    for(unsigned long i = 0; i<robots.size();i++){
        s.push_back(QString::fromStdString(robots[i].robotName));
        //ui->comboBox->addItem(QString::fromStdString(robots[i].robotName));
    }
return s;


}


void Controller::dataUpdate()
{

    for(unsigned long i = 0; i<robots.size();i++){
        if(robots[i].connected){

            if(robots[i].runn[0]==1){

                if(toggle){
                    string s=to_string(robots[i].directions[0]+1);
                    unsigned char c[1];
                    strcpy( (char*) c, s.c_str());
                    grippers[i].sendmsg(c[0]);
                    toggle = 0;
                }

                bool r = grippers[i].readSerial(&d, test_id, i);

                if(r){
                    robots[i].setFinished(1);
                    robots[i].modbusUpdateCoords();
                    sleep(1);
                    robots[i].setFinished(0);
                    robots[i].modbusUpdateCoords();
                    toggle = 1;
                }
            }else{
                grippers[i].readSerial(&d, test_id, i);
            }

        }else{
            grippers[i].readSerial(&d, test_id, i);
        }

        robots[i].modbusUpdateCoords();
    }

}

float Controller::getAngle(int index)
{
    return grippers[index].angle;
}

void Controller::drive(int index, char dir)
{
    if(dir=='0'){
        grippers[index].sendmsg('0');
        robots[index].setFinished(1);
        robots[index].modbusUpdateCoords();
        sleep(1);
        robots[index].setFinished(0);
        robots[index].modbusUpdateCoords();
        toggle = 1;
    }else{
        grippers[index].sendmsg(dir);
    }
}

void Controller::calibrategripper(int index)
{
    grippers[index].calibrate();
}

void Controller::setTestID(int id)
{
    test_id = id;
}

QString Controller::getIp(int index)
{
    return QString::fromStdString(robots[index].tcpUR5IP);
}

QString Controller::getComport(int index)
{
    return QString::fromStdString(grippers[index].portCOM);
}

float Controller::getAmp(int index)
{
    return grippers[index].avg_amp;
}

array<float,6> Controller::getCords(int index)
{
    return robots[index].TCP_Coords;
}
