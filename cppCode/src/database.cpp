#include "database.h"

database::database()
{
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "127.0.0.1", "root", "Emil2000", "ur5Database", 3306, NULL, 0);
}
