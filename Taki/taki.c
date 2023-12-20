#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define LINE1 12
#define LINE2 11
#define ROWS 6
#define COLS 9
#define STAR '*'
#define SPACE ' '
#define UNDER_LINE '_'
#define HORZ_LINE '|'
#define UNDER_SIZE 18 
#define MAX_NAME 21
#define STARTING_HAND 4
#define MIN_PLAERS 2
#define VALUE_LENGTH 6
#define COLOR_LENGTH 6
#define YELLOW 'Y'
#define BLUE 'B'
#define GREEN 'G'
#define	RED 'R'
#define COLOR "COLOR"
#define TAKI " TAKI"
#define STOP " STOP"
#define CHANGE_DIR " <-> "
#define PLUS "  +  "
#define NUM1 "  1  "
#define NUM2 "  2  "
#define NUM3 "  3  "
#define NUM4 "  4  "
#define NUM5 "  5  "
#define NUM6 "  6  "
#define NUM7 "  7  "
#define NUM8 "  8  "
#define NUM9 "  9  "
#define STATS_PARAMETERS 14
#define FIRST_DIR 1
#define SECOND_DIR -1

const char VALUE[STATS_PARAMETERS][VALUE_LENGTH] = { PLUS, CHANGE_DIR, STOP, TAKI, COLOR, NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7, NUM8, NUM9 };
const char COLORS[COLOR_LENGTH] = { YELLOW, RED, BLUE, GREEN, SPACE };

struct Card {
	int rows;
	int cols;
	char value[VALUE_LENGTH];
	char color;
};
typedef struct Card card;

struct Player {
	char* name;
	int num_of_cards;
	card* cards;
	int phys_size;
};
typedef struct Player player;

struct Stats {
	char value[VALUE_LENGTH];
	int quan;
};
typedef struct Stats card_stats;

card* arr_realloc(card* arr, int size, int new_size);
void print_welcome();
void print_line(char c, int n);
int get_num_of_players();
player* get_names_of_players(player* players, int num);
char* get_name(char* name, int num);
player* get_cards(player* players, int num_of_players, card_stats stats[], int stats_size);
card get_random_card(card one_card, card_stats stats[], int stats_size);
card center_in_beginning(card one_card, card_stats stats[], int stats_size);
char* get_value(card_stats stats[], int stats_size);
char* get_value_for_beginning(card_stats stats[], int stats_size);
char get_color();
void game_of_taki(player* players, int num_of_players, card center, card_stats stats[], int stats_size);
int check_for_negative(int num, int to_add);
void turn(player* current, card* center, bool* direction, bool* stop, bool* plus, bool* taki, bool* continue_taki, card_stats stats[], int stats_size);
void print_card(int rows, int cols, char* value, char color);
void add_value_to_stats(char* value, card_stats stats[], int stats_size);
void restars_stats(card_stats init[], int size);
void swap_value(char* s1, char* s2);
bool is_there_winner(int num_of_cards);
int player_choice(int max);
bool run_until_valid(card* the_card, card* center, int num_of_cards, int* card_lose, bool* continue_taki);
bool is_choice_valid(card* the_card, card* center, bool* continue_taki);
void swap_cards(card* card_1, card* card_2);
void special_cards(card* the_card, bool* direction, bool* stop, bool* plus, bool* taki, bool* continue_taki);
void is_color(card* the_card, bool* continue_taki);
bool is_change_dir(card* the_card);
bool is_stop(card* the_card);
bool is_plus (card* the_card);
bool is_taki(card* the_card);
int choose_color();
void merge_sort_stats(card_stats stats[], int stats_size);
void merge(card_stats arr1[], int size1, card_stats arr2[], int size2, card_stats res[]);
void copy_stats_arr(card_stats dest[], card_stats src[], int size);
void print_stats(card_stats stats[], int stats_size);
void free_all(player taki[], int size);

