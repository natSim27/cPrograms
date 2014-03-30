#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkAcceptingState(int acceptingStates[], int numOfAcceptingStates, int finalState, char string[]);

int main(void){
	
  int q, s, currentState=0, numOfAcceptingStates,length, x, y, i, j, m, n, l;
  char *alphabet;
  char inputString[25], input[25];
  int **transitionTable, *acceptingStates;

  scanf("%d %d", &q, &s);

  alphabet = (char*)malloc(s * sizeof(char));
  scanf("%s", alphabet);
  
  transitionTable = (int**)malloc(q * sizeof(int*));
    for (n=0; n<q; n++) {
      transitionTable[n] = (int*)malloc(s * sizeof(int));
  } 

  for(x=0; x<=q-1; x++){
      for (y=0;y<=s-1;y++){
        scanf("%d", &transitionTable[x][y]);
      }
  }

  scanf("%d", &numOfAcceptingStates);
  
  acceptingStates = (int*) malloc(numOfAcceptingStates*sizeof(int));
	
  for(m=0; m<=numOfAcceptingStates-1; m++){
    scanf("%d", &acceptingStates[m]); 
  }

  scanf("%s", input);
  sscanf(input, "%[^.]", inputString);
	
  for(l=0;l<=strlen(inputString)-1;l++){
    for(i=0; i<=s-1; i++){
      if(inputString[l] == alphabet[i])
        currentState = transitionTable[currentState][i];
    }
  }
	
  checkAcceptingState(acceptingStates, numOfAcceptingStates, currentState, inputString);
	
}

int checkAcceptingState(int acceptingStates[], int numOfAcceptingStates, int finalState, char string[]){
  int j;

  for(j=0; j<=numOfAcceptingStates-1; j++){
    if(finalState == acceptingStates[j])
      return printf("DFA has accepted input string %s Ended in state %d.\n", string, finalState);
  }
	
  return printf("DFA has NOT accepted input string %s Ended in state %d.\n", string, finalState);
}
