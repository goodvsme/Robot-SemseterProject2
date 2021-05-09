#include "gripper.h"

gripper::gripper()
{

}


bool gripper::setAddress(string inPort)
{

    portCOM = inPort;
    //portCOM.c_str()
    serial_port  = open("/dev/ttyUSB0", O_RDWR);

    // Create new termios struc, we call it 'tty' for convention
    struct termios tty;

    // Read in existing settings, and handle any error
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

    tty.c_cc[VTIME] = 0;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
    tty.c_cc[VMIN] = 0;

    fcntl(serial_port,F_SETFL,FNDELAY);

    // Set in/out baud rate to be 115200
    cfsetispeed(&tty, B115200);
    cfsetospeed(&tty, B115200);

    // Save tty settings, also checking for error
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
        return 1;
    }

    printf("%s\n", strerror(errno));
    return 0;
}


bool gripper::readSerial(class database *inwrite, int testid, int rAgID){

        if(stop == 0){

            calibrateTest = 0;
            int datafr = read(serial_port, &dataIn, sizeof(dataIn));
            if(datafr == 0){return 0;}
            cout<<"dataIn[0] " << (int)dataIn[0] <<endl;
            if(dataIn[0] == 0){         //Change Direction
                //send data
                inwrite->sendData(testid, rAgID, peak_amp, avg_amp, dataIn[0], force, strokeTime, direction);
                //reset variabals
                amp=0;
                avg_amp=0;
                peak_amp=0;
                force=0;
                strokeTime=0;

                dataIn[0]=128;

                return 1;

            }else if(dataIn[0]==1){      //Stop

                stop = 1;

                inwrite->sendData(testid, rAgID, peak_amp, avg_amp, dataIn[0], force, strokeTime, direction);
                //reset variabals
                amp=0;
                avg_amp=0;
                peak_amp=0;
                force=0;
                strokeTime=0;

                dataIn[0]=128;
                return 1;
            }
            else{               //Running
                amp = ((5/637.5)*(int)dataIn[0]-1);
                avg_amp = (abs(amp)+avg_amp)/2;
                if(abs(amp)>peak_amp){
                    peak_amp=abs(amp);
                }
                strokeTime+=0.05;
                if(0>amp){
                    direction = 1;
                }else{
                    direction = -1;
                }
                angleTime += 0.05*direction;
                angle = (70/speed)*angleTime;
                force = (0.3*(58/1)*490)/(55*sin((90-angle)*(M_PI/180))+45*cos(35*(M_PI/180)));
                return 0;
            }
        }else if(calibrateTest == 1){
            int datafr = read(serial_port, &dataIn, sizeof(dataIn));
            if(datafr == 0){return 0;}

            if(dataIn[0]==1){      //Stop
                //reset variabals
                amp=0;
                avg_amp=0;
                peak_amp=0;
                force=0;
                strokeTime=0;

                dataIn[0]=128;
                angleTime = 0;
                angle = (70/speed)*angleTime;
                calibrateTest = 0;
                return 1;
            }

        }
        return 0;
}


void gripper::closeSerial(){
    close(serial_port);
}

void gripper::sendmsg(unsigned char i){
    stop = 0;
    unsigned char msg []= {i};
    write(serial_port, msg, sizeof(msg));
}

void gripper::calibrate()
{
    stop = 1;
    calibrateTest = 1;
    unsigned char msg []= {'2'};
    write(serial_port, msg, sizeof(msg));
}

gripper::~gripper(){
    closeSerial();
}
