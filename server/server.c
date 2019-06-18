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
        char buff1[MAX_LEN]="",buff2[MAX_LEN]="",op[2];
        int p, ns, pid;
        printf("Port -\n");
        scanf("%d",&p);
        int s = socket(AF_INET , SOCK_STREAM , 0);
        serv.sin_family = AF_INET;
        serv.sin_port = htons(p);
        serv.sin_addr.s_addr = htonl(INADDR_ANY);
        int k = bind(s , (struct sockaddr *)&serv , sizeof(serv));
        listen(s,5);
        int size = sizeof(client);
	togo:
        ns = accept(s , (struct sockaddr *)&client , &size);

	while(10)
	{
		int f = recv(ns ,op , sizeof(op) , 0);
		if(op[0]=='1')
		{
		        pid = fork();
		        if(pid==0)
			{
		                while(20)
		                {
		                        f = recv(ns ,buff1 , sizeof(buff1) , 0);
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
		                        int d = send(ns , buff2 , sizeof(buff2) , 0);
		                        if(strcmp(buff2,"bye\n")==0){break;}   
		                }
		        }	
			if(pid!=0)
				wait(NULL);
		}
		else if(op[0]=='2')
		{
		        f = recv(ns ,buff1 , sizeof(buff1) , 0);
		        printf("Filename : %s\n",buff1);

		        char filee[MAX_LEN];
		        f = recv(ns ,filee , sizeof(filee) , 0);
		        FILE *file = fopen(buff1, "w");

		        int results = fputs(filee, file);
		        if (results == EOF) 
			{
		                printf("Failed to write to the file.\n");
		        }
		        else
		        {
		                printf("File transfered succesfully.\n");
		        }
		        fclose(file);
		}
		else if(op[0]=='3')
		{
		        printf("Client is ready to recieve, enter filename that you wish to send:\n");
		        char name[30];
		        scanf("%s",name);
			while(!(file_exist(name)))
		        { 
				printf("File does not exist, enter a valid filename that you wish to send:\n");
				scanf("%s",name);
		        }
		        int d = send(ns , name , sizeof(name) , 0);
		        FILE *fp;
		        char f[MAX_LEN];
		        fp = fopen(name,"rb");
		        fread(f,MAX_LEN,1,fp);
		        d = send(ns , f , sizeof(f) , 0);
		        fclose(fp);
		}
		else if(op[0] == '4')
		{
			close(ns);
			goto togo;
		}
		else
		{
			close(ns);
			close(s);
			exit(0);
		}
	}
        close(ns);
        close(s);
}

