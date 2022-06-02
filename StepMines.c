/* ***	Author *** */
/*
		Author : ¦¶®e¼x 
		Connection : s1090219@stu.ccsh.tp.edu.tw	 
*/

/* ***	journal *** */
/*
	05/29 : accomplish.c 		 
*/

/* ***	target *** */
/*
	05/29 : colorful-finished
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

/* ***	constant modification area *** */
#define MAP_LENGTH 10
#define MAP_WIDTH 10
#define BOMB_COUNT 10
#define TUTORIAL_COUNT 8						// fence length
#define GAME_COUNT 4							// fence length
 
// Map[][][0] = 1 : bomb check, MAP[][][1] = 1 : pace check
static int Map[MAP_WIDTH][MAP_LENGTH][2] = {0};			
static int UnKnown = MAP_LENGTH * MAP_WIDTH;

int Generate_Bomb(void)
{
	for(int i = 1; i <= BOMB_COUNT; ++i)			
	{
		// bomb's x, y aixs 
		int x = rand() % MAP_LENGTH;			// rnad() : MAX >= X >= 0, rand() % X : MAX > X >= 0
		int y = rand() % MAP_WIDTH;				// (Left Top, Left Top) = (0, 0)
		
		Map[x][y][0] = 1;
	}
	
	return 0;
}

int GameUpdate(void)
{
	system("cls");
	
	short out = 0;
	
	do
	{
		int x, y;
		printf("\033[32mPlease enter a set of coordinates you want to go : \033[m");
		scanf("%d %d", &x, &y);
		
		system("cls");
		
		x -= 1;
		y-= 1;
		
		if(x >= MAP_LENGTH || y >= MAP_WIDTH)	// out of Map	
		{
			printf("\033[31mError : Out of range...\033[m\n");
//			printf("Error : Out of range...\n");
			
			continue;
		}
		else
		{
			if(Map[x][y][1] == 0) Map[x][y][1] = 1;
			else
			{
				printf("\033[31mError : Already exists...\033[m\n");
				continue;
			}
			
			for(int row = 0; row < MAP_WIDTH; ++row)
			{
				if(row == 0)
				{
					for(int j = 0; j < GAME_COUNT * 10 + 1; ++j)
					{
						if(j == GAME_COUNT * 10) printf("\033[37m-\033[m\n");
						else printf("\033[37m-\033[m");
					} 	
				}
				
				for(int column = 0; column < MAP_LENGTH; ++column)
				{
					// step on bomb
					if(Map[row][column][0] == 1 && Map[row][column][1] == 1)
					{
						printf("\033[37m|\033[m");
						if(column == MAP_LENGTH - 1)
						{
							printf("\033[31m X \033[m");
							printf("\033[37m|\n\033[m");
						} 
						else printf("\033[31m X \033[m");
						
						out = 1;
					}
					// step on safe area
					else if(Map[row][column][0] == 0 && Map[row][column][1] == 1)
					{
						int count = 0;
						
						for(int i = -1; i <= 1; ++i)
						{
							for(int j = -1; j <= 1; ++j)
							{
								if(i == 0 && j == 0) continue;
								else if(Map[row + i][column + j][0] == 1) ++count;
							}
						}
						
						printf("\033[37m|\033[m");
						if(column == MAP_LENGTH - 1)
						{
							printf("\033[36m %d \033[m", count);
							printf("\033[37m|\n\033[m");
						}
						else printf("\033[36m %d \033[m", count);
						
						UnKnown -= 1;
					}
					// no pace
					else
					{
						printf("\033[37m|\033[m");
						if(column == MAP_LENGTH - 1)
						{
							printf("\033[35m ? \033[m");
							printf("\033[37m|\n\033[m");
						}
						else printf("\033[35m ? \033[m");
					}
				}
				
				for(int j = 0; j < GAME_COUNT * 10 + 1; ++j)
				{
					if(j == GAME_COUNT * 10) printf("\033[37m-\033[m\n");
					else printf("\033[37m-\033[m");
				}
				
				if(UnKnown == 0) return 2;
			}	
		}
//		system("pause");
	}while(out != 1);
	
	if(out == 1) return 1;
	else return 0;
}

int GameStart(void)
{
	printf("\033[37m\t\tGame Program Start...\033[m\n");
	
	// 1. summon bomb
	Generate_Bomb();
	
	// 2. make step
	// 3. check whether step bomb or not
	// 4. print historical pace & bomb count in ¤E®c®æ 
	if(GameUpdate() == 1) printf("\033[31m\n\t\tGAME OVER!\033[m\n\n");
	else if(GameUpdate() == 2) printf("\033[33m\n\t\tYOU WIN!\033[m\n\n");
	
	printf("\033[37m\t\tGame Program End...\033[m\n");
	
	return 0;
}

int Tutorial(void)
{
	printf("\033[37m\t\tTutorial Program Start...\033[m\n");
	
	printf("\033[32mMap coordinates : \033[m\n");
	
	for(int i = 0; i < 10 + 1; ++i)
	{
		if(i == 0)
		{
			for(int j = 0; j < TUTORIAL_COUNT * 10 + 1; ++j)
			{
				if(j == TUTORIAL_COUNT * 10) printf("\033[37m-\033[m\n");
				else printf("\033[37m-\033[m");
			} 	
		}
		else
		{
			for(int j = 0; j < 10; ++j)
			{
				if(j == 10 - 1)
				{
					printf("|");
					printf("\033[36m%2d * %d \033[m", i - 1, j);
					printf("|\n");
				}
				else
				{
					printf("|");
					printf("\033[36m%2d * %d \033[m", i - 1, j);
				}
			}
			for(int j = 0; j < TUTORIAL_COUNT * 10 + 1; ++j)
			{
				if(j == TUTORIAL_COUNT * 10) printf("\033[37m-\033[m\n");
				else printf("\033[37m-\033[m");
			}  
		}
	}
	
	printf("\033[33mExample 1. : the frist one element index is (0, 0)\033[m\n");
	printf("\033[33mExample 2. : (5, 9) means row 4 & column 8\033[m\n");
	printf("\033[33mExample 3. : (4, 8) means row 3 & column 7\033[m\n");
	system("pause");
	printf("\033[37m\t\tTutorial Program End...\033[m\n");
	
	GameStart();
	
	return 0;
}

int main()
{
	srand(time(NULL));
	system("color A");
		
	printf("\t\t\033[37mProgram Start...\033[m\n");
	printf("\033[32mMode choose --> Tutorial(1), GameStart(2) : \033[m");
	
	int choose = 0;
	scanf("%d", &choose);
	
	if(choose == 1) Tutorial();
	else GameStart();
	
	printf("\033[37m\t\tProgram End...\033[m\n");
	
	return 0;	
} 
