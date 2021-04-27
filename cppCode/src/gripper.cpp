#include "gripper.h"

gripper::gripper()
{

}


bool gripper::setAddress(string inPort)
{

    portCOM = inPort;
    //portCOM.c_str()
    serial_port  = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);


    FD_ZERO(&fdset);
    FD_SET(serial_port, &fdset);


    tv.tv_sec = 0;
    tv.tv_usec = 0;

    // Create new termios struc, we call it 'tty' for convention
    struct termios tty;

    // Read in existing settings, and handle any error
    cout<<tcgetattr(serial_port, &tty)<<endl;
    if(tcgetattr(serial_port, &tty) != 0) {

        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
         cout<<""<<endl;

        return 1;
    }

    tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
    tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
    tty.c_cflag &= ~CSIZE; // Clear all bits that set the data size
    tty.c_cflag |= CS8; // 8 bits per byte (most common)
    tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
    tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO; // Disable echo
    tty.c_lflag &= ~ECHOE; // Disable erasure
    tty.c_lflag &= ~ECHONL; // Disable new-line echo
    tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

    tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
    // tty.c_oflag &= ~OXTABS; // Prevent conversion of tabs to spaces (NOT PRESENT ON LINUX)
    // tty.c_oflag &= ~ONOEOT; // Prevent removal of C-d chars (0x004) in output (NOT PRESENT ON LINUX)

    tty.c_cc[VTIME] = 1;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
    tty.c_cc[VMIN] = 1;

    fcntl(serial_port,F_SETFL,FNDELAY);

    // Set in/out baud rate to be 115200
    cfsetispeed(&tty, B115200);
    cfsetospeed(&tty, B115200);

    // Save tty settings, also checking for error
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
        return 1;
    }

    //1 close, 2 is open
    //unsigned char msg []= {2};
    //write(serial_port, msg, sizeof(msg));

    printf("%s\n", strerror(errno));
    return 0;
}


void gripper::readSerial(class database *inwrite, int testid, int rAgID){

    int ret = select(serial_port +1, &fdset, 0, 0, &tv);

    if(!ret){return;}

    if(stop == 0){
        read(serial_port, &dataIn, sizeof(dataIn));
        if(dataIn[0] == 0){
            //send data
            //inwrite->sendData(testid, rAgID, peak_amp, avg_amp, dataIn[0], force, strokeTime, direction);
            //reset variabals
            amp=0;
            avg_amp=0;
            peak_amp=0;
            force=0;
            strokeTime=0.05;



            dataIn[0]=128;


        }else if(dataIn[0]==1){
            stop = 1;
            //send data
            //inwrite->sendData(testid, rAgID, peak_amp, avg_amp, dataIn[0], force, strokeTime, direction);
            //reset variabals
            amp=0;
            avg_amp=0;
            peak_amp=0;
            force=0;
            strokeTime=0.05;




            dataIn[0]=128;

        }
        else{
            amp = ((5/637.5)*(int)dataIn[0]-1);
            avg_amp = (abs(amp)+avg_amp)/2;
            if(abs(amp)>peak_amp){
                peak_amp=abs(amp);
            }
            strokeTime+=0.05; 
            if(0>amp){
                direction = 1;
            }else{
                direction = 0;
            }
            angleTime += 0.05*direction;
            force=(0.3*(58/1)*490)/(55*sin(1.571-(1.222/speed)*(speed-angleTime))+45*cos(0.611));
            angle = (70/speed)*angleTime;

        }
        cout << angle << endl;
    }




}


void gripper::closeSerial(){
    close(serial_port);
}

void gripper::sendmsg(unsigned char i){
    unsigned char msg []= {i};
    write(serial_port, msg, sizeof(msg));
    stop = 0;
}

gripper::~gripper(){
    closeSerial();
}
