
#include "tokenizer.h"

char    *ft_strjoin_1(char *str, char c)
{
    char        *s;
    int        i;
    int        n;

    i = 0;
    n = 0;
    s = malloc(strlen(str) + 2);
    while (str[i])
        s[n++] = str[i++];
    s[n] = c;
    s[n + 1] = 0;
    free(str);
    return (s); 
}

int ft_set_token_type(char *str, int q_flag, int *token_type)
{
    printf("%d <<<<<\n", q_flag);
    if(strcmp(str, "|") == 0 && !q_flag)
    {
        *token_type = 55;
        return (1);
    }
     if(strcmp(str, "<") == 0 && !q_flag)
        return (REDIRIN);
     if(strcmp(str, ">") == 0 && !q_flag)
        return (REDIROUT);
     if(strcmp(str, ">>") == 0 && !q_flag)
        return (APPEND);
     if(strcmp(str, "<<") == 0 && !q_flag)
        return (HEREDOC);
    else
        return (WORD);
    
}

t_token *add(t_token *t, char *s, int q_flag)
{
    t_token *n;
    t_token *tmp;

    n = malloc(sizeof(t_token));
    n->token = strdup(s);
    if(q_flag == '\"')
        n->quote = '\"';
    else if(q_flag == '\'')
        n->quote = '\'';
    else
        n->quote = 0;
    ft_set_token_type(s, q_flag, &n->token_type);
    printf("%d <<\n",n->token_type);
    n->next = 0;
    if (!t)
        return (n);
    tmp = t;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = n;
    return (t);
}

t_token *parser(char *line, t_token *token)
{
    int     i;
    int     j;
    int     d_flag;
    int     s_flag;
    int     f;
    char    *s;

    d_flag = 0;
    s_flag = 0;
    if (!line)
        return 0;
    f = 0;
    i = 0;
    s = strdup("");
    while (line[i])
    {
        f = 0;
        j = i;
        while (line[i] && line[i] == ' ')
            i++;
        while (line[j] && line[j] != ' ' && line[j] != '"' && line[j] != '\'')
            s = ft_strjoin_1(s, line[j++]);
        if (line[j] == '"' || line[j] == '\'')
        {
            if (line[j] == '"')
            {
                d_flag = 1;
                j++;
                while (line[j] != '"')
                    s = ft_strjoin_1(s, line[j++]);
            }
            if (line[j] == '\'')
            {
                s_flag = 1;
                j++;
                while (line[j] != '\'')
                    s = ft_strjoin_1(s, line[j++]);
            }
            j++;
            printf("%c\n", line[j + 1]);
            if ((line[j] != ' ' && line[j]))
                f = 1;
        }
        if (line[j] == ' ')
            j++;
        printf("HERE %d\n", f);
        if (!f)
        {
            if(s_flag)
            {
                token = add(token, s, '\'');
                s_flag = 0;
            }
            else if(d_flag)
            {
                token = add(token, s, '\"');
                d_flag = 0;
            }
            else
                token = add(token, s, 0);
            s = strdup("");
        }
        free(s);
        i = j;
    }
    return (token);
}

void    ft_free_list(t_token **token)
{
    t_token *temp;

    while(*token)
    {
        temp = *token;
        *token = (*token)->next;
        free(temp->token);
        free(temp);
    }
    *token = 0;
}

void    ft_print_token(t_token *token)
{

    while(token)
    {
        printf("token Type ->> %d\n", token->token_type);
        printf("token Quote ->> %c\n", token->quote);
        printf("token Value ->> %s\n", token->token);
        token = token->next;
    }
}

int main()
{
    t_token *t = 0;
    t_token *tmp = 0;
    char    *s;

    while (1)
    {
        s = readline("bash_lite>");
        t = parser(s, t);
        tmp = t;
        ft_print_token(tmp);
        free(s);
        ft_free_list(&t);
    }
}

