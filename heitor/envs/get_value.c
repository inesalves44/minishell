
#include "../temp.h"

char    *get_env_value(t_root *root, char *key)
{
    t_env	*head;

	head = root->envs;
	while(root->envs)
	{

		if (ft_strncmp(key, root->envs->key, ft_strlen(key)) == 0)
		{
			root->envs = head;
			return (root->envs->value);
		}
		root->envs = root->envs->next;
	}
	root->envs = head;
	return (NULL);
}