void main()
{
	/*
	This program displays the game of taki between a chosen number of players.
	It guides the plyers to play according to the rules and after one wins it
	prints the statistics of the card appeared in the game.
	*/
	srand(time(NULL));
	int i;
	player* taki_players;
	card center;
	card_stats stats[STATS_PARAMETERS];
	restars_stats(stats, STATS_PARAMETERS);
	center.rows = 0;
	center.cols = 0;
	strcpy(center.value, NUM1);
	center.color = '0';
	print_welcome();
	int num_of_players = get_num_of_players();
	taki_players = (player*)malloc(num_of_players * sizeof(player));
	if (taki_players == NULL)
	{
		printf("Error with memory allocation!\n");
		exit(1);
	}
	taki_players = get_names_of_players(taki_players, num_of_players);
	taki_players = get_cards(taki_players, num_of_players, stats, STATS_PARAMETERS);
	center = center_in_beginning(center, stats, STATS_PARAMETERS);
	game_of_taki(taki_players, num_of_players, center, stats, STATS_PARAMETERS);
	merge_sort_stats(stats, STATS_PARAMETERS);
	print_stats(stats, STATS_PARAMETERS);
	free_all(taki_players, num_of_players);
}

card* arr_realloc(card* arr, int size, int new_size)
{
	/*
	This function gets an array of integers, its size and a new one and
	changes the size to the new one
	*/
	int i;
	card* new_arr = (card*)malloc(new_size * sizeof(card));
	if (new_arr == NULL)
	{
		return NULL;
	}
	else
	{
		for (i = 0; i < size && i < new_size; i++)
		{
			*(new_arr + i) = *(arr + i);
		}
		free(arr);
	}
	return new_arr;
}

void print_welcome()
{
	/*
	This function prints a welcome announcement
	*/
	print_line(STAR, LINE1);
	printf(" Welcome to TAKI game !!! ");
	print_line(STAR, LINE2);
	printf("\n");
}

void print_line(char c, int n)
{
	/*
	This function gets a char and a number and prints a line
	of this char number times
	*/
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%c", c);
	}
}

int get_num_of_players()
{
	/*
	This function gets the number of players in the game
	*/
	int num_of_players;
	printf("Please enter  the number of players:\n");
	scanf("%d", &num_of_players);
	return num_of_players;
}

player* get_names_of_players(player* players, int num)
{
	/*
	This function gets the name of each player in the game and return them
	*/
	int i;
	for (i = 0; i < num; i++)
	{
		players[i].name = get_name(players[i].name, i + 1);
	}
	return players;
}

char* get_name(char* name, int num)
{
	/*
	This function creates a string and gets a name of a player. It returns
	the name
	*/
	name = (char*)malloc(MAX_NAME * sizeof(char));
	if (name == NULL)
	{
		printf("Error with memory allocation!\n");
		exit(1);
	}
	printf("Please enter first name of player #%d\n", num);
	scanf("%s", name);
	return name;
}

player* get_cards(player* players, int num_of_players, card_stats stats[], int stats_size)
{
	/*
	This function gets 4 starting cards of each player
	*/
	int i, j;
	for (i = 0; i < num_of_players; i++)
	{
		players[i].num_of_cards = STARTING_HAND;
		players[i].phys_size = STARTING_HAND;
		players[i].cards = (card*)malloc(players[i].num_of_cards * sizeof(card));
		if (players[i].cards == NULL)
		{
			printf("Error with memory allocation!\n");
			exit(1);
		}
		for (j = 0; j < players[i].num_of_cards; j++)
		{
			players[i].cards[j] = get_random_card(players[i].cards[j], stats, stats_size);
		}
	}
	return players;
}

card get_random_card(card one_card, card_stats stats[], int stats_size)
{
	/*
	This function gets the parameters of a card and returns them
	*/
	one_card.rows = ROWS;
	one_card.cols = COLS;
	strcpy(one_card.value, get_value(stats, stats_size));
	one_card.color = get_color();
	if (strcmp(one_card.value, COLOR) == 0)
	{
		one_card.color = SPACE;
	}
	return one_card;
}

card center_in_beginning(card one_card, card_stats stats[], int stats_size)
{
	/*
	This function chooses randomaly card for the center without special cards
	*/
	one_card.rows = ROWS;
	one_card.cols = COLS;
	strcpy(one_card.value, get_value_for_beginning(stats, stats_size));
	one_card.color = get_color();
	if (strcmp(one_card.value, COLOR) == 0)
	{
		one_card.color = SPACE;
	}
	return one_card;
}

char* get_value(card_stats stats[], int stats_size)
{
	/*
	This function returns rendomaly one of 14 possible values
	for a card
	*/
	int choice = rand() % 14;
	char* value = VALUE[choice];
	add_value_to_stats(value, stats, stats_size);
	return value;
}

