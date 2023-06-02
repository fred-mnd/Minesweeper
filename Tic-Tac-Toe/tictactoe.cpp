#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
int angka=9;
char square[*angka];

void printBoard(){
	for(int i=1;i<=9;i++){
		printf("[%c]", square[i-1]);
		if(i%3==0){
			printf("\n");
		}
		else{
			printf(" ");
		}
	}
}

int main(){
	//initiate
	char player1[30], player2[30];
	int finalScore[2]={0,0};
	
	// Name input
	printf("Welcome to Tic-Tac-Toe!\n--------------------\nPlease type Player 1 name: ");
	scanf("%[^\n]", &player1); getchar();
	printf("Please type Player 2 name: ");
	scanf("%[^\n]", &player2); getchar();
	system("cls");
	
	//tutorial
	puts("Welcome to Tic-Tac-Toe!");
	puts("Tic-Tac-Toe is a 2-player game where you must place X or O in 9 squares available.");
	puts("Each player takes turns to place their symbol (X or O). Player 1 is X, Player 2 is O.");
	puts("Whoever can place 3 of their symbols in a straight line (vertical, horizontal, or diagonal) wins the game!");
	puts("Remember that you can't overdraw a square that is already filled.");
	puts("[1] [2] [3]");
	puts("[4] [5] [6]");
	puts("[7] [8] [9]");
	puts("To place your symbol, just type the square number, and the program will put your symbol automatically.");
	printf("If you're ready, press any key to begin...");
	getch();
	system("cls");
	
	for(int loop=0;loop<5;){
		for(int i=0;i<9;i++){
			square[i]=32;
		}
		int winner=0;
		for(int i=0;i<10;i++){
			//print template
			printBoard();
			printf("--------------------\n");
			
			if(winner!=0||i==9){
				break;
			}
			
			if(i%2==0){
				printf("%s, please type the square number: ", player1);
			}
			else{
				printf("%s, please type the square number: ", player2);
			}
			
			//input square number & assign ke square
			for(int j=0;j<10;){
				int storage=0;
				char input=getch();
				printf("%c\n", input);
				storage=int(input)-49;
				if(!(storage>=0&&storage<=8)){
					printf("Please type the appropriate square number: ");
				}
				else if(square[storage]!=32){
					printf("This square is already filled. Please type another square number: ");
				}
				else{
					if(i%2==0){
						square[storage]='X';
					}
					else{
						square[storage]='O';
					}
					break;
				}
			}
			//detector pemenang
			if(square[0]==square[1]&&square[1]==square[2]&&square[0]==square[2]&&square[0]!=32){
				if(i%2==0){
					winner=1;
				}
				else{
					winner=2;
				}
			}
			else if(square[3]==square[4]&&square[4]==square[5]&&square[3]==square[5]&&square[3]!=32){
				if(i%2==0){
					winner=1;
				}
				else{
					winner=2;
				}
			}
			else if(square[6]==square[7]&&square[7]==square[8]&&square[6]==square[8]&&square[6]!=32){
				if(i%2==0){
					winner=1;
				}
				else{
					winner=2;
				}
			}
			else if(square[0]==square[3]&&square[3]==square[6]&&square[0]==square[6]&&square[0]!=32){
				if(i%2==0){
					winner=1;
				}
				else{
					winner=2;
				}
			}
			else if(square[1]==square[4]&&square[4]==square[7]&&square[1]==square[7]&&square[1]!=32){
				if(i%2==0){
					winner=1;
				}
				else{
					winner=2;
				}
			}
			else if(square[2]==square[5]&&square[5]==square[8]&&square[2]==square[8]&&square[2]!=32){
				if(i%2==0){
					winner=1;
				}
				else{
					winner=2;
				}
				
			}
			else if(square[0]==square[4]&&square[4]==square[8]&&square[0]==square[8]&&square[0]!=32){
				if(i%2==0){
					winner=1;
				}
				else{
					winner=2;
				}
			}
			else if(square[6]==square[4]&&square[4]==square[2]&&square[6]==square[2]&&square[6]!=32){
				if(i%2==0){
					winner=1;
				}
				else{
					winner=2;
				}
			}
			system("cls");
		}
		//announcement
		if(winner==1){
			printf("%s wins the game!\n", player1);
			finalScore[0]++;
		}
		else if(winner==2){
			printf("%s wins the game!\n", player2);
			finalScore[1]++;
		}
		else{
			printf("It's a tie!\n");
		}
		
		//scoreboard
		printf("--------------------\n");
		puts("Current score:");
		printf("%s %d - %d %s\n", player1, finalScore[0], finalScore[1], player2);
		
		//play again?
		printf("\nDo you want to play again? [Y/N]: ");
		char choice;
		for(int i=0;i<5;){
//			scanf("%c", &choice); getchar();
			choice=getch();
			printf("%c\n", choice);
			if(choice=='Y'||choice=='y'||choice=='N'||choice=='n'){
				break;
			}
			else{
				printf("Please type the appropriate character [Y/N]: ");
			}
		}
		if(choice=='N'||choice=='n'){
			system("cls");
			puts("Thank you for playing Tic-Tac-Toe! Have a great day!\n");
			printf("Press any key to exit...");
			getch();
			printf("\n");
			break;
		}
		
		//switching sides
		printf("Do you want to switch side? [Y/N]: ");
		char tukar;
		for(int i=0;i<5;){
//				scanf("%c", &tukar); getchar();
				tukar=getch();
				printf("%c\n", tukar);
				if(tukar=='Y'||tukar=='y'||tukar=='N'||tukar=='n'){
					break;
				}
				else{
					printf("Please type the appropriate character [Y/N]: ");
				}
			}
			if(tukar=='Y'||tukar=='y'){
				char backup[30];
				int scorebackup;
				for(int j=0;j<30;j++){
					backup[j]=player1[j];
				}
				scorebackup=finalScore[0];
				for(int j=0;j<30;j++){
					player1[j]=player2[j];
				}
				finalScore[0]=finalScore[1];
				for(int j=0;j<30;j++){
					player2[j]=backup[j];
				}
				finalScore[1]=scorebackup;
			}
		system("cls");
	}
	return 0;
}
