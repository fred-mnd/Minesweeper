#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>

void bombGenerator(int x, int y, char **board, int sizeX, int sizeY);
void surroundNumber(int x, int y, char **board, int sizeX, int sizeY);
void printBoard(char **board, bool **revealed, bool **isFlagged, bool isPlaying, bool win, int x, int y, int sizeX, int sizeY, int bombLeft, clock_t timer);
void reveal(int x, int y, char **board, bool **revealed, bool **isFlagged, int *opened, int sizeX, int sizeY);
long int timer(int opened, clock_t start);

void game(int bomb, int sizeX, int sizeY);
int selectDifficulty(int *sizeX, int *sizeY);
bool welcome();
void tutorial();

//----------------------------------------------------------------;

int main()
{
	system(" ");
	srand(time(0));
	if (welcome() == true)
		tutorial();
	int sizeX, sizeY;
	int bomb;
	do
	{
		bomb = selectDifficulty(&sizeX, &sizeY);
	} while (bomb <= 0);
	do
	{
		game(bomb, sizeX, sizeY);
		printf("\n");
		printf("Do you want to play again? [Y/N]: ");
		char choice;
		do
		{
			choice = tolower(getch());
			printf("%c\n", choice);
			if (choice != 'y' && choice != 'n')
			{
				printf("Please type the appropriate input [Y/N]: ");
			}
			else
				break;
		} while (true);
		if (choice == 'n')
		{
			system("cls");
			puts("Thank you for playing Minesweeper! Have a great day!\n");
			printf("Press any key to exit...");
			getch();
			return 0;
		}
		else
		{
			printf("Do you want to change difficulty? [Y/N]: ");
			do
			{
				choice = tolower(getch());
				if (choice != 'y' && choice != 'n')
				{
					printf("%c\n", choice);
					printf("Please type the appropriate input [Y/N]: ");
				}
				else
					break;
			} while (true);
		}
		if (choice == 'y')
		{
			do
			{
				bomb = selectDifficulty(&sizeX, &sizeY);
			} while (bomb <= 0);
		}
	} while (true);
	return 0;
}

//-----------------------------------------------------------------------------;

void tutorial()
{
	printf("\033[?25l");
	int page = 1, maxPage = 5;
	do
	{
		system("cls");
		if (page > 1)
			printf("<- A");
		printf("\t\tPage %d-%d\t\t", page, maxPage);
		if (page < maxPage)
			printf("D ->");
		printf("\t\t\tEnter : Exit Tutorial\n\n");
		if (page == 1)
		{
			puts("Welcome to Minesweeper!\n");
			puts("Minesweeper is a simple game which features grids and mines or 'bombs' spread across the board. ");
			puts("To win the game, you must clear all the grids without detonating the bombs,");
			puts("or in simpler words, open all squares except the bomb squares.");
		}
		else if (page == 2)
		{
			puts("Controls\n");
			puts(" -------");
			for (int i = 0; i < 3; i++)
			{
				if (i == 0)
					printf("| \033[94m-\033[39m - - |\n");
				else
					puts("| - - - |");
			}
			puts(" -------\n");
			puts("The grid or 'dash' in blue is the cursor.");
			puts("You can move the cursor by pressing W, A, S, or D to move it up, left, down, or right respectively.");
			puts("After moving the cursor, you can press Spacebar or F to either open or mark the grid.");
		}
		else if (page == 3)
		{
			puts("Actions\n");
			puts(" -------");
			for (int i = 0; i < 3; i++)
			{
				if (i == 0)
					printf("| - \033[94m-\033[39m - |\n");
				else if (i == 1)
					printf("| 1 \033[33mF\033[39m - |\n");
				else
					puts("| - - - |");
			}
			puts(" -------\n");
			puts("As stated earlier, you can perform 2 actions on a grid:");
			puts("   1. Open (Spacebar)");
			puts("      Opening a grid will show its value.");
			puts("      The value is really important as it'll guide you through the game.\n");
			puts("   2. Mark (F)");
			puts("      Marking the grid will mark it as flagged, or '\033[33mF\033[39m' on the board.");
			puts("      Flagged grid can't be opened, unless you unmark it, by pressing F again.");
		}
		else if (page == 4)
		{
			puts("Grid Values\n");
			puts(" -------");
			for (int i = 0; i < 3; i++)
			{
				if (i == 0)
					printf("| \033[94m-\033[39m 1 1 |\n");
				else if (i == 1)
					printf("|   1 \033[31mB\033[39m |\n");
				else
					puts("| - - - |");
			}
			puts(" -------\n");
			puts("Each grid has their own value, which can be categorized by 3 indicators:");
			puts("   1. Bomb (\033[31mB\033[39m)");
			puts("      This grid is the grid you have to avoid.");
			puts("      Don't open this grid or you'll lose the game!\n");
			puts("   2. Numbers (1-9)");
			puts("      This grid indicates the number of bombs around it.");
			puts("      For example, if the value is 1, it means that 1 of the 8 grids around it has a bomb.");
			puts("      This grid is probably the most important one, as it gives you clues about where the bombs are.\n");
			puts("   3. Empty grid ( )");
			puts("      It means that the grid is completely safe, no bombs are nearby.");
			puts("      This grid is pretty special, because if you open the empty grid, it will open all the grids around it,");
			puts("      until it opens the number grid.");
		}
		else if (page == 5)
		{
			puts("Winning / Losing\n");
			puts("You win if you open all the grids while securing the bomb grids.");
			puts("Otherwise, you lose if you open a bomb grid.\n");
			puts("So, don't be careless, mind your surroundings, and have fun!");
		}
		char action = tolower(getch());
		if (action == 'a' && page > 1)
			page--;
		else if (action == 'd' && page < maxPage)
			page++;
		else if (action == '\r')
		{
			printf("\033[?25h");
			return;
		}
	} while (true);
}

