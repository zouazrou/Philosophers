#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define sz 9
/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int	depth;

int			put_dice(int *grid, int dp);
bool		isfull(int *grid);
long long	solve(int *grid, int dp);
void		cpy(int *dst, int *src);

int main()
{
	int grid[sz];

	scanf("%d", &depth);
	for (int i = 0; i < sz; i++)
	{
		scanf("%d", grid + i);
		fprintf(stderr, "%d->", grid[i]);
	}

	solve(grid, depth);
	// Write an action using printf(). DON'T FORGET THE TRAILING \n
	// To debug: fprintf(stderr, "Debug messages...\n");

	printf("10\n");
	return 0;
}
/*
			0->6->0
			2->2->2
			1->6->1

	1->6->0			0->6->1
	2->2->2			2->2->2
	1->6->1			1->6->1

	1->6->1			1->6->1
	2->2->2			2->2->2
	1->6->1			1->6->1
	161222161

*/

long long	solve(int *grid, int dp)
{

	if (dp == 0 || isfull(grid) == true)
		return (1);
	int sl = 0;
	int	local_g[sz];
	cpy(local_g, grid);

	for (int i = 0; i < sz; i++)
	{
		sl += put_dice(local_g, dp);
	}
	return (sl);
}

// utils
int	put_dice(int *grid, int dp)
{
	int	place = 0;
	while (place < sz && grid[place])
	{
		place++;
	}
	middle(grid, place);
	return (place);
}

void	middle(int *dst, int p)
{

}
void	cpy(int *dst, int *src)
{
	for (int i = 0; i < sz; i++)
		dst[i] = src[i];
}

bool	isfull(int *grid)
{
	for (int i = 0; i < sz; i++)
	{
		if (grid[i] == 0)
			return (false);
	}
	return (true);
}
// test 1
// 20
// 0->6->0->2->2->2->1->6->1->
