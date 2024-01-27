#include<stdio.h>
void display(char board[3][3], char player1N[], char player2N[]){
    int i;
    printf("X: %s\t\tO: %s\n\n",player1N,player2N);
    for(i=0;i<3;i++){
        printf(" %c | %c | %c\n-----------\n", board[i][0],board[i][1],board[i][2]);
    }
}
int move(char player1N[], char player2N[], char turn){
    int moveN;
    if(turn=='X')
        printf("%s's turn, Enter number to place X: ", player1N); 
    else
        printf("%s's turn, Enter number to place O: ",player2N); 
    scanf("%d", &moveN);
    if(moveN<1 || moveN>9){
        moveN = move(player1N,player2N,turn);
    }
    return moveN;
}
int updateBoard(char board[][3], int moveN,char turn){
    int row = (moveN-1)/3,col = (moveN-1)%3;
    if(board[row][col]=='X' || board[row][col]=='O')
        return 1;
    else
        board[row][col] = turn;
    return 0;
}
void winDisplay(int winPos, char winPlayer, char player1N[], char player2N[], char board[][3]){
    int i;
    if(winPlayer=='X')
        printf("\033[1;32mX: %s\033[1;0m\t\tO: %s\n\n",player1N,player2N);
    else
        printf("X: %s\t\t\033[1;32mO: %s\033[1;0m\n\n",player1N,player2N);
    for(i=0;i<3;i++){
        if(winPos<3){
        if(i==winPos)
            printf("\033[1;32m %c | %c | %c\033[1;0m\n-----------\n", board[i][0],board[i][1],board[i][2]);
        else
            printf(" %c | %c | %c\n-----------\n", board[i][0],board[i][1],board[i][2]);
        }
        else if(winPos<6)
            if(winPos==3)
                printf("\033[1;32m %c \033[1;0m| %c | %c\n-----------\n", board[i][0],board[i][1],board[i][2]);
            else if(winPos==4)
                printf(" %c |\033[1;32m %c \033[1;0m| %c\n-----------\n", board[i][0],board[i][1],board[i][2]);
            else if(winPos==5)
                printf(" %c | %c |\033[1;32m %c \033[1;0m\n-----------\n", board[i][0],board[i][1],board[i][2]);
    }
    if(winPos==6){
        printf("\033[1;32m %c \033[1;0m| %c | %c \n-----------\n %c |\033[1;32m %c \033[1;0m| %c \n-----------\n %c | %c |\033[1;32m %c \033[1;0m\n-----------\n", board[0][0],board[0][1],board[0][2], board[1][0],board[1][1],board[1][2], board[2][0],board[2][1],board[2][2]);
    }
    else if(winPos==7){
        printf(" %c | %c |\033[1;32m %c \033[1;0m\n-----------\n %c |\033[1;32m %c \033[1;0m| %c \n-----------\n\033[1;32m %c \033[1;0m| %c | %c \n-----------\n", board[0][0],board[0][1],board[0][2], board[1][0],board[1][1],board[1][2], board[2][0],board[2][1],board[2][2]);
    }
}
int checkWin(char board[][3],char player1N[], char player2N[]){
    int i,j,availMove=0;
    char pos[2] = {'X','O'};
    for(i=0;i<3;i++){
        for(j=0;j<2;j++)
            if(board[i][0]==pos[j] && board[i][1]==pos[j] && board[i][2]==pos[j]){
                winDisplay(i,pos[j],player1N,player2N,board);
                return 1;
            }
        for(j=0;j<2;j++)
            if(board[0][i]==pos[j] && board[1][i]==pos[j] && board[2][i]==pos[j]){
                winDisplay(i+3,pos[j],player1N,player2N,board);
                return 1;
            }
    }
    for(j=0;j<2;j++)
        if(board[0][0]==pos[j] && board[1][1]==pos[j] && board[2][2]==pos[j]){
            winDisplay(6,pos[j],player1N,player2N,board);
            return 1;
        }
        else if(board[0][2]==pos[j] && board[1][1]==pos[j] && board[2][0]==pos[j]){
            winDisplay(7,pos[j],player1N,player2N,board);
            return 1;
        }
    for(i=0;i<9;i++){
        int row = i/3, col=i%3;
        if(board[row][col]!='O' && board[row][col]!='X')
            availMove++;
    }
    if(availMove>0)
        return 0;
    else
        return -1;
}
int contGame(){
	int play;
	printf("\nWant to play another?\n1. Yes\n2. No\nEnter: ");
	scanf("%d", &play);
	if(play==1)
		return 1;
	else
		return 0;
}
void resetBoard(char board[][3]){
	int i,j;
    char newBoard[3][3] = {'1','2','3','4','5','6','7','8','9'};
    // board = newBoard;
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			board[i][j] = newBoard[i][j];
	
}
int main(){
    char board[3][3] = {'1','2','3','4','5','6','7','8','9'};
    char turn = 'X', player1N[20], player2N[20];
    int moveN,ava,game=1,win=0;
    printf("Enter name of player 1: ");
    gets(player1N);
    printf("Enter name of player 2: ");
    gets(player2N);
    while(game){
    display(board,player1N,player2N);
    moveN = move(player1N,player2N,turn);
    ava = updateBoard(board,moveN,turn);
    if(ava)
       printf("\033[1;33mCan't Overwrite\n\033[1;0m");
    else{
        win = checkWin(board,player1N,player2N);
        if(win==1){
            if(turn=='X')
                printf("\033[1;32m\n%s WON!\n\033[1;0m", player1N);
            else
                printf("\033[1;32m\n%s WON!\n\033[1;0m", player2N);
            resetBoard(board);
            game = contGame();
        }
        else if(win==-1){
            printf("\033[1;33m\nDRAW!\n\033[1;0m");
            resetBoard(board);
            game = contGame();
        }
        else
            turn = turn=='X'?'O':'X';
    }
    }
    return 0;
}