char* get_value_for_beginning(card_stats stats[], int stats_size)
{
	/*
	This function returns rendomaly one of 9 possible values
	for a card
	*/
	int choice = rand() % 9;
	char* value = VALUE[choice + 5];
	add_value_to_stats(value, stats, stats_size);
	return value;
}

char get_color()
{
	/*
	This function returns one of 4 possible values for a card's color
	*/
	int choice = rand() %4;
	char color = COLORS[choice];
	return color;
}

void game_of_taki(player* players, int num_of_players, card center, card_stats stats[], int stats_size)
{
	/*
	This function gets the players data, their size and the center card's
	data and begins to run the game of taki
	*/
	int turns_counter = 0;
	bool winner = false;
	int i = 0, direction = FIRST_DIR;
	bool change_direction = false;
	bool stop = false;
	bool plus = false;
	bool taki = false;
	bool continue_taki = false;
	bool after_plus = false;
	bool after_stop = false;
	while (winner == false || after_plus == true || after_stop == true)
	{
		if ((after_plus == true || after_stop == true) && players->num_of_cards == 1)
		{
			players->num_of_cards = 0;
		}
		after_plus = false;
		after_stop = false;
		i = check_for_negative(i, num_of_players);
		turn(&players[i % num_of_players], &center, &change_direction, &stop, &plus, &taki, &continue_taki, stats, stats_size);
		winner = is_there_winner(players[i % num_of_players].num_of_cards);
		if (change_direction == true && continue_taki == false)
		{
			direction = direction * SECOND_DIR;
			change_direction = false;
		}
		else if (stop == true && continue_taki == false)
		{
			i = i + direction;
			stop = false;
			if (num_of_players == MIN_PLAERS)
			{
				after_stop = true;
			}
		}
		else if (plus == true && continue_taki == false)
		{
			i = i - direction;
			plus = false;
			after_plus = true;
		}
		else if (taki == true)
		{
			continue_taki = true;
			while(continue_taki == true && winner == false)
			{
				turn(&players[i % num_of_players], &center, &change_direction, &stop, &plus, &taki, &continue_taki, stats, stats_size);
				winner = is_there_winner(players[i % num_of_players].num_of_cards);
			}
			continue_taki = false;
		}
		i = i + direction;
	}
	i = check_for_negative(i, num_of_players);
	printf("\nThe winner is... %s! Congratulations!\n\n", players[i % num_of_players].name);
}

void print_card(int rows, int cols, char* value, char color)
{
	/*
	This function gets parameters of a taki card and prints it. It also counts the
	value printed.
	*/
	int i, j;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1)
			{
				printf("%c", STAR);
			}
			else if (i == 2 && j == 2)
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

void add_value_to_stats(char* value, card_stats stats[], int stats_size)
{
	/*
	This fucntion counts the values appears in the game.
	*/
	int i;
	for (i = 0; i < stats_size; i++)
	{
		if (strcmp(value, stats[i].value) == 0)
		{
			stats[i].quan++;
		}
	}
}

int check_for_negative(int num, int to_add)
{
	/*
	This function prevents the counter of turns to become negative. If it is
	it adds the counter the number of players to keep the modulo.
	*/
	if (num < 0)
	{
		num = num + to_add;
	}
	return num;
}

void turn(player* current, card* center, bool* direction, bool* stop, bool* plus, bool* taki, bool* continue_taki, card_stats stats[], int stats_size)
{
	/*
	This function gets the current turn player's data and the center card data.
	It runs all the possible results to his turn;
	*/
	int i, the_player_choice, card_lose, color_chose;
	printf("Upper card:\n");
	print_card(center->rows, center->cols, center->value, center->color);
	printf("\n%s's turn:\n\n", current->name);
	for (i = 0; i < current->num_of_cards; i++)
	{
		printf("Card #%d\n", i + 1);
		print_card(current->cards[i].rows, current->cards[i].cols, current->cards[i].value, current->cards[i].color);
		printf("\n");
	}
	bool to_draw = run_until_valid(current->cards, center, current->num_of_cards, &card_lose, continue_taki);
	if (to_draw == false)
	{
		// delete card
		special_cards(center, direction, stop, plus, taki, continue_taki);
		swap_cards(&current->cards[card_lose - 1], &current->cards[current->num_of_cards - 1]);
		current->num_of_cards--;
	}
	else
	{
		//add card
		if (*continue_taki == false)
		{
			if (current->num_of_cards == current->phys_size)
			{
				card* temp = arr_realloc(current->cards, current->num_of_cards, current->num_of_cards * 2);
				current->cards = temp;
				current->phys_size = current->phys_size * 2;
			}
			current->num_of_cards++;
			current->cards[current->num_of_cards - 1] = get_random_card(current->cards[current->num_of_cards], stats, stats_size);
		}
		*continue_taki = false;
	}
	
}

