# include "tetris.h"

t_mino *duplicate_mino(t_mino *mino)
{
	t_mino *new_mino = (t_mino *)xmalloc(sizeof(t_mino));

	new_mino->mino_size = mino->mino_size;
	new_mino->mino_array = (char **)xmalloc(sizeof(char *) * (new_mino->mino_size + 1));
	for (int i = 0; i < new_mino->mino_size; i++)
	{
		new_mino->mino_array[i] = (char *)xmalloc(sizeof(char) * (new_mino->mino_size + 1));
		memcpy(new_mino->mino_array[i], mino->mino_array[i], new_mino->mino_size);
	}
	new_mino->mino_array[mino->mino_size] = NULL;
	new_mino->current_row = mino->current_row;
	new_mino->current_col = mino->current_col;
	return new_mino;
}

char	**mino_dup(char **mino, int size)
{
	char	**array;

	array = (char **)xmalloc(sizeof(char *) * (size + 1));
	for (int i = 0; i < size; i++)
		array[i] = memdup(mino[i], size);
	array[size] = NULL;
	return (array);
}