#include<stdio.h>
int isAttack(int i, int j, int board[5][5],int N){
int k,l;
for (k=1;k<=i-1;k++){
if (board[k][j]==1)
return 1;
}
k=i-1;
l=j+1;
while(k>=1 && l<=N){
if(board[k][l]==1)
return 1;
k=k-1;
l=l+1;
}
k=i-1;
l=j-1;
while(k>=1 && l>=1){
if (board[k][l]==1)
return 1;
k=k-1;
l=l-1;
}
return 0;
}
int n_queen(int row, int N, int board[5][5]){
if (row > N)
return 1;
int j;
for(j=1;j<=N;j++){
if(!isAttack(row,j,board,N)){
board [row][j]=1;
if(n_queen (row+1,N,board))
return 1;
board [row][j]=0;
}
}
return 0;
}
int main(){
int board[5][5],i,j;
for(i=1;i<=5;i++){
for(j=1;j<=5;j++)
board[i][j]=0;
}
n_queen(1,5,board);
for(i=1;i<=5;i++){
for(j=1;j<=5;j++)
printf("%d ",board[i][j]);
printf("\n");
}
return 0;
}
