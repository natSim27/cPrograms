#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void serverCheck(char userID[32], char userXOR[32], char userHash[32],char r[96]);
int serverSendRand(char inputUserID[32], char *serverNum, char *userHash);

/*
	The main method represents the user in this progam and sends their user name to the server in the method serverSendRand.
	The server then checks user ID and if the user is in table it stores its hash in the server and send the user a random number.
	The user then does a bitwise XOR function between its hash and the random number the server has sent it. The user then sends 
	this XOR function back to the server in the method serverCheck and the server then does another bitwise XOR function on the 
	function the user sent and the random number it sent to the user. If the hash the server has stored for this user and the result 
	of the bitwise XOR it has just performed match, it authenticates the user and sends the message "Access granted."
*/
int main(void){
	char inputUserID[32];
	char userID[32];
	char userHash[12];
	char r[96];
	char userXOR[32];
	char serverRetrievalXOR[32];
	int i;
	
	printf("Enter user name: ");
	scanf("%s", userID);
	
	serverSendRand(userID,r, userHash);
	
	for(i=0;i<32;i++){
		userXOR[i] = userHash[i] ^ r[i];
	}
	
	serverCheck(userID, userXOR,userHash, r);
}

int serverSendRand(char inputUserID[32], char *serverNum, char *userHash){
	int possibleNums[20];
	int k,l;
	
	char tableUserID[32];
	
	FILE *userTable;
	
	userTable=fopen("table.txt", "r");
	
	fscanf(userTable,"%s %s",tableUserID, userHash);
	
	while(strcmp(inputUserID,tableUserID)!=0){
		fscanf(userTable,"%s %s",tableUserID, userHash);
		
		if(fscanf(userTable,"[^%s] %s",tableUserID) == EOF){
			printf("Unrecognized user.");
			exit(1);
		}
	}
	
	for(k=0;k<20;k++)
		possibleNums[k] = rand() % 999 + 100;;

	
	for(l=0;l<4;l++)
		sprintf(serverNum,"%d%d%d%d", possibleNums[rand()%20]);
	
}


void serverCheck(char userID[32], char userXOR[32], char userHash[32],char r[96]){
	int j;
	char serverXOR[32];
		
	for(j=0;j<32;j++){
		serverXOR[j] = r[j] ^ userXOR[j];
	}
	
	if(strcmp(serverXOR,userHash) == 0)	   printf("Access Granted");

	else	printf("Access Denied");
}


