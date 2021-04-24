#include "database.h"


database::database()
{
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "127.0.0.1", "root", "Emil2000", "ur5Database", 3306, NULL, 0);
}

vector<robotUR5> database::getRobots()
{
    ur5Bots.clear();
    string navn;
    string ip;
    query = "select UR5.navn,UR5.IP from UR5, Orders, Gripper where UR5.robot_id=Orders.robot_id and Orders.gripper_id=Gripper.gripper_id order by UR5.robot_id";
    q = query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {
        res = mysql_store_result(conn);

        while ((row = mysql_fetch_row(res))){
            navn = row[0];
            ip = row[1];

            //inputting the robots in list
            robotUR5 i(navn, ip);
            ur5Bots.push_back(i);

        }
        return ur5Bots;
    }
    else{
        robotUR5 i("NA", "127.0.0.1");
        ur5Bots.push_back(i);

        cout << "Query failed: " << mysql_error(conn) << endl;
        return ur5Bots;
    }

}

bool database::setRobot(int index, string newIP)
{

}

vector<gripper> database::getGrippers()
{
    grippers.clear();
    string port;

    query = "select Gripper.COM_port from UR5, Orders, Gripper where UR5.robot_id=Orders.robot_id and Orders.gripper_id=Gripper.gripper_id order by UR5.robot_id";
    q = query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {
        res = mysql_store_result(conn);

        while ((row = mysql_fetch_row(res))){
            port = row[0];
            //inputting the robots in list
            gripper i(port);
            grippers.push_back(i);

        }
        return grippers;
    }
    else{
        gripper i("/dev/ttyUSB0");
        grippers.push_back(i);

        cout << "Query failed: " << mysql_error(conn) << endl;
        return grippers;
    }
}

bool database::setGripper(int index, string newCOM)
{

}
