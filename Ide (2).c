#include <stdio.h>
#include <stdlib.h>


struct PlayerInformation {
    char name[50];
    char date[20];
    int generations;
};

void PlayerInfo(struct PlayerInformation* player){
    printf("Enter your Name and Date:\n");
    scanf("%s%s", &player->name, &player->date);
}

int max(int a, int b){
    return a>b ? a : b;
}

int min(int a, int b){
    return a>b ? b : a;
}

void readPlayerInformation(char *arr){
    char x[5][5] = {
                {'x','-','x','-','x'},
                {'-','x','-','x','-'},
                {'x','-','x','-','x'},
                {'-','x','-','x','-'},
                {'x','-','x','-','x'}
                };
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            arr[i*5+j] = x[i][j];
        }
    }
}
void generations(char *arr, int rows, int cols){
    char *temparr = malloc(sizeof(char)*rows*cols);
    int activeNeighbours;
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            switch (*(arr+(i*5)+j)){
                case 'x':
                    activeNeighbours = calculateActiveNeighbouringCells(arr, rows, cols, i, j);
					if(activeNeighbours == 2 || activeNeighbours == 3){
						temparr[i*cols+j] = 'x';
					}
					else{
						temparr[i*cols+j] = '-';
					}
					break;
				case '-':
					activeNeighbours = calculateActiveNeighbouringCells(arr, rows, cols, i, j);
					if(activeNeighbours == 3){
						temparr[i*cols+j] = 'x';
					}
					else{
						temparr[i*cols+j] = '-';
					}
					break;
				default :
					break;
            }
        }
    }
    memcpy(arr, temparr, sizeof(char)*rows*cols);
    free(temparr);
}

int calculateActiveNeighbouringCells(char *arr, int rows, int cols, int rowPosition, int colPosition){
    int activeNeighbours = 0;
    for(int x = max(0, rowPosition-1); x <= min(rowPosition+1, rows-1); x++) {
    for(int y = max(0, colPosition-1); y <= min(colPosition+1, cols-1); y++) {
      if(x != rowPosition || y != colPosition) {
        if(*(arr+x*cols+y) == 'x')
            activeNeighbours++;
      }
    }
  }
  return activeNeighbours;
}

void displayGeneration(char *arr, int rows, int cols, int generation){
    printf("\nGeneration:%d\n", generation);
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            printf("%c ", *(arr+(i*5)+j));
        }
        printf("\n");
    }
}

int main(void) {
	struct PlayerInformation* player;
	char *arr;
	arr = malloc(sizeof(char)*5*5);
    player = malloc(sizeof(struct PlayerInformation));
	PlayerInfo(player);
	readPlayerInformation(arr);
	displayGeneration(arr, 5, 5, 0);
	for(int i=1;i<6;i++){
	    generations(arr, 5, 5);
	    displayGeneration(arr, 5, 5, i);
	}
	free(player);
	free(arr);
	return 0;
}