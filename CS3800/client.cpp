/*
Connor Coward, Matt Carr
4-20-2015
CS3800 - Operating systems
This file defines the client for a chatroom
*/

#include <iostream>
#include <cstdlib>
#include <signal.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>

#define SERVER_PORT 9999

using namespace std;

int clientSocket;
int k;
char buff[1024];
char code[]="505";
bool exitCondition = false;

void signalHandler(int signalNumber)
{
  if(signalNumber==2)
  {
    cout<<"\nTo exit type /quit /exit or /part"<<endl;
  }
}

void * readingOut(void* arg);

int main(int argc, char* argv[])
{
  signal(SIGINT, signalHandler);
  pthread_mutex_t m;
  char cQuit[]="/quit"; //define quit commands
  char cExit[]="/exit";
  char cPart[]="/part";
  struct hostent *hostServer; //server
  struct sockaddr_in server_addr = { AF_INET, htons( SERVER_PORT ) }; //server address

  // Check the number of arguments passes in
  if(argc != 2)
  {
    printf("ERROR: Wrong usage, example: %s hostname\n", argv[0]);
    exit(1);
  }

  // look up the hostname to see if it is real
  if( (hostServer = gethostbyname(argv[1]) ) == NULL)
  {
    printf("ERROR: Tried to look up %s - Not Found\n", argv[1]);
    exit(1);
  }
  
  // copy the host address to our server address
  memcpy( hostServer->h_addr_list[0], (char*)&server_addr.sin_addr, hostServer->h_length );
    
  //create the client's socket as a stream socket
  if( (clientSocket=socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    printf("ERROR: Could not create a socket\n");
    exit(1);
  }
  
  // Connect the client socket to the server
  if( (connect( clientSocket,(struct sockaddr*)&server_addr, sizeof(server_addr))) == -1)
  {
    printf("ERROR: Could not connect to server\n");
    exit(1);
  }
  
  //get username from user
  printf("Connection was successful!\nEnter a Username: ");
  cin >> buff;

  // write the username to the server
  write(clientSocket, buff, sizeof(buff));
  // read from the server
  read(clientSocket, buff, sizeof(buff));
  printf("%s\n", buff);

  //create thread for handling simultaneous input & output
  pthread_t readThread;
  pthread_create(&readThread, NULL, readingOut, &clientSocket);
  
  cin.ignore(1000, '\n');
   
  //output to server
  while(exitCondition==false)
  {
    string str = "";
    getline(cin, str); //read the clients message
    strcpy(buff, str.c_str()); //copy it into the buffer
    
    // check if it matches any of our commands
    if(!strcmp(buff, cQuit) || !strcmp(buff, cExit)|| !strcmp(buff, cPart))
    {
      exitCondition = true;
      printf("Connection ended.\n");
      exit(1);
    }
    else // send the message
      write(clientSocket, buff, str.size()*8); // one byte per char so multiply by 8
  }
  
  close(clientSocket); //close the socket
  return 0;
}

//input from server
void* readingOut(void* arg)
{
  int clientSocket = *(int *)arg;
  
  // while the clients keep talking
  while ((k = read(clientSocket, buff, sizeof(buff))) > 0)
  {
    // if the server issues a termination announcement
    if(strcmp(buff, code) == 0)
    {
      exitCondition = true;
      printf("Connection ended\n");
      exit(1);
    }
    printf("%s\n", buff); //if not, print what the server has sent
  }
  
  return NULL;
}
