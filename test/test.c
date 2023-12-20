#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define STAR '*'
#define SPACE ' '
const char* COLOR = { "COLOR" };
const char* CHANGE_DIR = { " <-> " };
#define STOP " STOP"

void print_card(int rows, int cols, char* value, char color);

void main()
{
	printf("%d", (-1 % 3));
}

void print_card(int rows, int cols, char* value, char color)
{
	int i, j;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1)
			{
				printf("%c", STAR);
			}
			else if(i == 2 && j == 2)
			{
				printf("%s", value);
				j = 6;
			}
			else if (i == 3 && j == 4)
			{
				printf("%c", color);
			}
			else
			{
				printf("%c", SPACE);
			}
		}
		printf("\n");
	}
}

/*
mallocs:
taki_players
taki_players.name
taki_players.cards
*/

/*char* value = -1;
switch (choice)
{
	case 1:
		value = NUM1;
		break;
	case 2:
		value = NUM2;
		break;
	case 3:
		value = NUM3;
		break;
	case 4:
		value = NUM4;
		break;
	case 5:
		value = NUM5;
		break;
	case 6:
		value = NUM6;
		break;
	case 7:
		value = NUM7;
		break;
	case 8:
		value = NUM8;
		break;
	case 9:
		value = NUM9;
		break;
	case 10:
		value = PLUS;
		break;
	case 11:
		value = STOP;
		break;
	case 12:
		value = CHANGE_DIR;
		break;
	case 13:
		value = COLOR;
		break;
	case 14:
		value = TAKI;
		break;
}*/

/*char color = ' ';
	switch (choice)
	{
		case 1:
			color = YELLOW;
			break;
		case 2:
			color = BLUE;
			break;
		case 3:
			color = RED;
			break;
		case 4:
			color = GREEN;
			break;
	}*/