bool welcome()
{
	system("cls");
	puts("Welcome to Minesweeper!\n");
	puts("For better experience, turn this window to fullscreen.\n");
	printf("Do you want to read the tutorial? [Y/N]: ");
	char choice;
	do
	{
		choice = tolower(getch());
		if (choice != 'y' && choice != 'n')
		{
			printf("%c\n", choice);
			printf("Please type the appropriate input [Y/N]: ");
		}
		else
		{
			if (choice == 'y')
				return true;
			else
				return false;
		}
	} while (true);
}

int selectDifficulty(int *sizeX, int *sizeY)
{
	system("cls");
	puts("Select Difficulty");
	puts("1. Easy [10 bombs, 10x10]");
	puts("2. Normal [40 bombs, 15x15]");
	puts("3. Hard [80 bombs, 20x20]");
	puts("4. Custom");
	printf(">> ");
	char userInput;
	do
	{
		userInput = getch();
		if (userInput < '1' || userInput > '4')
		{
			printf("%c\n", userInput);
			printf("Please type the appropriate input: ");
		}
		else
			break;
	} while (true);
	if (userInput == '1')
	{
		*sizeX = *sizeY = 10;
		return 10;
	}
	else if (userInput == '2')
	{
		*sizeX = *sizeY = 15;
		return 40;
	}
	else if (userInput == '3')
	{
		*sizeX = *sizeY = 20;
		return 80;
	}
	else if (userInput == '4')
	{
		system("cls");
		puts("Type 0 to return.");
		printf("\nPlease type the board width [10-30]: ");
		int choice;
		do
		{
			scanf("%d", &choice);
			if (choice == 0)
				return 0;
			else if (choice < 10 || choice > 30)
			{
				printf("Please type the appropriate input: ");
			}
			else
			{
				*sizeX = choice;
				break;
			}
		} while (true);
		printf("\nPlease type the board height [10-30]: ");
		do
		{
			scanf("%d", &choice);
			if (choice == 0)
				return 0;
			else if (choice < 10 || choice > 30)
			{
				printf("Please type the appropriate input: ");
			}
			else
			{
				*sizeY = choice;
				break;
			}
		} while (true);
		int maxBomb = (*sizeX) * (*sizeY) / 10 * 3;
		printf("\nPlease type the amount of bombs [1 - %d]: ", maxBomb);
		do
		{
			scanf("%d", &choice);
			if (choice == 0)
				return 0;
			else if (choice < 1 || choice > maxBomb)
			{
				printf("Please type the appropriate input: ");
			}
			else
				return choice;
		} while (true);
	}
}

