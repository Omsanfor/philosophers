/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omsanfor <omsanfor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 18:03:56 by omsanfor          #+#    #+#             */
/*   Updated: 2022/06/26 18:03:57 by omsanfor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	is_not_num(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = -1;
		if (argv[i][0] == '-')
			return (1);
		else if (argv[i][0] == '+')
			j++;
		if (!ft_isdigit(argv[i][j + 1]))
			return (1);
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (1);
		}
	}
	return (0);
}

static int	is_minus(char *s)
{
	size_t	len;

	len = ft_strlen(s);
	if (*s == '+' && s++)
		len--;
	while (*s == '0' && *s && len--)
		s++;
	if (len > 10)
		return (1);
	else if (len < 10)
		return (0);
	if (ft_strncmp(s, "2147483648", 10) >= 0)
		return (1);
	return (0);
}

void	init_data_next(t_data *data)
{
	int	i;

	data->phil_die = 0;
	data->max_eat = 0;
	data->philos = (t_philo *)malloc(data->n_philos * sizeof(t_philo));
	i = -1;
	while (++i < data->n_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].eat_count = 0;
		if (i + 1 == data->n_philos)
			data->philos[i].r_philo = &data->philos[0];
		else
			data->philos[i].r_philo = &data->philos[i + 1];
		if (i == 0)
			data->philos[i].l_philo = &data->philos[data->n_philos - 1];
		else
			data->philos[i].l_philo = &data->philos[i - 1];
	}
}

void	initialise_sem(t_data *data)
{
	sem_unlink("/sem_print");
	sem_unlink("/sem_check");
	sem_unlink("/sem_forks");
	data->print = sem_open("/sem_print", O_CREAT, 0644, 1);
	data->check = sem_open("/sem_check", O_CREAT, 0644, 1);
	data->forks = sem_open("/sem_forks", O_CREAT, 0644, data->n_philos);
	sem_unlink("/sem_print");
	sem_unlink("/sem_check");
	sem_unlink("/sem_forks");
	if (data->print == SEM_FAILED || data->check == SEM_FAILED
		|| data->forks == SEM_FAILED)
	{
		write(2, "Error: sem_open failed\n", 23);
		exit(1);
	}
}

int	init_data(int argc, char *argv[], t_data *data)
{
	int	i;

	if (is_not_num(argc, argv))
		return (1);
	i = 0;
	while (++i < argc)
	{
		if (is_minus(argv[i]))
			return (1);
	}
	data->n_philos = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_slp = ft_atoi(argv[4]);
	data->n_eat = -1;
	if (argc == 6)
		data->n_eat = ft_atoi(argv[5]);
	init_data_next(data);
	initialise_sem(data);
	return (0);
}