void restars_stats(card_stats init[], int size)
{
	/*
	This function fills the array of the stats with an initial values
	*/
	int i;
	for (i = 0; i < size; i++)
	{
		init[i].quan = 0;
		strcpy(init[i].value, VALUE[i]);
	}
}

void swap_value(char* s1, char* s2)
{
	/*
	This function gets 2 strings from an array and swap them
	*/
	char temp[VALUE_LENGTH];
	strcpy(temp, s1);
	strcpy(s1, s2);
	strcpy(s2, temp);
}

bool is_there_winner(int num_of_cards)
{
	/*
	This function gets the players's data and checks if someone won the game
	(has no cards). It returns true if there is winner and false otherwise.
	*/
	if (num_of_cards == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int player_choice(int max)
{
	/*
	This function gets the number of cards in the player's hand,
	gets the number of card he chooses to put in the middle and
	returns it.
	*/
	int choice;
	printf("Please enter 0 if you want to take a card from the deck\n");
	printf("or 1-%d if you want to put one of your cards in the middle: ", max);
	scanf("%d", &choice);
	return choice;
}

bool run_until_valid(card* the_card, card* center, int num_of_cards, int* card_lose, bool* continue_taki)
{
	bool check = false;
	int the_player_choice;
	while (!check)
	{
		the_player_choice = player_choice(num_of_cards);
		if (the_player_choice == 0)
		{
			return true;
		}
		else
		{
			if(the_player_choice > num_of_cards)
			{
				check = false;
			}
			else
			{
				check = is_choice_valid(the_card + the_player_choice - 1, center, continue_taki);
			}
			if (check == false)
			{
				printf("Invalid card! Try again.\n");
			}
		}
	}
	*card_lose = the_player_choice;
	*center = *(the_card + the_player_choice - 1);
	return false;
}

bool is_choice_valid(card* the_card, card* center, bool* continue_taki)
{
	/*
	This function gets the data of the card in the middle and the card
	the player chooses to play. It returns true for a valid choice
	and false otherwise.
	*/
	bool res = false;
	if (strcmp(the_card->value, center->value) == 0 && *continue_taki == false )
	{
	res = true;
	}
	else if (the_card->color == center->color)
	{
	res = true;
	}
	else if (strcmp(the_card->value, "COLOR") == 0)
	{
		res = true;
	}
	return res;
}

void swap_cards(card* card_1, card* card_2)
{
	card temp;
	temp = *card_1;
	*card_1 = *card_2;
	*card_2 = temp;
}

void special_cards(card* the_card, bool* direction, bool* stop, bool* plus, bool* taki, bool* continue_taki)
{
	/*
	This function gets a card played in the game and checks if a special
	card was played. It returns true for the parameter of the same card
	if it was.
	*/
	//color
	is_color(the_card, continue_taki);
	//change dir
	*direction = is_change_dir(the_card);
	//stop
	*stop = is_stop(the_card);
	//plus
	*plus = is_plus(the_card);
	//taki
	*taki = is_taki(the_card);

}

void is_color(card* the_card, bool* continue_taki)
{
	/*
	This function checks if the card in the middle is color, asks the player
	to which color he wants to change and adds this color to the card.
	*/
	int color_chose;
	if (strcmp(the_card->value, COLOR) == 0)
	{
		color_chose = choose_color();
		the_card->color = COLORS[color_chose - 1];
		*continue_taki = false;
	}
}

int choose_color()
{
	/*
	This function gets from the player the color he chooses and returns it.
	*/
	int choose;
	printf("Please enter your color choice:\n");
	printf("1 - Yellow\n");
	printf("2 - Red\n");
	printf("3 - Blue\n");
	printf("4 - Green\n");
	scanf("%d", &choose);
	while (choose < 1 || choose > 4)
	{
		printf("Invalid color! Try again\n");
		choose = choose_color();
	}
	return choose;
}

bool is_change_dir(card* the_card)
{
	/*
	This function checks if the diretion of the turns change and returns true
	if it is.
	*/
	bool res = false;
	if (strcmp(the_card->value, CHANGE_DIR) == 0)
	{
		res = true;
	}
	return res;
}

bool is_stop(card* the_card)
{
	/*
	This function checks if a card's value is STOP and return true if it is,
	otherwise it returns false;
	*/
	bool res = false;
	if (strcmp(the_card->value, STOP) == 0)
	{
		res = true;
	}
	return res;
}

bool is_plus(card* the_card)
{
	/*
	This function checks if a card's value is STOP and return true if it is,
	otherwise it returns false;
	*/
	bool res = false;
	if (strcmp(the_card->value, PLUS) == 0)
	{
		res = true;
	}
	return res;
}

bool is_taki(card* the_card)
{
	/*
	This function checks if a card's value is STOP and return true if it is,
	otherwise it returns false;
	*/
	bool res = false;
	if (strcmp(the_card->value, TAKI) == 0)
	{
		res = true;
	}
	return res;
}

void merge_sort_stats(card_stats stats[], int stats_size)
{
	/*
	This function sorts an array of card_stats with merge sort according
	to the quan field. It gets the array and it's size.
	*/
	card_stats* temp;
	if (stats_size <= 1)
	{
		return;
	}
	else
	{
		merge_sort_stats(stats, stats_size / 2);
		merge_sort_stats(stats + stats_size / 2, stats_size - stats_size / 2);

		temp = (card_stats*)malloc(sizeof(card_stats) * stats_size);
		if (temp == NULL)
		{
			printf("Error with memory allocation!\n");
			exit(1);
		}
		else
		{
			merge(stats, stats_size / 2, stats + stats_size / 2, stats_size - stats_size / 2, temp);
			copy_stats_arr(stats, temp, stats_size);
			free(temp);
		}
	}
}

void merge(card_stats arr1[], int size1, card_stats arr2[], int size2, card_stats res[])
{
	/*
	This function gets 2 sorted arrays of card_stats and merge to become
	sorted according to the quan field.
	*/
	int ind1 = 0, ind2 = 0, ind_res = 0;

	while ((ind1 < size1) && (ind2 < size2))
	{
		if (arr1[ind1].quan >= arr2[ind2].quan)
		{
			res[ind_res].quan = arr1[ind1].quan;
			strcpy(res[ind_res].value, arr1[ind1].value);
			ind1++;
		}
		else
		{
			res[ind_res].quan = arr2[ind2].quan;
			strcpy(res[ind_res].value, arr2[ind2].value);
			ind2++;
		}
		ind_res++;
	}

	while (ind1 < size1)
	{
		res[ind_res].quan = arr1[ind1].quan;
		strcpy(res[ind_res].value, arr1[ind1].value);
		ind1++;
		ind_res++;
	}

	while (ind2 < size2)
	{
		res[ind_res].quan = arr2[ind2].quan;
		strcpy(res[ind_res].value, arr2[ind2].value);
		ind2++;
		ind_res++;
	}
}

void copy_stats_arr(card_stats dest[], card_stats src[], int size)
{
	/*
	This function gets two arrays of card_stats and their size.
	It copys the second to the first.
	*/
	int i;
	for (i = 0; i < size; i++)
	{
		dest[i].quan = src[i].quan;
		strcpy(dest[i].value, src[i].value);
	}
}

void print_stats(card_stats stats[], int stats_size)
{
	/*
	This card gets an array of card_stats and its size and prints each
	value and quan in their order.
	*/
	int i;
	print_line(STAR, LINE1);
	printf(" Game Statistics ");
	print_line(STAR, LINE1);
	printf("\n");
	printf("Card # | Frequency\n");
	print_line(UNDER_LINE, UNDER_SIZE);
	printf("\n");
	for (i = 0; i < stats_size; i++)
	{
		printf(" %s ", stats[i].value);
		printf("%c", HORZ_LINE);
		printf("    %d     ", stats[i].quan);
		printf("\n");
	}
}

void free_all(player taki[], int size)
{
	/*
	This function frees all the memory allocated to the heap.
	*/
	int i;
	for (i = 0; i < size; i++)
	{
		free(taki[i].name);
		free(taki[i].cards);
	}
	free(taki);
}