#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>

void nullGen(char *a){
	for(int i=0;i<20;i++){
		*a=0;
		a++;
	}
}

bool check(char *a){
	bool flag=1;
	for(int i=0;i<6;i++){
		if(i==5&&*a!=0){
//			printf("exceed");
			flag=0;
			break;
		}
		if(!(*a>=65&&*a<=90)&&i<5){
//			printf("wrong");
			flag=0;
			break;	
		}
		a++;
	}
	return flag;
}

void upper(char *a){
	while(*a!=0){
		if(*a>=97&&*a<=122){
			*a=int(*a)-32;
		}
		a++;
	}
}

void clrl(){
	printf("\033[A");
	printf("\033[2K");
}

void green(char *a){
	printf("\033[32m");
	printf("%c", *a);
	printf("\033[0m");
}

void yellow(char *a){
	printf("\033[33m");
	printf("%c", *a);
	printf("\033[0m");
}

int main(){
	system(" ");
	srand(time(0)*5);
	int winning;
	
	FILE *file=fopen("words.txt", "r");
    if(file==0){
        system("cls");
        puts("\"words.txt\" not found.");
        puts("Please put the \"words.txt\" file to the same directory as this program.");
        printf("Press any key to exit...");
        getch();
        exit(1);
    }
	
    for(int loop=0;1;){
        system("cls");
        char input[20];
        char password[5];
	    nullGen(password);
        fseek(file,0,SEEK_END);
        int line=rand()%((ftell(file)+2)/7)+1;
	    for(int i=0;i<6;i++){
		    printf("-----\n");
	    }
        printf("\n");
        for(int i=0;i<6;i++){
            fseek(file,(line-1)*7,0);
            fgets(password,6,file);
            upper(password);
            winning=0;
            printf("Please type the word: ");
            for(int j=0;j<5;){
                nullGen(input);
                scanf("%[^\n]", input); getchar();
                upper(input);
                if(strcmp(input,"SURREN")==0){
                    nullGen(input);
                    i=5;
                    break;
                }
                if(check(input)==0){
                    clrl();
                    printf("Try again. [5 letters]: ");
                }
                else{
                    break;
                }
            }
            printf("\033[H");
            for(int j=0;j<i;j++){
                printf("\n");
            }
            for(int j=0;j<5;j++){
                if(input[j]==password[j]){
                    green(&input[j]);
                    password[j]=32;
                    winning++;
                }
                else{
                    printf("\033[C");
                }
            }
            printf("\r");
            for(int j=0;j<5;j++){
                bool wrong=1;
                if(password[j]!=32){
                    for(int k=0;k<5;k++){
                        if(input[j]==password[k]){
                            wrong=0;
                            yellow(&input[j]);
                            password[k]=64;
                            break;
                        }
                    }
                    if(wrong==1){
                        printf("%c", input[j]);
                    }
                }
                else{
                    printf("\033[C");
                }
            }
            for(int j=0;j<7-i;j++){
                printf("\n");
            }
            printf("\033[2K");
            if(winning==5){
                printf("You win!");
                break;
            }	
        }
        if(winning!=5){
            fseek(file,(line-1)*7,0);
            fgets(password,6,file);
            upper(password);
            printf("The word is: %s", password);
        }
        printf("\n\n");
        printf("Do you want to play again? [Y/N]: ");
        char choice;
        while(true){
            choice=getch();
            printf("%c\n", choice);
            if(!(choice!='Y'&&choice!='y'&&choice!='N'&&choice!='n')){
                break;
            }
            else{
                printf("Please type the appropriate character [Y/N]: ");
            }
        }
        if(choice=='N'||choice=='n'){
            system("cls");
            puts("Thank you for playing Wordle! Have a great day!\n");
            printf("Press any key to exit...");
            getch();
            exit(0);
        }
    }
	return 0;
}
