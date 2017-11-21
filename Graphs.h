//
// Created by andrew on 14.11.17.
//

#ifndef GRAPHS_GRAPHS_H
#define GRAPHS_GRAPHS_H

#define LENGTH_STR 40

typedef char* type_inf;

struct node_str {
    struct node_str *left;
    struct node_str *right;
    struct node_str *parent;
    type_inf data;
};

struct head_p {
    int amount;
    struct node_str *son;
};


node_str *add_elem(head_p *head, node_str* node, type_inf value);

void print_graph(node_str *elem, FILE* dot_f);

void create_dot(head_p *head);

void print_node(node_str *elem, FILE* text, int b);

void write_graph(head_p *head);

void introduce_graph(head_p *head);

int create_tree(char *buf, int pos, head_p *head, node_str *node);

void akinator(head_p *head);

void ans_no(head_p *head, node_str *element);

node_str *down_tree(head_p *head, int *yes_no);

void ans_yes(head_p *head, node_str *element);

void print_def(node_str *elem);

void search_def(type_inf value, node_str *elem);


#endif //GRAPHS_GRAPHS_H
