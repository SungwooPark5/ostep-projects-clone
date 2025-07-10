#include <stdio.h>

int main(int argc, char *argv[]){

  if (argc <2){
    return 0;
  }
  
  char buffer[1024];

  for(int i=0; i<(argc-1); i++){
      FILE *fp = fopen(argv[i+1],"r");
      if(fp==NULL){
	printf("wcat: cannot open file\n");
	return 1;
      }

    while(fgets(buffer, sizeof(buffer), fp)!=NULL){
      printf("%s", buffer);
    }
  }
      
  return 0;
}

