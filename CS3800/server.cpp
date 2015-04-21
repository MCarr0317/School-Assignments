/*Connor Coward & Matt Carr 
4-20-2015
CS3800 - Operating Systems
This file acts as the server for a chat room
*/

#include <iostream>
#include <pthread.h> 
#include <signal.h>
#include <cstdlib>
#include <stdio.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>  /* define socket */
#include <netinet/in.h>  /* define internet socket */
#include <netdb.h>       /* define internet socket */
#include <unistd.h>
#include <stdlib.h>
using namespace std;

#define SERVER_PORT 9999

const int MAX_CLIENT = 10;
int FD[MAX_CLIENT]; // backlog of clients
char usernames[MAX_CLIENT][500]; // container for all usernames
int counter = 0;
int numClients = 0; //current number of clients in the chat
int sd; //socket descriptor
pthread_mutex_t m;

void* runClient(void* arg);

// Interrupt handler for control-C
void signalHandler(int sig)
{
  char message[] = "Server will shut down in 10 seconds";
  printf("\n%s\n", message);
  
  // Tell clients they will be booted
  for(int i = 0; i < MAX_CLIENT; i++)
    if(FD[i] > 0)
      write(FD[i], message, sizeof(message));
  
  sleep(10); // wait for the ten seconds
  char code[]="505"; // special code for terminating the program
  
  // boot the clients off
  for(int i = 0; i < MAX_CLIENT; i++)
    if(FD[i] > 0)
    {
      printf("%s has left the chat.\n", usernames[i]);
      //cout << usernames[i] << " has left" << endl;
      write(FD[i], code, sizeof(code));
    }
  
  printf("Server has terminated\n");
  close(sd); // close the socket
  exit(1);
}

int main()
{
  
  struct sockaddr_in server_addr = { AF_INET, htons( SERVER_PORT ) };
  struct sockaddr_in client_addr = { AF_INET };
  unsigned int client_len = sizeof( client_addr );
  signal(SIGINT, signalHandler);
  
  for(int i = 0; i < MAX_CLIENT; i++)
  {
    FD[i] = 0;
  }

  // create a stream socket
  if( ( sd = socket( AF_INET, SOCK_STREAM, 0 ) ) == -1 )
  {
    cerr << "SERVER: socket failed" << endl;
    exit( 1 );
  }
  
  // bind the socket to a unique address
  if( bind(sd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1 )
  {
    cerr << "SERVER: bind failed" << endl;
    exit( 1 );
  }

  // start listening for clients 
  if( listen( sd, MAX_CLIENT-1 ) == -1 )
  {
    cerr << "SERVER: listen failed" << endl;
    exit( 1 );
  }

  printf("SERVER is listening for clients to establish a connection\n");

  int temp;
  // while a connection is accepted
  while((temp = accept(sd, (struct sockaddr*)&client_addr, &client_len )) > 0)
  {  
    // Check for max number of clients
    if(numClients < MAX_CLIENT)
    {
      if (!FD[counter])
      {
        pthread_mutex_lock(&m); // lock
        FD[counter++] = temp;
        counter = counter % MAX_CLIENT; 
        numClients++;
        if(numClients < MAX_CLIENT)
          while(FD[counter] != 0)
            counter = (counter + 1) % MAX_CLIENT;

        pthread_mutex_unlock(&m); // release lock
        pthread_t clientThread;
        pthread_create(&clientThread, NULL, runClient, &temp); // create the thread
      }
      else 
      {
        pthread_mutex_lock(&m);
        while(FD[counter] != 0)
          counter = (counter + 1)%MAX_CLIENT;

        FD[counter++] = temp;
        counter = counter % MAX_CLIENT;
        numClients++;
        if(numClients < MAX_CLIENT)
          while(FD[counter] != 0)
            counter = (counter + 1)%MAX_CLIENT;

        pthread_mutex_unlock(&m);
        pthread_t clientThread;
        pthread_create(&clientThread, NULL, runClient, &temp);
      }
    }
    else
    {
      char error[] = "Sorry, too many users are connected.\n";
      write(temp, error, sizeof(error));
    }
  }
  
 return 0;
}

// Thread for each client connection
void* runClient(void* arg) 
{
  if(arg == NULL)
    cerr << "Thread received null argument" << endl;
  
  char buffer[512];
  int k;
  int skt = *(int *)arg;
  int location; // the index of usernames in FD

  // find location of username in FD
  for(int i = 0; i < MAX_CLIENT; i++)
    if(FD[i] == skt)
      location = i;
  
  char username[500]; //containers for username and their messages
  char message[1024];
  
  //read in client username and greet them
  if((k = read(skt, buffer, sizeof(buffer))) > 0)
  {   
    printf("%s joined\n", buffer);
    strcpy(username, buffer);
    strcat(message, "Welcome ");
    strcat(message, username);
    write(skt, message, sizeof(message));
  }
  
  //create alert string
  pthread_mutex_lock(&m); // but lock first
  strcat(message, "ALERT: ");
  strcat(message, username);
  strcat(message, " joined the chat");
  strcpy(usernames[location], username);
 
  // send new join alert to all clients
  for(int i = 0; i < MAX_CLIENT; i++)
    if(FD[i] > 0 && FD[i] != skt)
      write(FD[i], message, sizeof(message));
    
  pthread_mutex_unlock(&m); // we're done so unlock
  
  // while the client keeps sending messages  
  while ((k = read(skt, buffer, sizeof(buffer))) > 0)
  {
    pthread_mutex_lock(&m); // lock
    strcpy(message, " "); 
    if (strcmp(buffer, "")) // print the username only if they sent something
    {
      strcpy(message, username);
      strcat(message, ": ");
      strcat(message, buffer);
    }

    //write message to each FD
    for(int i = 0; i < MAX_CLIENT; i++)
      if(FD[i] > 0 && FD[i] != skt)
        write(FD[i], message, sizeof(message));
    
    pthread_mutex_unlock(&m); //unlock      
  }

  // if the client has quit the chat, we need
  //   to close the socket and decrement numClients
  pthread_mutex_lock(&m);
  close(FD[location]);
  FD[location] = 0;
  printf("%s has left\n", username);
  numClients--;
  pthread_mutex_unlock(&m);
  pthread_exit(arg);


  return NULL;
}
