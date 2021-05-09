#include "database.h"


database::database()
{
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "127.0.0.1", "root", "UbuJhJoefi99", "ur5Database", 3306, NULL, 0);
    //conn = mysql_real_connect(conn, "127.0.0.1", "root", "Emil2000", "ur5Database", 3306, NULL, 0);
}

vector<robotUR5> database::getRobots()
{
    ur5Bots.clear();
    if(conn == 0){
        robotUR5 i("NA", "127.0.0.1");
        ur5Bots.push_back(i);

        cout << "Query failed: " << mysql_error(conn) << endl;
        return ur5Bots;
    }
    string navn;
    string ip;
    query = "select UR5.navn, UR5.IP from UR5 order by UR5.robot_id";
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



vector<string> database::getGrippers()
{
    gripperports.clear();
    string port;
    if(conn == 0){
        gripperports.push_back("/dev/ttyUSB0");

        cout << "Query failed: " << mysql_error(conn) << endl;
        return gripperports;
    }
    query = "select Gripper.COM_port from Gripper order by Gripper.Gripper_id";
    q = query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {
        res = mysql_store_result(conn);

        while ((row = mysql_fetch_row(res))){
            port = row[0];
            //inputting the robots in list
            gripperports.push_back(port);

        }
        return gripperports;
    }
    else{
        gripperports.push_back("/dev/ttyUSB0");

        cout << "Query failed: " << mysql_error(conn) << endl;
        return gripperports;
    }
}
void database::sendData(int test,int rAg, double ampP, double ampA, int stroke, double force, double time, int dir){

    if(conn == 0){
        cout << "Update failed. " << endl;
    }else{
        string max;

        query = "select max(gripper_data_id) from Gripper_Data";
        q = query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);

            while ((row = mysql_fetch_row(res))){
                max = row[0];
            }
        }
        else{
            max = "1";

            cout << "Query failed: " << mysql_error(conn) << endl;
        }

        stringstream s(max);
        int maxx = 0;
        s >> maxx;

        query = "insert into Gripper_Data values ("+ to_string(maxx+1) +","+ to_string(test) +","+ to_string(ampP) +","+ to_string(ampA) +","+ to_string(stroke) +","+ to_string(force) +","+ to_string(time) +","+ to_string(dir) +","+ to_string(rAg+1) +","+ to_string(rAg+1) +");";
        cout << query << endl;
        q = query.c_str();
        qstate = mysql_query(conn, q);
        if (qstate != 0)
            cout << "Update failed. " << mysql_error(conn) << endl;
        else{
            cout << "send" << endl;
        }
    }

}

