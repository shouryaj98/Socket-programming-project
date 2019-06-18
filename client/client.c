#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <signal.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define MAX_LEN 1024

int file_exist (char *filename)
{
  struct stat   buffer;   
  return (stat (filename, &buffer) == 0);
}

int main()
{
        struct sockaddr_in serv;
        struct sockaddr_in client;
        char buff1[MAX_LEN]="",buff2[MAX_LEN]="",address[100]="";
	size_t lop2;
        int s;
        int p,comp;
	togo:
	s = socket(AF_INET , SOCK_STREAM , 0);
	printf("Whom do you want to connect with ?\n1.Computer 1\n2.Computer 2\n3.Computer 3\n");
	printf("Computer -\n");
        scanf("%d",&comp);
	if(comp==1)
		strcpy(address,"192.168.43.119"); // Change !
	else if(comp==2)
		strcpy(address,"192.168.43.207"); // Change !
	else if(comp==3)
		strcpy(address,"192.168.43.235"); // Change !
	else
	{
		printf("\nIncorrect choice entered, terminating -\n");
		return 0;
	}
	printf("\nPort -\n");
        scanf("%d",&p);
        serv.sin_family = AF_INET;
        serv.sin_port = htons(p);
        serv.sin_addr.s_addr = inet_addr(address);
        int size = sizeof(serv);
        int xyz = connect(s , (struct sockaddr *)&serv , sizeof(serv));
        printf("Connected\n");
	int pid;
	while(10)
	{
		printf("1.Chat\n2.Send File\n3.Receive File\n4.Disconnect\n5.Exit\n");
		char op[2],t;
		
		scanf("%s",op);
		int d = send(s , op , sizeof(op) , 0);
		if(op[0]=='1')
		{
		        printf("Start Chatting\n");
		        pid = fork();
		        if(pid==0)
			{        
		                while(20)
		                {
		                        int f = recv(s ,buff1 , sizeof(buff1) , 0);
		                        printf("Received -%s\n",buff1);
		                        if(strcmp(buff1,"bye\n")==0){exit(0);}   
		                }
		        }
		        else
		        {
		                
				fgets(buff2, MAX_LEN, stdin); 
		                while(20)
		                {
		                        fgets(buff2, MAX_LEN, stdin); 
		                        d = send(s , buff2 , sizeof(buff2) , 0);
		                        if(strcmp(buff2,"bye\n")==0){break;}   
		                }
		        }
		if(pid!=0)
			wait(NULL);

		}
		else if(op[0]=='2')
		{
		        printf("Enter filename that you wish to send:\n");
		        char name[30];
		        scanf("%s",name);
			while(!(file_exist(name)))
		        { 
				printf("File does not exist, enter a valid filename that you wish to send:\n");
				scanf("%s",name);
		        }
			d = send(s , name , sizeof(name) , 0);
		        FILE *fp;
		        char f[MAX_LEN];
		        fp = fopen(name,"rb");
		        fread(f,MAX_LEN,1,fp);
		        
		        d = send(s , f , sizeof(f) , 0);
		        fclose(fp);
		}
		else if(op[0]=='3')
		{
		        int f = recv(s ,buff1 , sizeof(buff1) , 0);
			
		        printf("Filename : %s\n",buff1);

		        char filee[MAX_LEN];
		        f = recv(s ,filee , sizeof(filee) , 0);
		        FILE *file = fopen(buff1, "w");

		        int results = fputs(filee, file);
		        if (results == EOF) {
		                printf("Failed to write to the file.\n");
		        }
		        else
		        {
		                printf("File transfered succesfully.\n");
		        }
		        fclose(file);
		}
		else if(op[0] == '4')
		{
		        
			close(s);
			goto togo;
		}
		else
		{
			close(s);
			exit(0);		
		}
	}
        close(s);
}

