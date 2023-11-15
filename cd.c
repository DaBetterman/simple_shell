#include "shell.h"


/**
 * cd_dot - changes to the parent directory
 *
 * @database: data relevant (environ)
 *
 * Return: no return
 */
void cd_dot(data *database)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	/*Get the current working directory and make a copy*/
	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, database);
	dir = database->args[1];

	/*Check if the user wants to stay in the same directory*/
	if (_strcmp(".", dir) == 0)
	{
		set_env("PWD", cp_pwd, database);
		free(cp_pwd);
		return;
	}

	/*Check if the current directory is the root directory*/
	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}

	/*Reverse the path, split it, and get the parent directory*/
	cp_strtok_pwd = cp_pwd;
	rev_string(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			rev_string(cp_strtok_pwd);
	}

	/*Change the current working directory to the parent directory or root*/
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_env("PWD", cp_strtok_pwd, database);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", database);
	}
	database->status = 0;
	free(cp_pwd);
}

/**
 * cd_to - changes to a directory given
 * by the user
 *
 * @database: data relevant (directories)
 * Return: no return
 */
void cd_to(data *database)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	/*Get the current working directory*/
	getcwd(pwd, sizeof(pwd));

	dir = database->args[1];

	/*Try to change the current working directory to the user-specified directory*/
	if (chdir(dir) == -1)
	{

		/*Handle the case where changing directory fails*/
		get_error(database, 2);
		return;
	}

	/*Make copies of the old and new working directories, and set environment variables*/
	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, database);

	cp_dir = _strdup(dir);
	set_env("PWD", cp_dir, database);

	free(cp_pwd);
	free(cp_dir);

	/*Update the status to indicate success*/
	database->status = 0;

	/*Change the current working directory to the new directory*/
	chdir(dir);
}

/**
 * cd_previous - changes to the previous directory
 *
 * @database: data relevant (environ)
 * Return: no return
 */
void cd_previous(data *database)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	/*Get the current working directory and store it in the pwd array*/
	getcwd(pwd, sizeof(pwd));

	/*Make a copy of the current working directory path*/
	cp_pwd = _strdup(pwd);

	/*Get the value of the "OLDPWD" environment variable*/
	p_oldpwd = _getenv("OLDPWD", database->_environ);


	/*If "OLDPWD" is not found, use the copy of the current working directory*/
	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else

		/*Make a copy of "OLDPWD"*/
		cp_oldpwd = _strdup(p_oldpwd);

	/*Set "OLDPWD" to the copy of the current working directory*/
	set_env("OLDPWD", cp_pwd, database);

	/*Try to change the current working directory to the copy of "OLDPWD"*/
	if (chdir(cp_oldpwd) == -1)

	/*If it fails, set "PWD" to the copy of the current working directory*/
		set_env("PWD", cp_pwd, database);
	else

		/*If successful, set "PWD" to the copy of "OLDPWD"*/
		set_env("PWD", cp_oldpwd, database);

	/*Get the value of the "PWD" environment variable and print it to the standard output*/
	p_pwd = _getenv("PWD", database->_environ);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));

	/*Print the path to the standard output with a newline*/
	write(STDOUT_FILENO, "\n", 1);

	/*Free the allocated memory and update the status*/
	free(cp_pwd);
	if (p_oldpwd)

		/*Free the memory used by cp_oldpwd if it was allocated*/
		free(cp_oldpwd);

	/*Update the status to indicate success*/
	database->status = 0;

	/*Change the current working directory to the copy of "PWD"*/
	chdir(p_pwd);
}

/**
 * cd_to_home - changes to home directory
 *
 * @database: data relevant (environ)
 * Return: no return
 */
void cd_to_home(data *database)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	/*Get the current working directory and store it in the pwd array*/
	getcwd(pwd, sizeof(pwd));

	/*Make a copy of the current working directory path*/
	p_pwd = _strdup(pwd);

	/*Try to find the home directory path*/
	home = _getenv("HOME", database->_environ);

	/*If the home directory is not found, handle the case*/
	if (home == NULL)
	{
		/*Set "OLDPWD" to the original current directory*/
		set_env("OLDPWD", p_pwd, database);

		/*Free the memory used by p_pwd*/
		free(p_pwd);

		/*Exit the function*/
		return;
	}

	/*Try to change the current working directory to the home directory*/
	if (chdir(home) == -1)
	{
		/*Handle the case where changing directory fails*/
		get_error(database, 2);

		/*Free the memory used by p_pwd*/
		free(p_pwd);

		/*Exit the function*/
		return;
	}

	/*Set environment variables and update the status*/

	/*Set "OLDPWD" to the original current directory*/
	set_env("OLDPWD", p_pwd, database);

	/*Set "PWD" to the home directory*/
	set_env("PWD", home, database);

	/*Free the memory used by p_pwd*/
	free(p_pwd);

	/*Update the status to indicate success*/
	database->status = 0;
}
