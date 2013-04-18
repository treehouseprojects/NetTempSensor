#include <my_global.h>
#include <time.h>
#include <mysql.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

volatile sig_atomic_t stop;

int	open_port(void)
{
  int fd;

  fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);
  
  if (fd == -1)
  {
   // Could not open the port.			
   perror("open_port: Unable to open /dev/ttyUSB0 - ");
  }
  else
	fcntl(fd, F_SETFL, 0);
	
  struct termios options;
    
  tcgetattr(fd, &options); //setting baud rates and stuff
  cfsetispeed(&options, B19200);
  cfsetospeed(&options, B19200);
  options.c_cflag |= (CLOCAL | CREAD);
  tcsetattr(fd, TCSANOW, &options);
  tcsetattr(fd, TCSAFLUSH, &options);
  
  options.c_cflag &= ~PARENB;//next 4 lines setting 8N1
  options.c_cflag &= ~CSTOPB;
  options.c_cflag &= ~CSIZE;
  options.c_cflag |= CS8;
  
  options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); //raw input
  options.c_iflag &= ~(IXON | IXOFF | IXANY); //dsiable software flow control
  
  sleep(5); //required to make flush work, for some reason
  tcflush(fd,TCIOFLUSH);

  return (fd);
}

void inthand(int signum) {
    stop = 1;
}

int main(int argc, char **argv) {
  MYSQL *conn;
  MYSQL_RES *result;
  MYSQL_ROW row;
  int num_fields;
  
  signal(SIGINT, inthand);

  int fd = open_port();
  
  struct tm *ptr;
  time_t lt;

  conn = mysql_init(NULL);

  if (conn == NULL) {
      printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
      exit(1);
  }

  if (mysql_real_connect(conn, "hostname", "username", "password", "database", 0, NULL, 0) == NULL) {
	  printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
      exit(1);
  }
  
	char buf[10], date[80], command[150];
		
	while(!stop) {
		lt = time(NULL);
		ptr = localtime(&lt);
		strftime(date, 100, "%a %b %d %H:%M:%S %Y", ptr);
		read (fd, buf, sizeof(buf));
		
		//strncpy(temp, buf, 3);
		//printf("%c%c", temp[0], temp[1]);
				
		sprintf(command, "UPDATE roomtemp SET temperature='%c%c', date='%s' WHERE type='display'", buf[0], buf[1], date);			
		printf("%s\n", command);
		mysql_query(conn, command);
	}
	
	printf("safe exit\n");
		
	close(fd);
	mysql_free_result(result);
	mysql_close(conn);
	return 0;
}
