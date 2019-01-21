#include <iostream>
using namespace std;

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <algorithm>

#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()


int main(int argc, char const *argv[])
{
    int serial_port = open("/dev/rfcomm0", O_RDWR | O_NOCTTY);

    
    if (serial_port < 0) {
        printf("Error %i from open: %s\n", errno, strerror(errno));
    }

    // Create new termios struc, we call it 'tty' for convention
    struct termios tty;
    memset(&tty, 0, sizeof tty);

    // Read in existing settings, and handle any error
    if(tcgetattr(serial_port, &tty) != 0) {
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
    }

    tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
    tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
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
    tty.c_cc[VMIN] = 1;

    // Set in/out baud rate to be 9600
    cfsetispeed(&tty, B9600);
    cfsetospeed(&tty, B9600);

    // Save tty settings, also checking for error
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
    }

    // // Write to serial port
    char reset_msg[] = { 'A', 'T', 'Z', '\r'};
    char echo_msg[] = { 'A', 'T', 'E', '0', '\r'};
    char line_msg[] = { 'A', 'T', 'L', '0', '\r'};
    char pid_msg[] = { '0', '1', '0', '0', '\r'};

    write(serial_port, reset_msg, sizeof(reset_msg));
    sleep(1);
    write(serial_port, echo_msg, sizeof(echo_msg));
    sleep(0.2);
    write(serial_port, line_msg, sizeof(line_msg));
    sleep(0.2);
    write(serial_port, pid_msg, sizeof(pid_msg));    

    char read_buf [256];
    string rec = "";
    while(1){
        memset(&read_buf, '\0', sizeof(read_buf));
        int num_bytes = read(serial_port,read_buf, sizeof(read_buf));
        if(num_bytes>0){            
            rec = rec+string(read_buf);         
            cout<<read_buf<<endl;
            //cout<<"Buffer: "<<read_buf<<", Rec: "<<rec<<"\n";
            if (string(read_buf).find('>')!=string::npos){      
                replace( rec.begin(), rec.end(), '\n', ' ');          
                cout<<"Rec: "<<rec<<endl;
                rec = "";
            }
        }        
    }
    
    close(serial_port);

    cout<<"done\n";
    return 0;
}