void game(int bomb, int sizeX, int sizeY)
{
	system("cls");
	printf("\033[?25l");
	char **board = (char **)malloc(sizeof(char *) * sizeY);
	bool **revealed = (bool **)malloc(sizeof(bool *) * sizeY);
	bool **isFlagged = (bool **)malloc(sizeof(bool *) * sizeY);
	for (int i = 0; i < sizeY; i++)
	{
		board[i] = (char *)malloc(sizeof(char) * sizeX);
		revealed[i] = (bool *)malloc(sizeof(bool) * sizeX);
		isFlagged[i] = (bool *)malloc(sizeof(bool) * sizeX);
		for (int j = 0; j < sizeX; j++)
		{
			board[i][j] = ' ';
			revealed[i][j] = false;
			isFlagged[i][j] = false;
		}
	}
	bool win = true;
	int opened = 0;
	int bombLeft = bomb;
	int xChoice = 0, yChoice = 0;
	bool kb = 1;
	clock_t start, delay = 1, time;
	do
	{
		time = timer(opened, start);
		if (kb == 1 || time >= delay)
		{
			if(time >= delay) delay ++;
			printBoard(board, revealed, isFlagged, true, win, xChoice, yChoice, sizeX, sizeY, bombLeft, time);
			kb = 0;
		}
		if (kbhit())
		{
			char temp = tolower(getch());
			if (temp == 27)
			{
				clock_t paused = clock();
				printf("\033[0JPAUSED. Press any key to continue, or Esc to surrender.\r");
				temp = tolower(getch());
				start += clock() - paused;
				if (temp == 27)
				{
					win = false;
					break;
				}
			}
			printf("\033[0J");
			if (temp == ' ' || temp == 'f')
			{
				if (revealed[yChoice][xChoice] == true)
					printf("The square you selected is already opened.");
				else if (temp == ' ')
				{
					if (isFlagged[yChoice][xChoice] == true) printf("The square you selected is flagged.");
					else{
						if (opened <= 0)
						{
							for (int i = 0; i < bomb; i++)
							{
								int x, y;
								do
								{
									x = rand() % sizeX;
									y = rand() % sizeY;
								} while (board[y][x] == 'B' || (x >= xChoice - 1 && x <= xChoice + 1 && y >= yChoice - 1 && y <= yChoice + 1));
								bombGenerator(x, y, board, sizeX, sizeY);
							}
							start = clock();
						}
						reveal(xChoice, yChoice, board, revealed, isFlagged, &opened, sizeX, sizeY);
						if (board[yChoice][xChoice] == 'B')
						{
							win = false;
							break;
						}
					}
				}
				else if (temp == 'f')
				{
					if (isFlagged[yChoice][xChoice] == false)
					{
						isFlagged[yChoice][xChoice] = true;
						bombLeft--;
					}
					else
					{
						isFlagged[yChoice][xChoice] = false;
						bombLeft++;
					}
				}
			}
			else if ((temp == 'w') && yChoice > 0)
				yChoice--;
			else if ((temp == 's') && yChoice < sizeY - 1)
				yChoice++;
			else if ((temp == 'a') && xChoice > 0)
				xChoice--;
			else if ((temp == 'd') && xChoice < sizeX - 1)
				xChoice++;
			else if (temp == 'r')
				system("cls");
				
			kb = 1;
		}
	} while (sizeX * sizeY - bomb > opened);
	printBoard(board, revealed, isFlagged, false, win, 0, 0, sizeX, sizeY, 0, time);
	printf("\033[?25h\033[J");

	for(int i=0;i<sizeY;i++){
		free(board[i]);
		free(revealed[i]);
		free(isFlagged[i]);
	}
	free(board);
	free(revealed);
	free(isFlagged);
}

void bombGenerator(int x, int y, char **board, int sizeX, int sizeY)
{
	board[y][x] = 'B';
	surroundNumber(x, y + 1, board, sizeX, sizeY);
	surroundNumber(x + 1, y + 1, board, sizeX, sizeY);
	surroundNumber(x + 1, y, board, sizeX, sizeY);
	surroundNumber(x + 1, y - 1, board, sizeX, sizeY);
	surroundNumber(x, y - 1, board, sizeX, sizeY);
	surroundNumber(x - 1, y - 1, board, sizeX, sizeY);
	surroundNumber(x - 1, y, board, sizeX, sizeY);
	surroundNumber(x - 1, y + 1, board, sizeX, sizeY);
}
void surroundNumber(int x, int y, char **board, int sizeX, int sizeY)
{
	if (x < 0 || x > sizeX - 1 || y < 0 || y > sizeY - 1)
		return;
	else if (board[y][x] == ' ')
		board[y][x] = '1';
	else if (board[y][x] >= '1' && board[y][x] <= '9')
		board[y][x]++;
}

void printBoard(char **board, bool **revealed, bool **isFlagged, bool isPlaying, bool win, int x, int y, int sizeX, int sizeY, int bombLeft, clock_t timer)
{
	printf("\033[H");
	printf(" -");
	for (int i = 0; i < sizeX; i++)
	{
		printf("--");
	}
	printf("\n");
	for (int i = 0; i < sizeY; i++)
	{
		printf("| ", i + 1);
		for (int j = 0; j < sizeX; j++)
		{
			if (isPlaying == true)
			{
				bool same = 0;
				if (i == y && j == x)
				{
					printf("\033[94m");
					same = 1;
				}
				if (isFlagged[i][j] == true)
				{
					if (same == 1)
						printf("F ");
					else
						printf("\033[33mF ");
				}
				else if (revealed[i][j] == true)
				{
					if (same == 1 && board[i][j] == ' ')
						printf(". ");
					else
						printf("%c ", board[i][j]);
				}
				else
					printf("- ");
			}
			else if (win == true)
			{
				if (isFlagged[i][j] == true)
				{
					printf("\033[32mF ");
				}
				else if (board[i][j] == 'B')
				{
					printf("\033[32mB ");
				}
				else if (revealed[i][j] == true)
					printf("%c ", board[i][j]);
				else
					printf("- ");
			}
			else
			{
				if (isFlagged[i][j] == true)
				{
					if (board[i][j] == 'B')
						printf("\033[32mF ");
					else
						printf("\033[33mX ");
				}
				else if (board[i][j] == 'B')
				{
					printf("\033[31mB ");
				}
				else if (revealed[i][j] == true)
					printf("%c ", board[i][j]);
				else
					printf("- ");
			}
			printf("\033[39m");
		}
		printf("|");
		if (isPlaying == true)
		{
			if (i == 0)
				printf("\t\tControls:");
			else if (i == 2)
				printf("\t\tW : Up");
			else if (i == 3)
				printf("\t\tA : Left");
			else if (i == 4)
				printf("\t\tS : Down");
			else if (i == 5)
				printf("\t\tD : Right");
			else if (i == 6)
				printf("\t\tF : Flag");
			else if (i == 7)
				printf("\t\tSpace : Open");
			else if (i == 8)
				printf("\t\tR : Refresh UI");
			else if (i == 9)
				printf("\t\tEsc : Pause");
		}
		else
			printf("\033[K");
		printf("\n");
	}
	printf(" -");
	for (int i = 0; i < sizeX; i++)
	{
		printf("--");
	}
	printf("\n\n");
	printf("\033[2K");

	if (isPlaying == 1)
		printf("Bomb(s) left: %d\n", bombLeft);
	else if (win == 1)
		printf("You Win!\n");
	else
		printf("Game Over!\n");
	printf("\n\033[2KTime elapsed: ");
	// if(elapsed/60>0){
	// 	printf("%d minute(s) ", elapsed/60);
	// 	if(elapsed%60!=0) printf("%d second(s)", elapsed%60);
	// }
	// else printf("%d second(s)", elapsed);
	printf("%d:%02d\n", timer / 60, timer % 60);
}

void reveal(int x, int y, char **board, bool **revealed, bool **isFlagged, int *opened, int sizeX, int sizeY)
{
	if (x < 0 || x > sizeX - 1 || y < 0 || y > sizeY - 1 || revealed[y][x] == true)
		return;
	if (isFlagged[y][x] == false)
	{
		revealed[y][x] = true;
		(*opened)++;
	}
	if (board[y][x] != ' ')
	{
		return;
	}
	reveal(x + 1, y, board, revealed, isFlagged, opened, sizeX, sizeY);
	reveal(x + 1, y + 1, board, revealed, isFlagged, opened, sizeX, sizeY);
	reveal(x, y + 1, board, revealed, isFlagged, opened, sizeX, sizeY);
	reveal(x - 1, y + 1, board, revealed, isFlagged, opened, sizeX, sizeY);
	reveal(x - 1, y, board, revealed, isFlagged, opened, sizeX, sizeY);
	reveal(x - 1, y - 1, board, revealed, isFlagged, opened, sizeX, sizeY);
	reveal(x, y - 1, board, revealed, isFlagged, opened, sizeX, sizeY);
	reveal(x + 1, y - 1, board, revealed, isFlagged, opened, sizeX, sizeY);
}

clock_t timer(int opened, clock_t start)
{
	if (opened <= 0)
		return 0;
	else
		return (clock() - start) / CLOCKS_PER_SEC;
}